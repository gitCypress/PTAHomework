#include <stdio.h>
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
    int i, j, sum=0;
    CreateUDN(G);
    for(i = 0 ; i < G.vexnum ; ++i){
        sum=0;
        for(j = 0; j < G.vexnum; ++j){
            if(G.arcs[i][j] == 1)
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
            else G.arcs[i][j] = 65535;
        }
    }

    for (int i = 0; i < G.arcnum; i++){
        char head, tail;
        int cost;
        cin >> head >> tail >> cost;
        int headIndex = indexMap[head], tailIndex = indexMap[tail];

        G.arcs[headIndex][tailIndex] = cost;
        G.arcs[tailIndex][headIndex] = cost;
    }

}

void Prim(AMGraph G, char u){
        
}
