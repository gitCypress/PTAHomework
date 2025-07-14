//
// Created by DesCypress on 24-9-22.
// 7-4 链表重排
// tips:
// 这里面 Ls是自己的地址，da是数据，Rs是 next

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

int length = 0;  // 输入节点（有效）个数
int startSerial;  // 起始地址
int beforeHalf = 0;  // 要把前半和后半分开，因为是以 1作结尾

struct Node {
    int addr = -1;
    int data = 0;
    int next = -1;
};

Node* input();  // 将输入转换成内存池
void print(Node* pool, int current = startSerial);  // 打印 “链表”, start 是头指针
int halfserial(Node* pool);  // 获取中点位

int main() {

    // 处理输入
    cin >> startSerial >> length;
    Node* pool = input();

    // N = 2 特例
    if (pool[pool[startSerial].next].next == -1) {
        int arr[2] = {pool[startSerial].addr, startSerial};

            std::stringstream ssL, ssL2;
            ssL << setw(5) << setfill('0') << pool[arr[0]].addr;
            ssL2 << setw(5) << setfill('0') << pool[arr[1]].next;

            cout << ssL2.str() << " "
                 << pool[pool[startSerial].next].data << " "
                 << ssL.str() << endl;

            cout << ssL.str() << " "
                 << pool[arr[0]].data << " "
                 << "-1" << endl;

        delete [] pool;
        return 0;
    };

    int half = halfserial(pool);
    pool[beforeHalf].next = -1; // 用 -1 标志分割前半和后半


    // 倒转后半部分，以 456为例
    int former = half;  // 4
    int current = pool[half].next;  // 5
    pool[former].next = -1;  // 实际末尾的 4->5 变为 4->null
    int label = 0;  // 倒二标记
    // cout << "former: " << pool[former].data << " current:" << pool[current].data << endl;

    while (true) {
        int next = pool[current].next;  // 存储 6 地址
        pool[current].next = former;  // 使得 5-> 6 变成 5-> 4
        former = current;  // 更新现指针为 6
        current = next;  // 更新前指针为 5
        // cout << "--former: " << pool[former].data << " current:" << pool[current].data << endl;
        if (label == 1) break;  // 判断是否为倒数第二次
        if (pool[current].next == -1) label = 1;  //abc, ba c, cba，可以看到，停止的条件必须在倒数第二次时知道

    }


    int lastSerial = former;  // 这时的 former是数组末尾数字；
    pool[beforeHalf].next = -1;

    // 交叉合并 543,(0)12 为 (0)51423  // 核心思路是 找停止条件-定位-修改-更新-修改-更新-。。。-收尾
    // 偶数：zap，azp=null
    // 奇数

    // 创建头节点
    pool[100000].next = startSerial;
    startSerial = 100000;

    int ap = startSerial, zp = lastSerial;  // 2 4 // 654 (0)123  (0)615243

    while(true) {
        int apn = pool[ap].next; // 3
        int zpn = pool[zp].next; // null

        if (apn == -1) {
            pool[ap].next = zp;
            break;
        }

        pool[zp].next = apn;
        pool[ap].next = zp;
        ap = apn;
        zp = zpn;

        if (zpn == -1) break;
    }

    print(pool, pool[startSerial].next);

    delete [] pool;
}

Node* input() {

    Node* output = new Node[100001];  // 左地址做下标

    for (int i = 0; i < length; i++) {
        int L, R; int d = 0;
        cin >> L >> d >> R;
        output[L].addr = L;
        output[L].data = d;
        output[L].next = R;
    }

    return output;
}

void print(Node* pool, int current) {

    while (current != -1) {

        // stringstream 格式化
        std::stringstream ssL, ssR;
        ssL << setw(5) << setfill('0') << pool[current].addr;
        ssR << setw(5) << setfill('0') << pool[current].next;

        cout << ssL.str() << " "
             << pool[current].data << " ";

        if (pool[current].next == -1) {
            cout << -1 << endl;
        }
        else cout << ssR.str() << endl;

        current = pool[current].next;
    }
}

int halfserial(Node* pool) {

    int slow = startSerial, fast = startSerial;

    while (fast != -1 && pool[fast].next != -1) {  // 快指针的判断有两个，因为有可能快指针下次直接跳进未定义区域或着快指针已经到最后一位了
        beforeHalf = slow;
        slow = pool[slow].next;
        fast = pool[pool[fast].next].next;
        // cout << "slow: " << pool[slow].data << ", fast: " << pool[fast].data << endl;
    }

    return slow;
};
