#include <iostream>
#include <windows.h>
#include <cstdint> // For uintptr_t

// 这是一个“受害者”类，它有一个虚函数
class Victim {
public:
    // 这是一个合法的虚函数，是CFG白名单的一部分
    virtual void legitimate_call() {
        std::cout << "  [SUCCESS] Inside the legitimate virtual function.\n";
    }
};

// 这是一个我们将要非法跳转到的目标函数
void invalid_target_function() {
    std::cout << "  [FAILURE] You should NEVER see this message! CFG has been bypassed!\n";
    // 如果CFG失效，为了安全起见，我们在这里制造一个断点
    __debugbreak();
}


int main() {
    std::cout << "--- Control Flow Guard (CFG) Trigger Demo ---\n\n";

    // --- 步骤 1: 创建一个合法的对象并正常调用 ---
    std::cout << "[1] Demonstrating a normal virtual function call:\n";
    Victim* real_victim = new Victim();
    real_victim->legitimate_call();
    delete real_victim;
    std::cout << "--------------------------------------------------\n\n";


    // --- 步骤 2: 准备伪造我们的攻击载荷 ---
    std::cout << "[2] Preparing a fake object and a fake vtable...\n";

    // 我们的伪造虚函数表。它是一个指针数组。
    // 我们将把这个数组的地址当作虚函数表的地址。
    uintptr_t fake_vtable[1]; 

    // 这是攻击的关键：我们不指向函数的开头，而是指向函数中间的某个位置。
    // 这100%不在CFG的合法目标白名单里。
    // uintptr_t 是一个能存下指针地址的整数类型。
    uintptr_t invalid_address = (uintptr_t)invalid_target_function + 5; // 指向函数中间
    fake_vtable[0] = invalid_address;
    
    std::cout << "  - Fake vtable created at address: " << &fake_vtable << "\n";
    std::cout << "  - It points to an invalid target address: 0x" << std::hex << invalid_address << std::dec << "\n";

    // 我们的伪造对象。我们只需要对象头部的空间来存放指向我们伪造vtable的指针。
    uintptr_t fake_object[1]; 
    
    // 让伪造对象的第一个成员（也就是隐藏的vtable指针）指向我们伪造的vtable
    fake_object[0] = (uintptr_t)fake_vtable;
    std::cout << "  - Fake object created at address:  " << &fake_object << "\n";
    std::cout << "  - Fake object now points to the fake vtable.\n";
    std::cout << "--------------------------------------------------\n\n";


    // --- 步骤 3: 执行攻击，触发CFG ---
    std::cout << "[3] Casting the fake object and attempting the illegal call...\n";
    std::cout << "    The program should crash here due to CFG violation.\n";

    // 将我们的伪造对象（的地址）强制类型转换为一个Victim类的指针
    Victim* attacker_ptr = (Victim*)fake_object;

    // 尝试通过这个被劫持的指针调用虚函数。
    // 调用流程：
    // 1. 程序访问 attacker_ptr 指向的 fake_object
    // 2. 读取其中的 vtable 指针，得到 fake_vtable 的地址
    // 3. 访问 fake_vtable[0]，得到 invalid_address
    // 4. CFG介入：在执行跳转到 invalid_address 之前，检查其合法性。
    // 5. CFG发现 invalid_address 不在白名单中，触发异常，终止程序。
    attacker_ptr->legitimate_call();


    // 如果你看到了这条消息，说明CFG没有启用或被绕过了
    std::cout << "\n[FAILURE] CFG was not triggered!\n";

    return 0;
}