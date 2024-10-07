#include <cctype>
#include <iostream>
#include <stack>
#include <vector>

// 对任何容器的访问以非空为前提

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

    string elem;

    if (input[count] == '-' or input[count] == '+'){  //首位减号属于负号
        if (input[count] == '-') elem += input[count];
        count++;
    }

    while(count < input.size()){

        // 分隔出单个元素，这里的数字可能是非整数或者负数
        while(true){

            char str = input[count];
            if(isdigit(str) or str == '.') {  // 是数字、小数点就继续叠加到 elem
                elem += str;
                count++;
                if (count == output.size() - 1) break;  // 如果是结尾数字就可以直接结束了
            }
            else{  // 是符号要结算，这里可以处理结尾符号

                if ((str == '-' or str == '+') and input[count - 1] == '('){  // 首位之外的负数前有括号
                    if (str == '-') elem += str;
                    count++;  // 作为数字的一部分处理
                }
                else if (elem.empty()) {  // 说明前面的数字结算完了，直接处理符号
                    elem += str;
                    count++;
                    break;
                }
                else {  // elem 里面有数字，先结算数字，符号下轮处理
                    break;
                }
            }
        }

        // 转化逻辑
        if (isdigit(elem[0]) or (elem.size() > 1 and isdigit(elem[1]))){  // 这个是数字(包括负数)
            output.push_back(elem);
        }
        else{  // 这个是符号
            if (symbols.empty() or elem == "(") {
                symbols.push(elem);
                elem = "";
                continue;  // 特别注意遍历放在循环外的变量，需要保证每次都能刷新到
            }

            string s = symbols.top();  // 遍历符号栈用临时变量，这个条件以栈不为空为前提
            if (elem == ")") {
                while (s != "(") {  // 一直存到左括号前
                    output.push_back(s);
                    symbols.pop();
                    s = symbols.top();
                }
                symbols.pop();  // 清除左括号
            }
            else if (elem == "+" or elem == "-") {
                while (s != "(") {
                    output.push_back(s);
                    symbols.pop();
                    if (symbols.empty()) break;
                    s = symbols.top();
                }
                symbols.push(elem);
            }
            else if (elem == "*" or elem == "/") {
                while (s != "(" and s != "+" and s != "-") {
                    output.push_back(s);
                    symbols.pop();
                    if (symbols.empty()) break;
                    s = symbols.top();
                }
                symbols.push(elem);
            }
        }

        elem = "";
    }

    while (!symbols.empty()) {
        output.push_back(symbols.top());
        symbols.pop();
    }

    for (size_t i = 0; i < output.size() ;i++) {
        cout << output[i] ;
        if (i != output.size() - 1) cout << " ";
    }
    cout << endl;

}
