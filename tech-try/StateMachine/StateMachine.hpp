//
// Created by 27301 on 25-5-5.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <string>
#include <memory> // 用于 std::unique_ptr
#include <map>    // 用于 std::map (库存)
#include <iostream> // 用于 VendingMachine::transitionTo 中的 std::cout

// 前向声明
class VendingMachine;

// --- 1. State 接口 (基类) ---
// 定义所有状态共有的接口
class State {
public:
    virtual ~State() = default; // 重要的虚析构函数

    // 用户可以触发的操作，提供默认实现
    virtual void insertCoin(VendingMachine& machine);  // 投币: 默认报错
    virtual void ejectCoin(VendingMachine& machine);  // 退币: 默认报错
    virtual void selectItem(VendingMachine& machine, const std::string& item);  // 选择商品: 默认报错

    // 可选的生命周期钩子 (进入/退出状态时执行)
    virtual void onEnter(VendingMachine& /*machine*/);  // 进入状态时：默认无操作   
    virtual void onExit(VendingMachine& /*machine*/);  // 退出状态时：默认无操作

    // 用于标识状态/日志输出
    [[nodiscard]] virtual std::string getName() const = 0; // 强制派生类提供名称
};

// --- 2. 具体状态类的声明 ---
// 无硬币状态
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine& machine) override;                      // 投币: 进入「有硬币」状态 
        // ejectCoin(VendingMachine& machine)                               // 退币: 默认报错
        // selectItem(VendingMachine& machine, const std::string& item)     // 选择商品: 默认报错
    void onEnter(VendingMachine& /*machine*/) override;                     // 进入状态时：提示投币
        // void onExit(VendingMachine& /*machine*/) override;               // 退出状态时：默认无操作
    std::string getName() const override;
};

// 有硬币状态
class HasCoinState : public State {
public:
    // insertCoin(VendingMachine& machine)                                  // 投币: 默认报错
    void ejectCoin(VendingMachine& machine) override;                       // 退币: 执行退币并进入「无硬币」状态
    void selectItem(VendingMachine& machine, const std::string& item) override; // 选择商品: 检查库存, 进入「出货」或「售罄」状态
    void onEnter(VendingMachine& /*machine*/) override;                     // 进入状态时：提示选择商品
    void onExit(VendingMachine& /*machine*/) override;                      // 退出状态时：默认无操作
    std::string getName() const override;
};

// 售罄状态
class SoldOutState : public State {
public:
    // insertCoin(VendingMachine& machine)                              // 投币: 默认报错
    // ejectCoin(VendingMachine& machine)                               // 退币: 默认报错 (onEnter 已处理退币逻辑)
    // selectItem(VendingMachine& machine, const std::string& item)     // 选择商品: 默认报错
    void onEnter(VendingMachine& machine) override;                     // 进入状态时：提示商品无货/无效，自动退币并回到「无硬币」状态
    // void onExit(VendingMachine& /*machine*/) override;               // 退出状态时：默认无操作
    std::string getName() const override;
};

// 出货状态 (正在处理销售并发放商品)
class DispensingState : public State {
public:
    // insertCoin(VendingMachine& machine)                              // 投币: 默认报错
    // ejectCoin(VendingMachine& machine)                               // 退币: 默认报错
    // selectItem(VendingMachine& machine, const std::string& item)     // 选择商品: 默认报错
    void onEnter(VendingMachine& machine) override;                     // 进入状态时：发放商品，然后自动回到「无硬币」状态
    // void onExit(VendingMachine& /*machine*/) override;               // 退出状态时：默认无操作
    std::string getName() const override;
};

// --- 3. Context (自动售货机本身) 声明 ---
class VendingMachine {
private:
    std::unique_ptr<State> currentState; // 当前状态 (使用智能指针管理)
    std::map<std::string, int> inventory; // 商品库存 <商品名, 数量>
    std::string selectedItem; // 临时存储当前选择的商品名

public:
    VendingMachine(); // 构造函数
    ~VendingMachine() = default; // 默认析构函数

    // --- 由外部世界触发的动作 ---
    void insertCoin();
    void ejectCoin();
    void selectItem(const std::string& item);

    // --- 供状态类与售货机交互的方法 ---

    // 状态转换函数 (模板，方便指定目标状态类型)
    template <typename StateType>
    void transitionTo();

    int getItemCount(const std::string& item) const; // 获取商品库存
    void releaseItem(); // 发放商品
    void doEjectCoin(); // 执行退币操作
    void refillItem(const std::string& item, int quantity); // 补充商品库存
    const std::string& getSelectedItem() const; // 获取当前选择的商品名
    bool hasItem(const std::string& item) const; // 检查商品是否存在(即使数量为0)
};

// --- VendingMachine 模板成员函数定义 ---
// 模板成员函数的定义通常放在头文件中
template <typename StateType>
void VendingMachine::transitionTo() {
    if (currentState) {
        // std::cout << "DEBUG: Exiting state " << currentState->getName() << std::endl;
        currentState->onExit(*this); // 调用当前状态的退出动作
    }
    std::cout << "状态转换: 从 " << (currentState ? currentState->getName() : "nullptr");
    currentState = std::make_unique<StateType>(); // 创建新状态对象
    std::cout << " 到 " << currentState->getName() << std::endl;
    // std::cout << "DEBUG: Entering state " << currentState->getName() << std::endl;
    currentState->onEnter(*this);  // 调用新状态的进入动作
}

#endif //STATEMACHINE_HPP
