#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <list>
#include <iostream>
using namespace std;
/*
00100 5
99999 -7 87654
23854 -15 00000
87654 15 -1
00000 -15 99999
00100 21 23854

00100 21 23854
23854 -15 99999
99999 -7 -1
00000 -15 87654
87654 15 -1
*/

struct fakeLNode{
    string addr;
    int data;
    string next;
};

void print(list<fakeLNode> flist);

int main(){

    // 导入初始数据
    string head;
    int size;
    cin >> head >> size;

    // 用字典创建一张伪表
    unordered_map<string, fakeLNode> fakeList;
    for (int i = 0; i < size; i++){
        int data;
        string addr, next;
        cin >> addr >> data >> next;
        fakeList[addr] = fakeLNode{addr, data, next};
    }

    // 把伪表转化成真表，后面好操作
    auto p = head;
    list<fakeLNode> realList;
    while (p != "-1"){
        realList.push_back(fakeList[p]);
        p = fakeList[p].next;
    }

    // for(auto i : realList){
    //     cout << i.addr << " " << i.data << " " << i.next << endl;
    // }
    // return 0;

    // 除去绝对值重复元素
    auto itr = realList.begin();
    unordered_set<int> record;
    list<fakeLNode> wastedList;
    while (itr != realList.end()){
        if (record.find(abs(itr->data)) != record.end()) {
            wastedList.push_back(*itr);
            itr = realList.erase(itr);
        }else{
            record.insert(abs(itr->data));
            itr++;
        }
    }

    // 打印表数据，注意结尾-1的处理
    print(realList);
    print(wastedList);

}

void print(list<fakeLNode> flist){
    auto p = flist.begin();
    auto p2 = p;
    p2++;

    while (p2 != flist.end()){
        cout << p->addr << " " << p->data << " " << p2->addr << endl;
        p++;
        p2++;
    }
    cout << p->addr << " " << p->data << " " << "-1" << endl;

}
