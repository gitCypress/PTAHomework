//
// Created by 27301 on 25-5-5.
//

#include "StateMachine.hpp"

#include <iostream>
#include <string> // 尽管头文件已包含，但显式包含有助于明确依赖
#include <memory> // 用于 std::make_unique
#include <map>
#include <stdexcept> // 如果将来实现中用到标准异常
#include <utility>   // 用于 std::move (如果需要)
#include <cstdlib>   // 用于 system()

// --- State 基类默认实现 ---
void State::insertCoin(VendingMachine& /*machine*/) {
    std::cout << "[" << getName() << "] 在此状态下无法投币。\n";
}

void State::ejectCoin(VendingMachine& /*machine*/) {
    std::cout << "[" << getName() << "] 在此状态下无法退币。\n";
}

void State::selectItem(VendingMachine& /*machine*/, const std::string& /*item*/) {
    std::cout << "[" << getName() << "] 在此状态下无法选择商品。\n";
}

void State::onEnter(VendingMachine& /*machine*/) {
    // 默认无操作
}

void State::onExit(VendingMachine& /*machine*/) {
    // 默认无操作
}

// --- NoCoinState 方法实现 ---
void NoCoinState::insertCoin(VendingMachine& machine) {
    std::cout << "[" << getName() << "] 收到硬币。\n";
    machine.transitionTo<HasCoinState>(); // 转换到 HasCoin 状态
}

void NoCoinState::onEnter(VendingMachine& /*machine*/) {
    std::cout << "==== 机器就绪 - 请投入硬币 ====\n";
}

std::string NoCoinState::getName() const {
    return "NoCoin";
}

// --- HasCoinState 方法实现 ---
void HasCoinState::ejectCoin(VendingMachine& machine) {
    std::cout << "[" << getName() << "] 请求退币。\n";
    machine.doEjectCoin(); // 执行退币动作
    machine.transitionTo<NoCoinState>(); // 回到 NoCoin 状态
}

void HasCoinState::selectItem(VendingMachine& machine, const std::string& item) {
    std::cout << "[" << getName() << "] 选择商品: " << item << "\n";
    int count = machine.getItemCount(item);
    if (count > 0) {
        std::cout << "   商品有货 (" << count << " 件). 准备出货...\n";
        machine.transitionTo<DispensingState>(); // 转换到 Dispensing 状态
    } else {
        if (machine.hasItem(item)) { // 检查商品是否存在于库存记录中 (即使数量为0)
            std::cout << "   抱歉, " << item << " 已售罄。\n";
        } else {
            std::cout << "   抱歉, 无效的商品选项: " << item << "\n";
        }
        machine.transitionTo<SoldOutState>();
    }
}

void HasCoinState::onEnter(VendingMachine& /*machine*/) {
    std::cout << "---- 硬币已接收 - 请选择商品 ----\n";
}

void HasCoinState::onExit(VendingMachine& /*machine*/) {
    // 可选: 记录硬币使用等
}

std::string HasCoinState::getName() const {
    return "HasCoin";
}

// --- SoldOutState 方法实现 ---
void SoldOutState::onEnter(VendingMachine& machine) {
    std::cout << "!!!! 商品 " << machine.getSelectedItem() << " 无货或无效。请取回您的硬币。 !!!!\n";
    machine.doEjectCoin();
    machine.transitionTo<NoCoinState>();
}

// SoldOutState::ejectCoin 方法已被移除，因为其逻辑已由 onEnter 处理
// void SoldOutState::ejectCoin(VendingMachine& machine) {
//     std::cout << "[" << getName() << "] 选择失败后退回硬币。\n";
//     machine.doEjectCoin();
//     machine.transitionTo<NoCoinState>();
// }

std::string SoldOutState::getName() const {
    return "SoldOut";
}

// --- DispensingState 方法实现 ---
void DispensingState::onEnter(VendingMachine& machine) {
    std::cout << "[" << getName() << "] 正在处理销售...\n";
    machine.releaseItem(); // 调用机器的出货方法
    machine.transitionTo<NoCoinState>(); // 出货完成后, 自动返回到初始状态
}

std::string DispensingState::getName() const {
    return "Dispensing";
}

