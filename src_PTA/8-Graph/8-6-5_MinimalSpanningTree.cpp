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
void Prim(AMGraph G, char u){

    int startIndex = u - '0';  // 转化表示，没啥说的

    vector<int> lowcost;  // 每次我们遍历一个节点，就会把它们通往其他节点的权存这里面
    lowcost.resize(G.vexnum);
    vector<int> adjvex;  // 这个配合上面的数组，里面存储的值是上面每个下标存储权值的来头
    adjvex.resize(G.vexnum);

    // 这里先把首次遍历的节点的数据加进来了
    for (int i = 0; i < G.vexnum; i++){
        lowcost[i] = G.arcs[startIndex][i];  // 首遍历节点和其他节点的距离
        adjvex[i] = startIndex;  // 全部来自于首遍历节点
    }

    // 即使全连通，接下来按照路径遍历的次数，也不会超过节点数 - 1（上面遍历过首节点了）
    for (int i = 0; i < G.vexnum - 1; i++){
        
        // 找到当前权值组中的最小值及其下标
        int min = INT_MAX;
        int minIndex = 0;
        for (int j = 0; j < G.vexnum; j++){
            if (lowcost[j] != 0 && lowcost[j] < min){
                min = lowcost[j];
                minIndex = j;
            }
        }

        // 打印该权值的边，这里的对应关系可以方便理解
        cout << "[" << adjvex[minIndex] << ", " << minIndex << "]" << endl;

        // 清零当前节点权值记录，已经被遍历的节点作为一个整体来看与自身距离为0，这样就记录了谁已经被遍历了
        lowcost[minIndex] = 0;

        // 已经加入了一个点，那就再根据它的权关系更新权组，有更短的路径就进行替换
        for (int j = 1; j < G.vexnum; j++){
            if (lowcost[j] != 0 && G.arcs[minIndex][j] < lowcost[j]){
                lowcost[j] = G.arcs[minIndex][j];
                adjvex[j] = minIndex;
            }
        }

    }

}
