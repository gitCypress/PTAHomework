//
// Created by DesCypress on 24-10-5.
//

#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>

using namespace std;
unordered_set<char> targetSymbol;

int main() {

    // 方便判断非目标值，这里很多标点符号都不算所以没法用 cctype
    unordered_set<char> leftsymbol;
    leftsymbol.insert('(');  // ()
    leftsymbol.insert('[');  // []
    leftsymbol.insert('{');  // {}

    unordered_set<char> targetSymbol;
    targetSymbol.insert('/');
    targetSymbol.insert('*');
    targetSymbol.insert('[');
    targetSymbol.insert(']');
    targetSymbol.insert('(');
    targetSymbol.insert(')');
    targetSymbol.insert('{');
    targetSymbol.insert('}');

    stack<int> symbols;

    // 注释判断标记
    vector<string> tipStorage;
    int tsCount = 0;

    string line;  // 结尾判断用的行就没办法了
    int tips[4] = {0, 0, 0, 0};  // 专门用来记录注释情况，默认注释里面不会有注释符号
    getline(cin, line);
    while (line != ".") {  // 行读取循环

        for (size_t i = 0; i < line.size(); i++) {  // 行内字符读取循环

            char c = line[i];
            // 其他字符，跳过
            if (targetSymbol.find(c) == targetSymbol.end()) {}

            // 左符号，插入
            else if (leftsymbol.find(c) != leftsymbol.end()) {
                symbols.push(c);
            }

            // 注释符号?
            else if (c == '/' or c == '*') {
            
            }
            
            // 栈为空
            else if (symbols.empty()) {
                cout << "NO\n" << "?-" << c << endl;
                exit(0);
            }

            // 右符号，判断是否相等
            else if (c == ')') {
                if (symbols.top() == '(')  symbols.pop();  // 相等则配对，栈内弹出
                else {  // 不相等则栈顶符号不得配对，top-?
                    cout << "NO\n" << static_cast<char>(symbols.top()) << "-?" << endl;
                    exit(0);
                }
            }
            else if (c == ']') {
                if (symbols.top() == '[')  symbols.pop();
                else {
                    cout << "NO\n" << static_cast<char>(symbols.top()) << "-?" << endl;
                    exit(0);
                }
            }
            else if (c == '}') {
                if (symbols.top() == '{')  symbols.pop();
                else {
                    cout << "NO\n" << static_cast<char>(symbols.top()) << "-?" << endl;
                    exit(0);
                }
            }

            // 注释判断

            // 什么都没匹配到
            else cout << "Fatal error." << endl;

        }

        cin >> line;
    }

    // 剩余判断
    if (symbols.empty()) cout << "YES" << endl;  // 完美匹配
    else {  // 有没匹配到的符号
        cout << "NO\n" << static_cast<char>(symbols.top()) << "-?" << endl;
    }

}
