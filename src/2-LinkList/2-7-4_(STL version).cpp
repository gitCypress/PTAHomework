#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
// （遍历先用注释把停止条件写出来）遍历一定是在循环里面使用临时变量，不可能去用头指针；注意cin用法
struct Node{
    int addr;
    int data;
    int next;
};

void print(unordered_map<int, Node> map, vector<int> list){

    for(size_t i = 0; i < list.size(); i++){
        stringstream sAddr;
        sAddr << setw(5) << setfill('0') << map[list[i]].addr;
        cout << sAddr.str() << " " << map[list[i]].data << " ";
        if(i == list.size() - 1){
            cout << "-1" << endl;
        }
        else{
            stringstream sNext;
            sNext << setw(5) << setfill('0') << map[list[i+1]].addr;
            cout << sNext.str() << endl;
        }
    }
}

int main(){

    int headPoint, length;
    cin >> headPoint >> length;

    unordered_map<int, Node> listSpace;

    for(int i = 0; i < length; i++){  // 把输入遍历完
        int a, d, p;
        cin >> a >> d >> p;
        listSpace[a] = {a, d, p};
    }

    vector<int> addrVec;

    int current = headPoint;
    while (current != -1){  // 把表的地址遍历一遍，顺便记一下长度哦
        addrVec.push_back(current);
        current = listSpace[current].next;  // 更新
    }


    vector<int> resetVec;
    int size = addrVec.size();
    for (int i = 0, j = size - 1; i <= j; i++, j--){
        if (i < j){
            resetVec.push_back(addrVec[j]);
            resetVec.push_back(addrVec[i]);
        }
        else{
            resetVec.push_back(addrVec[i]);
        }
    }

    print(listSpace, resetVec);
}