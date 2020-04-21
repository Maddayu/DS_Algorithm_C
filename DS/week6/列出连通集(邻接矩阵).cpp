#include <stdio.h>
#include <stdlib.h>
#include <functional>



#define MaxVertexNum 10
#define Vertex int
#define WeightType int
#define DataType int


//-------图的表示----------------
//邻接矩阵

typedef struct GNode *PtrToGNode;
typedef PtrToGNode MGraph;

struct GNode{

    int Nv, Ne;

    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};


//-------创建空图-----------------
MGraph CreateGraph( int VertexNum ){


    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for(int i=0; i<VertexNum; i++){
      for(int j=0; j<VertexNum; j++){
          Graph->G[i][j] = 0;
      }
      Graph->Data[i] = 0;
    }
    return Graph;
}

//-------插入边------------------------
typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;

struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};

void InsertEdge( MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

//--------构造图-------------------------
MGraph BuildGraph(){

int nv, ne, i;
MGraph Graph;

scanf("%d %d", &nv, &ne);
Graph = CreateGraph (nv);
Graph->Ne = ne;

for(i = 0 ; i < Graph->Ne; i++){
  Edge E =(Edge)malloc(sizeof( struct ENode));
  scanf("%d %d", &(E->V2), &(E->V1));
  E->Weight = 1;
  InsertEdge( Graph, E );
  }

  return Graph;
}

//---------DFS-----------------------------
void DFS(MGraph Graph, Vertex V)
{
      Graph->Data[V] = 1;
      printf("%d ", V);

      for(int w=0; w < Graph->Nv; w++ ){
          // 遍历 v 附近的所有点 w， 如果 w 和 v 有边，而且 w 未被访问
          if(Graph->G[V][w] == 1 && Graph->Data[w] == 0){
            DFS(Graph, w);
          }
        }
}

//---------BFS--------------------------------
void BFS(MGraph Graph, Vertex V)
{
      Vertex Queue[MaxVertexNum] = { -1 } ;
      Vertex pop;
      int front=0, rear=0, CurrentSize=0 ;

      //V 点被访问
      Graph->Data[V] = 1;
      printf("%d ", V);

      //访问过后， V 点入队列
      Queue[rear]=V;
      rear++;
      CurrentSize++;

      //循环执行直至队列变空
      while(CurrentSize != 0){

      //从队列取出被访问过的点 记录为 pop
      pop = Queue[front];
      front = (front+1)%MaxVertexNum;
      CurrentSize--;

      for(int w=0; w < Graph->Nv; w++){
        // 遍历 pop 附近的所有点 w， 如果 w 和 pop 有边，而且 w 未被访问
        if(Graph->G[pop][w] == 1 && Graph->Data[w] == 0){

          //访问 w 点
          Graph->Data[w] = 1;
          printf("%d ", w);

          //访问过后， w 点入队列
          Queue[rear]= w;
          rear = (rear+1)%MaxVertexNum;
          CurrentSize++;
        }
      }
    }
}





//---------List Component--------------------------------
void ListComponent(MGraph Graph, std::function<void (MGraph, Vertex)> func){
        for(int i=0; i< Graph->Nv; i++){
          if(Graph->Data[i] == 0){
            printf("{ ");
            func(Graph,i);
            printf("}\n");
          }
        }
}




//----------Main--------------------------------------


int main(){

    MGraph Graph = BuildGraph();

    ListComponent(Graph, DFS);

    //reset Graph
    for(int i=0; i < Graph->Nv; i++)
    {
        Graph->Data[i] = 0;
    }

    ListComponent(Graph, BFS);

    return 0;
}




/*
8 6
0 7
0 1
2 0
4 1
2 4
3 5
{ 0 2 4 1 7 }
{ 3 5 }
{ 6 }
{ 0 2 1 7 4 }
{ 3 5 }
{ 6 }
*/
