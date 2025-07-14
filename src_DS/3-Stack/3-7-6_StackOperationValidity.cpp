#include <iostream>
#include <string>
using namespace std;

string YES = "YES";
string NO = "NO";
int maxVolume = 0;

string& ifValid(string& op);

int main(){

    int chkNum = 0;
    cin >> chkNum >> maxVolume;
    cin.get();  // 把第一行的换行符给处理了

    for (int i = 0; i < chkNum; i++){   // 序列遍历检查

        string input;
        getline(cin, input);

        cout << ifValid(input) << endl;
    }

}


string& ifValid(string& op){

    int count = 0;  // 计数器

    for (char sx : op){  // 遍历字符串进行操作
        // 模拟操作
        if (sx == 'S') {
            count++;
        }
        else {
            count--;
        }
        // 操作后合法性判断
        if (count < 0 or count > maxVolume) return NO;
    }

    if (count == 0) {  // 判断最后是否空栈
        return YES;
    }
    else {
        return NO;
    }
}
