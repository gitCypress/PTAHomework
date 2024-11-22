#include <stdio.h>
#include <stdlib.h>

#define MVNum 100 
typedef struct ArcNode{
    int adjvex;  // 存储顶点对应下标
    struct ArcNode *nextarc;  // 下一个数据 
    int info;  // 权，可选
}ArcNode; 

typedef struct VNode{ 
    char data;  // 顶点数据 
    ArcNode *firstarc;  // 边表头指针
}VNode, AdjList[MVNum]; 

typedef struct{ 
    VNode vertices[MVNum];  // 顶点数据
    int vexnum, arcnum;   // 顶点数，弧数
}ALGraph;

void CreateUDG(ALGraph &G);

int main(){
    ALGraph G;     
    int i , j,sum=0;
    CreateUDG(G);
    ArcNode * p; 
    for(i = 0 ; i < G.vexnum ; ++i){
        sum=0;
        p=G.vertices[i].firstarc;
        for(; p!=NULL; p=p->nextarc){
                sum+=1;
        }
        if(i==0)
            printf("%d",sum);
        else
            printf(" %d",sum);
    }
    return 0;
}

/* 请在这里填写答案 */

#include <iostream>
#include <unordered_map>
using namespace std;

void CreateUDG(ALGraph &G){

    cin >> G.vexnum >> G.arcnum;
    unordered_map<char, int> vexMap;

    for (int i = 0; i < G.vexnum; i++){
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = nullptr;
        vexMap[G.vertices[i].data] = i;
    }

    for (int i = 0; i < G.arcnum; i++){
        char head, tail;
        cin >> head >> tail;
        int headIndex = vexMap[head];  
        int tailIndex = vexMap[tail];

        // 先给头部添加尾部节点，头插法避免遍历问题
        VNode& headVN = G.vertices[headIndex];
        ArcNode* tailAN = new ArcNode;
        tailAN->adjvex = vexMap[tail];
        tailAN->nextarc = headVN.firstarc;
        headVN.firstarc = tailAN;

        // 尾部
        VNode& tailVN = G.vertices[tailIndex];
        ArcNode* headAN = new ArcNode;
        headAN->adjvex = vexMap[head];
        headAN->nextarc = tailVN.firstarc;
        tailVN.firstarc = headAN;

    }

}
