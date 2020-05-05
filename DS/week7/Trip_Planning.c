#include<stdio.h>
#include<stdlib.h>

#define INFINITY 1001

int Min( int array[], int size, int Visited[]){

    int min = INFINITY;
    int index = INFINITY;
    for(int i= 0; i < size; i++ ){
      if(Visited[i]){
        continue;
      }
      else{
      if( min > array[i]){ min = array[i]; index = i;}
      }
    }
    return index;
}

int main(){

//Take inputs
int N, M, S, D;
scanf("%d%d%d%d", &N, &M, &S, &D);


//Create Graph
int G[N][N][2];
int Visited[N];
int Dist[N];
int Cost[N];

for(int i= 0; i<N; i++){
  for(int j=0; j<N; j++){
    G[i][j][0] = INFINITY;
    G[i][j][1] = INFINITY;
  }
  Visited[i] = 0;
  Dist[i] = INFINITY;
  Cost[i] = INFINITY;
}

int start, dst, length, cost;
for(int i=0 ; i<M; i++){
scanf("%d%d%d%d", &start, &dst, &length, &cost);
G[start][dst][0] = length;
G[start][dst][1] = cost;
G[dst][start][0] = length;
G[dst][start][1] = cost;
}

//Dijkstra
Dist[S] = 0;
Cost[S] = 0;
int V;
int counter = 0;

while(1){

    V = Min(Dist, N, Visited);
    if(V == INFINITY || Dist[V] == INFINITY || counter > N ){
      break;
    }
    Visited[V] = 1;
    counter++;

    for(int i=0; i<N; i++){
      if( !Visited[i] ){  //not visited
        if( (Dist[V]+G[V][i][0]) < Dist[i]){
          Dist[i] = Dist[V] + G[V][i][0];
          Cost[i] = Cost[V] + G[V][i][1];
        }
        else if( (Dist[V]+G[V][i][0]) == Dist[i] && (Cost[V] + G[V][i][1]) <= Cost[i]){
          Cost[i] = Cost[V] + G[V][i][1];
        }
      }
    }
}

//Output
printf("%d %d", Dist[D], Cost[D]);

return 0;
}
