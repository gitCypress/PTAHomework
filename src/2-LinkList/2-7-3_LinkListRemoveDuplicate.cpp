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
using namespace std;

struct Node {
    int data = 0;
    int next = -1;
};

int head = 100000;  // 主链头节点
int length;  // 主链输入长度

int wastedHead = 100001;  // 丢弃链节点


void input(Node* list);
void print(Node* list, int HEAD);
void printArr(Node* list, int* arr, int LENGTH);

int main() {
    // 自建内存
    Node* list = new Node[100001];  // 主链

    // 处理输入
    input(list);

    // 核心逻辑
    int fp = head;  // 指向头节点的临时指针 former point
    int cp = list[head].next;  // 等于头指针的临时指针 current point

    int set[length];
    int setLength = 0;  // 记录比较过了的值，并且保留它的长度

    int wasted[length];
    int wastedLength = 0;  // 不需要也不能直接new一个list，这样会导致映射关系不统一

    while (cp != -1) {  // 遍历主链

        int listData = list[cp].data;  // 取一个数

        bool is_nobody = true;  // 是否跑完了整个记录值表都没跑出来

        for (int i = 0; i < length; i++) {  // 遍历记录值，listData主链元素和记录值依次比较

            int setData = set[i];  // 取数

            int cpn = list[cp].next;// 备份所有 自身会被被修改 的临时指针的 next，后面确定不用了再删

            if(abs(listData) == abs(setData)) {  // 如果相等，就需要将当前节点从主链删除，添加到到废弃链尾部


                list[fp].next = cpn;
                list[cp].next = -1;  // 标准删除操作

                wasted[wastedLength] = cp;  // 特殊添加操作，需要复制数据
                wastedLength++;

                // 更新操作
                fp = fp;  // 删除操作 fp不动
                cp = cpn;  // cp 在原链后移

                is_nobody = false;  // 有修改说明有一样的
                break;  // 不用再看后面了
            }
        }

        if (is_nobody) {  // 没有相等的值则不修改指针，只自更新主链，并把值添加到记录表
            fp = list[fp].next;
            cp = list[cp].next;

            set[setLength] = listData;  // 长度即为添加到尾部的下标
            setLength++;
        }

    };

    print(list, head);
    printArr(list, wasted, wastedLength);

    delete list;
}

void input(Node* list) {

    cin >> list[head].next >> length;

    for (int i = 0; i < length; i++) {
        int addr_, next_, data_;
        cin >> addr_ >> data_ >> next_;
        list[addr_].data = data_;
        list[addr_].next = next_;
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

void printArr(Node* list, int* arr, int LENGTH) {

    for (int i = 0; i < LENGTH ; i++) {  // 遍历，所以读到尾部即可

        // 不修改，只涉及读取
        stringstream sAddr;
        sAddr << setw(5) << setfill('0') << arr[i];

        cout << sAddr.str() << " "
             << list[arr[i]].data << " ";

        if (i == LENGTH - 1)
            cout << "-1" << endl;
        else {
            stringstream sNext;
            sNext << setw(5) << setfill('0') << arr[i+1];
            cout << sNext.str() << endl;
        }
    }
}

