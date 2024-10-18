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
cout<<Index_KMP(S,T,1,next);
return 0; 
}

/* 请在这里填写答案 */
void get_nextval(char T[], int next[]){

    int TSize = T[0];
    int p = 1;
    next[p] = 0;
    int coPrefix = 0;

    while(p < TSize){
        if (T[coPrefix + 1] == T[p + 1]){
            coPrefix++;
            p++;
            next[p] = coPrefix;
            cout << p << ":" << next[p] << " ";
        }
        else if (coPrefix == 0){
            p++;
            next[p] = coPrefix;
            cout << p << ":" << next[p] << " ";

        }
        else{
            coPrefix = next[coPrefix];  // 这里不减一，因为next首位无意义
        }
    }

}

int Index_KMP(char S[], char T[], int pos, int next[]){
    
    int SSize = S[0], TSize = T[0];
    int sp = 1, tp = 1;  // 针对大小设定做出的妥协。。。

    while (sp <= SSize){
        if (tp == TSize + 1){
            return sp - TSize;
        }
        else if (S[sp] == T[tp]){
            sp++;
            tp++;
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
