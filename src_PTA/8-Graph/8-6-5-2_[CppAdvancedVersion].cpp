
#include <climits>
#include <iostream>
#include <unordered_map>
using namespace std;

#define MVNum 100                           
typedef struct{ 
    char vexs[MVNum];          
    int arcs[MVNum][MVNum];   
    int vexnum,arcnum;      
}AMGraph;

void CreateUDN(AMGraph &G);
void Prim(AMGraph G, char u);

int main(){
    AMGraph G;
    CreateUDN(G);
    char u;
    cin >> u;
    Prim(G , u);
    return 0;
}

void CreateUDN(AMGraph &G){

    cin >> G.vexnum >> G.arcnum;
    unordered_map<char, int> indexMap;

    for (int i = 0; i < G.vexnum; i++){
        cin >> G.vexs[i];
        indexMap[G.vexs[i]] = i;
    }

    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            if (i == j) G.arcs[i][j] = 0;
            else G.arcs[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < G.arcnum; i++){
        char head, tail;
        int data;
        cin >> head >> tail >> data;
        int headIndex = indexMap[head], tailIndex = indexMap[tail];

        G.arcs[headIndex][tailIndex] = data;
        G.arcs[tailIndex][headIndex] = data;

    }

}

#include <vector>
#include <unordered_map>
struct LowcostNode{
    int weight;  // 权值
    int from;  // 权值起点
};

void Prim(AMGraph G, char u){

    int startIndex = u - '0';  // 转化表示，没啥说的

    unordered_map<int, LowcostNode> lowcost;  // 其下标表示权值终点

    // 这里先把首次遍历的节点的数据加进来了
    for (int i = 0; i < G.vexnum; i++){
        lowcost[i].weight = G.arcs[startIndex][i];  // 首遍历节点和其他节点的距离
        lowcost[i].from = startIndex;  // 全部来自于首遍历节点
    }

    // 即使全连通，接下来按照路径遍历的次数，也不会超过节点数 - 1（上面遍历过首节点了）
    for (int i = 0; i < G.vexnum - 1; i++){
        
        // 找到当前权值组中的最小值及其下标
        int min = INT_MAX;
        int minIndex = 0;
        for (int j = 0; j < G.vexnum; j++){
            if (lowcost[j].weight != 0 && lowcost[j].weight < min){
                min = lowcost[j].weight;
                minIndex = j;
            }
        }

        // 打印该权值的边，这里的对应关系可以方便理解
        cout << lowcost[minIndex].from << "->" << minIndex << endl;

        // 清零当前节点权值记录，已经被遍历的节点作为一个整体来看与自身距离为0，这样就记录了谁已经被遍历了
        lowcost[minIndex].weight = 0;

        // 已经加入了一个点，那就再根据它的权关系更新权组，有更短的路径就进行替换
        for (int j = 1; j < G.vexnum; j++){
            if (lowcost[j].weight != 0 && G.arcs[minIndex][j] < lowcost[j].weight){
                lowcost[j].weight = G.arcs[minIndex][j];
                lowcost[j].from = minIndex;
            }
        }

    }

}
