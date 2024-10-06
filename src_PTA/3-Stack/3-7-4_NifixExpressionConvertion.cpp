#include <cctype>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    // 设置存储的容器
    stack<string> symbols;  // 暂存符号
    vector<string> output;  // 保存后缀表达式输出
    string input;  // 保存输入
    //接受输入
    getline(cin, input);
    //按字符处理输入
    int count = 0;
    while(count < output.size()){
        string elem;
        while(true){  // 每次分隔元素
            char str = input[count];
            if(isdigit(str)) {  // 是数字就继续叠加到 elem
                if(count == input.size() - 1) // 结尾是数字
                elem += str;
                count++;
            }
            else{  // 是符号要结算，这里可以处理结尾符号
                if (elem == "") {  // 说明前面的数字结算完了，直接处理符号
                    elem += str;
                    count++;
                    break;
                }
                else {  // elem 里面有数字，先结算数字，符号下轮处理
                    break;
                }
            }
        }
    }

}
