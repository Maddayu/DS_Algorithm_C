/*
already been reported.
/Users/mac/Documents/GitHub/DS_Algorithm_C/DS_Algorithm_C/DS/week4/Unary_Polynomial_Add_Multiply.cpp:18:17: error: cannot initialize a variable of type 'PolyNomial ' (aka 'PolyNode **') with an rvalue of type 'PtrToNode' (aka 'PolyNode ')
PolyNomial p = (PtrToNode)malloc(Nsizeof(struct PolyNode));
^ ~~~~~~~~~~


4 3 4 -5 2 6 1 -2 0
3 5 20 -7 4 3 1


15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0


5 20 -4 4 -5 2 9 1 -2 0


5 5
50 40 30 20 10
5 4 3 2 1

10 8
1 2
2 3
3 4
4 5
5 6
6 7
8 9
9 8


10 9
1 2
2 3
3 4
4 5
5 6
6 7
8 9
9 8
7 8

*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int N,E;
int mp[15][15];
int book[15];
int ans[15];
int num;
void dfs(int n){
    ans[num++]=n;
    book[n]=1;
    for(int i=0;i<N;i++){
        if(book[i]==0 && mp[n][i]==1){
            dfs(i);
        }
    }
}
void bfs(int n){
    ans[num++]=n;
    book[n]=1;
    queue<int> q;
    q.push(n);
    while(!q.empty()){
        int fr = q.front();
        q.pop();
        for(int i=0;i<N;i++){
            if(mp[fr][i]==1 && book[i]==0){
                book[i]=1;
                ans[num++]=i;
                q.push(i);
            }
        }
    }
}
int main(){
    int a,b;
    scanf("%d%d",&N,&E);
    for(int i=1;i<=E;i++){
        scanf("%d%d",&a,&b);
        mp[a][b]=1;
        mp[b][a]=1;
    }
    for(int i=0;i<N;i++){
        num=0;
        if(book[i]==0){
            dfs(i);
            printf("{");
            for(int i=0;i<num;i++)
                printf(" %d",ans[i]);
            printf(" }\n");

        }
    }
    memset(book,0,sizeof(book));
    memset(ans,0,sizeof(ans));
    for(int i=0;i<N;i++){
        num=0;
        if(book[i]==0){
            bfs(i);
            printf("{");
            for(int i=0;i<num;i++)
                printf(" %d",ans[i]);
            printf(" }\n");

        }
    }
    return 0;
}
