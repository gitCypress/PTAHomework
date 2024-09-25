#include <iostream>
using namespace std;

struct DNode{
    int data;
    DNode* prev;
    DNode* next;  // 双向链表
};

typedef DNode* Node;

int main(){

    int position;
    cin >> position;

    // 创建头尾节点
    auto L = new DNode;
    auto LL = new DNode;
    L->prev = nullptr;
    L->next = LL;
    LL->prev = L;
    LL->next = nullptr;

    int input = 0;
    Node p = L;
    while(true){
        cin >> input;

        if (input == -1) break;

        auto newNode = new DNode;
        newNode->data = input;

        newNode->prev = p;
        newNode->next = LL;
        LL->prev = newNode;
        p->next = newNode;

        p = p->next;
    }

    p = LL;
    for (int i = 0; i < position; i++){
        if (p == nullptr) {
            cout << "NULL" << endl;
            return 0;
        }
        p = p->prev;
        
    }

    cout << p->data << endl;
    return 0;

} // 100 1 2 3 4 5 6 7 8 9 0 -1