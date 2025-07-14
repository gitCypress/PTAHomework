//
// Created by DesCypress on 24-10-31.
//

#include <iostream>

using namespace std;

int gcd(int a, int b){
    // 保证输入时 a > b
    while (b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b){
    return a * b / gcd((a > b) ? a : b, (a < b) ? a : b);
}

int main() {
    int m, n;
    cin >> m >> n;

    cout << gcd((m > n) ? m : n, (m < n) ? m : n) << endl;
    cout << lcm(m ,n) << endl;

}


