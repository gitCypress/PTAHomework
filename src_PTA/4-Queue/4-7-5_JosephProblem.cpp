#include <iostream>
using namespace std;

struct LNode{
    int data;
    LNode* next;
};

typedef LNode* Node;

int main(){

    int size, targetNum;
    cin >> size >> targetNum;

    while (size != 0 and targetNum != 0){

        // 初始化编号
        auto firstMonkey = new LNode;
        firstMonkey->data = 1;  // 不要头节点了，这就是第一个猴子
        firstMonkey->next = firstMonkey;  // 循环链表

        Node p = firstMonkey;  // 跟踪用
        Node endMonkey;  // 需要额外记录一下 1 之前的节点
        for (int i = 2; i <= size; i++){
        
            auto newNode = new LNode;
            newNode->data = i;
        
            newNode->next = p->next;
            p->next = newNode;

            endMonkey = newNode;
            p = p->next;
        }

        // 依次判断      
        Node fp = endMonkey;  
        p = endMonkey->next;
        int reportNum = 1;
        while(fp != p){  // 只要还没只剩下一个节点，就一直遍历

            if (reportNum == targetNum) {

                fp->next = p->next;
                delete p;

                p = fp->next;
                
                reportNum = 1;
            }
            else{
                fp = fp->next;
                p = p->next;
                reportNum++;
            }
        }

        cout << p->data << endl;
        cin >> size >> targetNum;
    }

}
