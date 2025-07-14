// 操作同一数据要么引用要么指针

#include <iostream>
#include <stack>
using namespace std;

struct stick{  // 模拟棍子，结构让其有名字，方便打印
    char name;
    stack<int> disk;
    stick(char _name) : name(_name) {};
};

void hanoi(int height, stick& source, stick& assist, stick& target);
void move(stick& from, stick& to);


int main(){

    int height;
    cin >> height;
    stick source('a'), assist('b'), target('c');

    for (int i = height; i > 0; i--){  // 棍子初始化盘子
        source.disk.push(i);
    }

    hanoi(height, source, assist, target);
}

void hanoi(int height, stick& source, stick& assist, stick& target){

    if (height < 1) {
        cout << "Wrong heigth value." << endl;
    }

    if (height == 1){  // 注意覆盖定义域的所有情况
        move(source, target);
    }
    else if (height == 2){  // 这部分是汉诺塔问题的核心思路

        move(source, assist);
        move(source, target);
        move(assist, target);

    }
    // 在大于二的时候会将底盘之上看作整体，和核心思路是对应的
    else{  // height > 2

        // 中间的柱子起到辅助作用，填此时不需要的就行
        hanoi(height - 1, source, target, assist);  // source->assisit
        move(source, target);  // 只动“最底下”的圆盘  // source->target
        hanoi(height - 1, assist, source, target);  // assist->target

    }
};

void move(stick& from, stick& to){

    cout << "No." << from.disk.top() << " disk: "
         << from.name << "->" << to.name << endl;

    to.disk.push(from.disk.top());
    from.disk.pop();

}
