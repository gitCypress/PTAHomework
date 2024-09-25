#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
using namespace std;

// string 太大了，尽量不要往里面放，格式化处理就行了
// 千万注意这个题输入处理的结尾不会是-1哦
// 注意.size()的数据类型是 size_t
// cin不能接逗号
struct Node{
    int addr;
    int data;
    int next;
};

void print(unordered_map<int, Node> map, vector<int> list){

    if (list.size() != 0){

        for(size_t i = 0; i < list.size(); i++){
            int key = list[i];
            stringstream sAddr;
            sAddr << setw(5) << setfill('0') << map[key].addr;
            cout << sAddr.str() << " " << map[key].data << " ";
            if(i != list.size() - 1){
                int nkey = list[i + 1];
                stringstream sNext;
                sNext << setw(5) << setfill('0') << nkey;
                cout << sNext.str() << endl; 
            }
            else{
                cout << "-1" << endl;
            }
        }
    }
}

int main(){

    int headPoint;
    int length;
    cin >> headPoint >> length;

    unordered_set<int> chkSet;
    unordered_map<int, Node> listSpace;

    int a, d, n;  // 建立映射，注意这应是唯一的映射空间，用别的表存地址
    for (int i = 0; i < length; i++){  // 直到达到长度数！！输入顺序不定，不能用-1判断哦
        cin >> a >> d >> n;
        listSpace[a] = {a, d, n};
    }

    vector<int> mainlist;
    vector<int> wastedlist;

    int curr = headPoint;  // 临时：头指针
    while(curr != -1){  // 一直遍历到最后
        if (chkSet.find(abs(listSpace[curr].data)) != chkSet.end()){  // 发现重复了
            wastedlist.push_back(curr);
        }
        else{  // 没匹配到，加入主链，并把数据加入检查表
            mainlist.push_back(curr);
            chkSet.insert(abs(listSpace[curr].data));
        }
        curr = listSpace[curr].next;  // 更新位置
    }
    // cout << "ans:" << endl;  // 清理干净输出
    print(listSpace, mainlist);
    print(listSpace, wastedlist);

}