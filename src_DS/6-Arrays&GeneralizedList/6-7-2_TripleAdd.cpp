#include <iostream>
#include <map>
#include <ostream>
using namespace std;

struct coordinate{
    int x;
    int y;

    coordinate(int _x, int _y) : x(_x), y(_y) {};
    friend ostream& operator<<(ostream& ost, const coordinate& coor){
        ost << coor.x << " " << coor.y;
        return ost;
    }
};

struct compare_coordinate{
    bool operator()(const coordinate& cm, const coordinate& cn) const {
        if (cm.x == cn.x) return cm.y < cn.y;
        else return cm.x < cn.x; 
    }
};

int main(){

    int m, n, countA, countB;
    cin >> m >> n >> countA >> countB;

    map<coordinate, int, compare_coordinate> output;

    for (int i = 0; i < countA + countB; i++){

        int x, y, data;
        cin >> x >> y >> data;
        coordinate coor(x, y);
        
        auto itr = output.find(coor);
        if (itr != output.end()) data += itr->second;
        if (data != 0){
            output[coor] = data;
            }
        else{
            output.erase(itr);
        }
    }    

    cout << m << " " << n << " " << output.size() << endl;
    for (auto i :output){
        cout << i.first << " " << i.second << endl;
    }
}
