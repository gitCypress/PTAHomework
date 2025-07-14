#include <iostream>
using namespace std;

struct LNode{
    int data;
    LNode* next;
};

typedef LNode* Node;

Node input(){

    auto output = new LNode;

    int n = 0;
    Node p = output;
    cin >> n;
    while (n != -1){
        Node newNode = new LNode;
        newNode->data = n;

        newNode->next = nullptr;
        p->next = newNode;

        p = p->next;

        cin >> n;
    }

    return output->next;
}

int main(){

    Node list1 = new LNode;
    Node list2 = new LNode;
    Node olist = new LNode;

    list1->next = input();
    list2->next = input();

    Node p1 = list1->next;
    Node p2 = list2->next;
    Node o = olist;

    while (p1 != nullptr && p2 != nullptr){  // 有一条链跑完了就不需要比了
        if (p1->data < p2->data){  // 不变，小链后进
            p1 = p1->next;
        }
        else if(p1->data > p2->data){
            p2 = p2->next;
        }
        else{  // 相等，添加，一起往后拱
            Node newNode = new LNode;
            newNode->next = nullptr;
            newNode->data = p1->data;

            o->next = newNode;

            p1 = p1->next;
            p2 = p2->next;
            o = o->next;
        }
    }

    o = olist->next;
    if (o == nullptr) {
        cout << "NULL" << endl;
        return 0;
    }

    cout << o->data;
    o = o->next;
    while (o != nullptr ){
        cout << " " << o->data;
        o = o->next;
    }
}