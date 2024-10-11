#include <iostream>
using namespace std;

void solve(int steps);
void clrcle(int width);

int ways;

int main(){

    int steps = 0;


    while (cin >> steps){
        
        solve(steps);

        cout << ways << endl;
        ways = 0;

    }

}

void solve(int steps){

    if (steps > 0) {
        solve(steps - 1);
        solve(steps - 2);
    }
    else if (steps == 0) ways++;
    else {}
}
