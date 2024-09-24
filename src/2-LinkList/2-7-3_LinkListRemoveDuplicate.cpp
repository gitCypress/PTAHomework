//
// Created by DesCypress on 24-9-22.
// 7-3 链表去重
// 使用一个大数组的地址直接作为链表存储数据完成链接，有点像内存池这是可以说的吗
// !!注意多个表的时候有没有用叉
// !!一定要想清楚循环条件，这里就是表跑完了不匹配才加，而不是只要不匹配就加，是比较特殊的情况
// !!下面这种实现和真正的链表有区别，映射不共享，数据也要记得搬过去
// 这种方法创建的本身就是一个内存空间，意味着着不能随便去创建新空间，尤其是这里的 wasted

#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <vector>
using namespace std;

struct Node {
    int data = 0;
    int next = -1;
};

int head = 100000;  // 主链头节点
int length;  // 主链输入长度

unordered_set<int> mySet;
vector<int> mainVec;
vector<int> wastedVec;

void input(Node* list);
void print(Node* list, int HEAD);
void printArr(Node* list, vector<int> arr);

int main() {
    // 自建内存
    Node* list = new Node[100001];  // 主链

    // 处理输入
    input(list);

    printArr(list, mainVec);

    delete list;
}

void input(Node* list) {

    cin >> list[head].next >> length;

    for (int i = 0; i < length; i++) {
        int addr_, next_, data_;
        cin >> addr_ >> data_ >> next_;
        list[addr_].data = data_;
        list[addr_].next = next_;

        if (mySet.find(abs(data_)) != mySet.end()) {
            wastedVec.push_back(addr_);
        }
        else {
            mainVec.push_back(addr_);
        }

        mySet.insert(abs(data_));

    }
}

void print(Node* list, int HEAD) {

    int current = list[HEAD].next;  // 临时指针
    while(current != -1) {  // 遍历，所以读到尾部即可

        // 不修改，只涉及读取
        stringstream sAddr, sNext;
        sAddr << setw(5) << setfill('0') << current;
        sNext << setw(5) << setfill('0') << list[current].next;

        cout << sAddr.str() << " "
             << list[current].data << " ";

        if (list[current].next == -1)
            cout << "-1" << endl;
        else
            cout << sNext.str() << endl;

        // 更新临时指针
        current = list[current].next;
    }

}

void printArr(Node* list, vector<int> arr) {

    for (size_t i = 0; i < arr.size() - 1; ++i) {  // 遍历，所以读到尾部即可

        // 不修改，只涉及读取
        stringstream sAddr;
        sAddr << setw(5) << setfill('0') << arr[i];

        cout << sAddr.str() << " "
             << list[arr[i]].data << " ";

        if (i == arr.size() - 2)
            cout << "-1" << endl;
        else {
            stringstream sNext;
            sNext << setw(5) << setfill('0') << arr[i+1];
            cout << sNext.str() << endl;
        }
    }
}