// --- VendingMachine 方法实现 ---
VendingMachine::VendingMachine() {
    // 初始化库存 (示例)
    inventory["可乐"] = 5;
    inventory["薯片"] = 3;
    inventory["糖果"] = 0; // 售罄示例

    // 设置初始状态，手动创建第一个状态实例并调用 onEnter
    currentState = std::make_unique<NoCoinState>();
    std::cout << "自动售货机启动，初始状态: " << currentState->getName() << std::endl;
    currentState->onEnter(*this); // 调用初始状态的进入动作
}

void VendingMachine::insertCoin() {
    currentState->insertCoin(*this);
}

void VendingMachine::ejectCoin() {
    currentState->ejectCoin(*this);
}

void VendingMachine::selectItem(const std::string& item) {
    this->selectedItem = item; // 临时存储选择，供状态使用
    currentState->selectItem(*this, item);
}

int VendingMachine::getItemCount(const std::string& item) const {
    auto it = inventory.find(item);
    if (it != inventory.end()) {
        return it->second;
    }
    return 0; // 商品不存在
}

void VendingMachine::releaseItem() {
    if (!selectedItem.empty() && inventory.count(selectedItem) && inventory[selectedItem] > 0) {
        std::cout << ">>> 正在发放商品: " << selectedItem << " <<<\n";
        inventory[selectedItem]--; // 库存减一
        std::cout << "   (剩余 " << inventory[selectedItem] << " 件 " << selectedItem << ")\n";
    } else {
        std::cout << "错误: 尝试发放无效或无货的商品: " << selectedItem << std::endl;
    }
    selectedItem.clear(); // 发放尝试后清除选择
}

void VendingMachine::doEjectCoin() {
    std::cout << ">>> 硬币已退回 <<<\n";
}

void VendingMachine::refillItem(const std::string& item, int quantity) {
    std::cout << "补充库存: " << item << " 添加 " << quantity << " 件。\n";
    inventory[item] += quantity;
}

const std::string& VendingMachine::getSelectedItem() const {
    return selectedItem;
}

bool VendingMachine::hasItem(const std::string& item) const {
    return inventory.count(item) > 0;
}

// --- 5. main 函数演示 ---
int main() {
    // 设置 C++ 的 std::cout 使用本地编码（对 Windows 上的 CMD/PowerShell 显示中文可能有用）
#ifdef _WIN32
    system("chcp 65001 > nul"); // 设置控制台代码页为 UTF-8
#endif

    VendingMachine machine; // 创建售货机实例
    std::cout << "\n--- 模拟开始 ---\n";

    // 场景 1: 成功购买
    std::cout << "\n* 场景 1: 购买可乐 *\n";
    machine.selectItem("可乐");
    machine.insertCoin();
    machine.insertCoin();
    machine.selectItem("可乐");
    std::cout << "----\n";

    // 场景 2: 选择售罄商品
    std::cout << "\n* 场景 2: 尝试购买糖果 (售罄) *\n";
    machine.insertCoin();
    machine.selectItem("糖果");
    std::cout << "----\n";

    // 场景 3: 选择不存在的商品
    std::cout << "\n* 场景 3: 尝试购买苏打水 (不存在) *\n";
    machine.insertCoin();
    machine.selectItem("苏打水");
    std::cout << "----\n";

    // 场景 4: 投币后退币
    std::cout << "\n* 场景 4: 投币后立即退币 *\n";
    machine.insertCoin();
    machine.ejectCoin();
    std::cout << "----\n";

    // 场景 5: 多次购买同一种商品直到售罄
    std::cout << "\n* 场景 5: 连续购买薯片 *\n";
    machine.insertCoin(); machine.selectItem("薯片");
    machine.insertCoin(); machine.selectItem("薯片");
    machine.insertCoin(); machine.selectItem("薯片");
    std::cout << "   (薯片初始有 3 件，应该买完了)\n";
    machine.insertCoin();
    machine.selectItem("薯片");
    std::cout << "----\n";

    // 场景 6: 补货后购买
    std::cout << "\n* 场景 6: 补充糖果并购买 *\n";
    machine.refillItem("糖果", 2);
    machine.insertCoin();
    machine.selectItem("糖果");

    std::cout << "\n--- 模拟结束 ---\n";

    return 0;
}
