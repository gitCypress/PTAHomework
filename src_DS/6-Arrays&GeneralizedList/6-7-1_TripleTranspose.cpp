#include <iostream>
#include <map>
using namespace std;

struct coordinate{
    int x;
    int y;
    coordinate(int _x, int _y) : x(_x), y(_y) {};

    friend ostream& operator<<(ostream& ost, const coordinate& coor){
        ost << coor.x << " " << coor.y;
        return ost;
    };
};
struct compareCoor{
    bool operator()(const coordinate& m, const coordinate& n) const {
        if (m.x == n.x) return m.y < n.y;
        else return m.x < n.x;
    }
};

int main(){

    int m, n, count;
    cin >> m >> n >> count;

    map<coordinate, int, compareCoor> triple;

    for (int i = 0; i < count; i++){
        int x, y, data;
        cin >> y >> x >> data;
        coordinate elemCoordinate(x, y);
        triple[elemCoordinate] = data;
    }

    for (auto& p : triple){
        cout << p.first<< " ";
        cout << p.second << endl;
    }
}
