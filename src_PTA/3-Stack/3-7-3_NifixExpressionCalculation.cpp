//
// Created by DesCypress on 24-10-5.
// 注意符号连着符号的情况；注意数字结尾会无法利用符号结算
//

#include <iostream>
#include <vector>
#include <stack>
#include <cctype>
#include <climits>

// 9+(3-1)*3+10/2
// 931-3*+10/2

using namespace std;

vector<string> inputFormat(string& input);  // 格式化原始输入数据，分开符号和数字
vector<string> nifixFormat(const vector<string>& input);  // 将中缀表达式转化为后缀表达式
int postfixCalulate(vector<string> input);  // 计算后缀表达式
int powerCal(int a, int b);  // 计算^

int main() {

    // 按行存储输入
    vector<string> input;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        input.push_back(line);
    }

    // 验证前两个函数
    // for (string &exp : input) {
    //
    //     vector<string> test = inputFormat(exp);
    //     vector<string> test2 = nifixFormat(test);
    //     for (const string& exps : test2) {
    //     cout << exps << " ";
    //     }
    //     cout << endl;
    // }

    // 输出结果
    for (string &exp : input) {

        int output =  postfixCalulate(nifixFormat(inputFormat(exp)));
        if (output == INT_MIN) cout << "INVALID" << endl;
        else cout << output << endl;
    }

}

vector<string> inputFormat(string& input) {

    vector<string> output;
    size_t size = input.size();

    if(size == 0) return output;

    string storage;
    for (int i = 0; i < size; i++) {  // 数字的结算标志有两个：符号、式子结束
        char currCh = input[i];

        if (!isdigit(currCh)){  // 符号结算
            if (!storage.empty()) {
                output.push_back(storage);
                storage = "";
            }
            storage += currCh;
            output.push_back(storage);
            storage = "";
        }
        else if (i == size - 1) {  // 结尾结算（不是符号的情况下）
            storage += currCh;
            output.push_back(storage);
        }
        else {  // 数字不结算
            storage += currCh;
        }
    }

    return output;
}

vector<string> nifixFormat(const vector<string>& input) {

// 如果遇到操作数（数字），直接输出到后缀表达式中。
// 如果遇到左括号 (，压入栈中。
// 如果遇到右括号 )，弹出栈中的运算符并输出，直到遇到对应的左括号 (。左括号弹出后不输出。
// 如果遇到运算符（如 +, -, *, /, ^），根据优先级处理：
// 如果栈为空，或者栈顶运算符的优先级低于当前运算符的优先级，将当前运算符压入栈中。
// 如果栈顶运算符的优先级高于或等于当前运算符的优先级，弹出栈顶运算符并输出，然后重复检查，直到满足上述条件。
//  当扫描完表达式后，依次弹出栈中剩余的所有运算符并输出。(会忘记这个)
// [当前/栈顶]：【+-|+-】弹出【+-|*/】弹出【+-|^】弹出
//            【*/|+-】压入【*/|*/】弹出【*/|^】弹出
//            【^|+-】压入【^|*/】压入【^|^】弹出
//            遇到左括号一概压入

    vector<string> output;  // 后缀表达式
    stack<string> symbols;  // 符号栈
    for (string elem : input) {
        if (isdigit(elem[0])) {  // 这个元素是数字
            output.push_back(elem);
        }
        else {  // 是符号
            if(symbols.empty() or elem == "(") {  // 符号栈空、左括号
                symbols.push(elem);
            }
            else if(elem == ")" ) {  // 右括号，一直弹出到左括号，丢弃括号
                string curr;
                while (true) {
                    curr = symbols.top();
                    if (curr == "(" ) {
                        symbols.pop();
                        break;
                    };
                    output.push_back(curr);
                    symbols.pop();
                }
            }
            else if(elem == "+" or elem == "-") {  // 这里面的处理顺序至关重要，稍不注意就会越界访问！
                string curr = symbols.top();
                while (curr != "(" ) {
                    output.push_back(curr);
                    symbols.pop();
                    if (symbols.empty()) break;  // 防止下面的访问越界，这个条件不能和 while条件放在一起
                    curr = symbols.top();
                }
                symbols.push(elem);
            }
            else if(elem == "*" or elem == "/") {
                string curr = symbols.top();
                while (curr != "(" and curr != "+" and curr != "-") {
                    output.push_back(curr);
                    symbols.pop();
                    if (symbols.empty()) break;  // 防止下面的访问越界
                    curr = symbols.top();
                }
                symbols.push(elem);
            }
            else if(elem == "^") {
                string curr = symbols.top();
                while (curr != "(" and curr != "+" and curr != "-" and curr != "*" and curr != "/") {
                    output.push_back(curr);
                    symbols.pop();
                    if (symbols.empty()) break;  // 防止下面的访问越界
                    curr = symbols.top();
                }
                symbols.push(elem);
            }
        }
    }

    // 导入剩余运算符

    while (!symbols.empty()) {
        output.push_back(symbols.top());
        symbols.pop();
    }

    return output;

}

int postfixCalulate(vector<string> input) {

    stack<string> stack;
    for (string elem : input) {
        if (isdigit(elem[0])) {  // 数字压入
            stack.push(elem);
        }
        else { // 符号，计算，注意这里是反着拿出来的！！！！
            int b = stoi(stack.top());
            stack.pop();
            int a = stoi(stack.top());
            stack.pop();

            int answer;
            if (elem == "+") answer = a + b;
            else if (elem == "-") answer = a - b;
            else if (elem == "*") answer = a * b;
            else if (elem == "/") {
                if (b != 0) answer = a / b;
                else return INT_MIN;
            }
            else if (elem == "^") answer = powerCal(a, b);
            else abort();

            stack.push(to_string(answer));
        }
    }

    return stoi(stack.top());
}

int powerCal(int a, int b) {
    int result = 1;
    while (b > 0) {
        if (b & 1) result *= a;
        a *= a;
        b >>= 1;
    }
    return result;
}
