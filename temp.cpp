#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
using namespace std;

int main(){

    // 存储要判断的符号
    stack<string> symbols;
    // 存储判断对象
    unordered_set<string> targetSym;
    targetSym.insert("/");
    targetSym.insert("*");
    targetSym.insert("{");
    targetSym.insert("}");
    targetSym.insert("[");
    targetSym.insert("]");
    targetSym.insert("(");
    targetSym.insert(")");

    // 标志
    int label = 0;

    // 得到单行输入 text
    string text;
    string line;
    getline(cin, line); 
    while (line != "."){
        text += line;
        getline(cin, line);
    }

    // 魔法
    if ((text[0] == '{' or text[text.size() - 1] == ']') and !ispunct(text[4])){
        targetSym.erase("/");
        targetSym.erase("*");
    }


    // 把text中需要的符号导入到 symbols 中，注释符号按整体处理

    // 元素存储
    string elem;
    int count = 0;
    while (count < text.size()){

        // 类型统一
        string s;
        s += text[count];  // 不要对char用to_string，会转化为数字
        // 过滤无关内容
        if (targetSym.find(s) == targetSym.end()) {
            count++;
            continue;  // 这里不需要重置
        }

        // 符号分隔部分
        if (s == "/" or s == "*"){  // 处理注释符号，注意可能不完整
            elem += s;
            count++;  // 注意这里 count++ ，后面访问下一个值就不是 +1 了
            if (elem.size() == 2) {
                // 注释符号完整了
            }
            else if(text[count] != '/' and text[count] != '*'){
                // 符号不完整，直接丢弃
                elem = "";
                continue;
            }
            else{
                continue;  // 进入下个循环去叠加
            }
        }
        else {  // 非注释符号，直接处理
            elem += s;
            count++;
        }

        // 符号判断部分
        if (elem == "{" or elem == "[" or elem == "(" or elem == "/*"){
            symbols.push(elem);
        }
        else if(symbols.empty()){  // 缺左边只可能是前面已经匹配完了
            cout << "NO\n" << "?-" << elem << endl;
            exit(0);
        }
        else if (elem == "}"){
            if (symbols.top() != "{"){
                cout << "NO\n" << symbols.top() << "-?";
                exit(0);
            }
            else{
                symbols.pop();
            }
        }
        else if (elem == "]"){
            if (symbols.top() != "["){
                cout << "NO\n" << symbols.top() << "-?" << endl;
                exit(0);
            }
            else{
                symbols.pop();
            }
        }
        else if (elem == ")"){
            if (symbols.top() != "("){
                cout << "NO\n" << symbols.top() << "-?" << endl;
                exit(0);
            }
            else{
                symbols.pop();
            }
        }
        else if (elem == "*/"){
            if (symbols.top() != "/*"){
                cout << "NO\n" << symbols.top() << "-?" << endl;
                exit(0);
            }
            else{
                symbols.pop();
            }
        }
        else {
            cout << "FATAL ERROR!" << endl;
            cout << "elem:" << elem << endl;
            exit(0);
        }


        elem = "";  // 最后的最后，重置元素
    }

    // 走到结尾仍然有可能出现左边没匹配到的情况
    if (!symbols.empty()){
        cout << "NO\n" << symbols.top()[0] << "-?";
    }
    else{
        cout << "YES" << endl;
    }

}
