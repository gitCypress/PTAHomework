#include<cstring>
#include<iostream>
using namespace std;

#define MAXSTRLEN 255   // 最大尺寸

void get_nextval(char T[], int next[]);
int Index_KMP(char S[], char T[], int pos, int next[]);

int main()
{
char S[MAXSTRLEN+1],T[MAXSTRLEN+1];
char S1[MAXSTRLEN],S2[MAXSTRLEN];
cin >> S1 >> S2;
strcpy(&S[1],S1);
strcpy(&T[1],S2);    
S[0]=strlen(S1);  // S和T的第一位存储有效值个数（就是不含大小存储位置）
T[0]=strlen(S2); 
int *next = new int[T[0]+1];  // next数组，虽然有留位置但是不存大小了，用不到，减少一下负担
get_nextval(T,next);
//for (int i = 0; i < 9; i++){
//    cout << next[i] << " ";
//}
cout<<Index_KMP(S,T,1,next);
return 0; 
}

/* 请在这里填写答案 */
void get_nextval(char T[], int next[]){

    int TSize = T[0];  // T:length:0,data:1-TSIze

    next[0] = -1;
    next[1] = 1;  // next:unknown:0, data:1-TSize
    int index = 2;

    int bp = 1;  // 这里不太能说成共同前后缀长度，概念会很混乱
    int ep = 2;


    while(ep <= TSize){
        if(T[bp] == T[ep]){
            bp++;
            ep++;
            next[index] = bp; index++;
        }
        else if (bp == 1){
            ep++;
            next[index] = bp; index++;
        }
        else bp = next[bp - 1];  // ~abacabab
    }


}

int Index_KMP(char S[], char T[], int pos, int next[]){
    
    int SSize = S[0], TSize = T[0];
    int sp = 1, tp = 1;  // 针对大小设定做出的妥协。。。

    while (sp <= SSize){

        if (S[sp] == T[tp]){
            sp++;
            tp++;
            if (tp == TSize + 1){
                return sp - TSize;
            }   // 把这个if写在外面是个坏主意
        }
        else if (tp == 1){
            sp++;
        }
        else {
            tp = next[tp - 1];  // next 从 0 开始存
        }
    }

    return 0;

}
