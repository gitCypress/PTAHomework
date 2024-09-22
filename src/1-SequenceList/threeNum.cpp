#include <iostream>
#include <vector>
#include <climits>

using std::cin, std::cout, std::endl;

int main() {
    int count;  // 存储数目

    cin >> count;  // 存储首次传入的个数

    // 不足三个值的判断
    if (count <= 3) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    std::vector<int> number;  // 存储要排序的数字
    std::vector<int> output(3, INT_MIN);  // 存储最大的三个数字

    // 格式化数据
    int j;
    for (int i = 0; i < count; ++i) {
        cin >> j;
        number.push_back(j);
    }

    // 排序
    for (int Number : number) {
        if (Number > output[0]) {
            output[2] = output[1];
            output[1] = output[0];
            output[0] = Number;
        } else if (Number < output[0] && Number > output[1]) {
            output[2] = output[1];
            output[1] = Number;
        } else if (Number < output[1] && Number > output[2]) {
            output[2] = Number;
        }
    }

    // 输出结果
    if (output[1] == INT_MIN) {
        cout << "There is no second largest and third largest element" << endl;
    } else if (output[2] == INT_MIN) {
        cout << "There is no third largest element" << endl;
    } else {
        cout << output[0] << " " << output[1] << " " << output[2] << endl;
    }

    return 0;
}