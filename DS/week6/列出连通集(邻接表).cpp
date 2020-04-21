#include <stdio.h>
#include <stdlib.h>
#include <functional>



#define MaxVertexNum 10
#define Vertex int
#define WeightType int
#define DataType int


//-------图的表示----------------
//邻接链表

typedef struct AdjVNode *PtrToAdjVNode;

struct AdjVNode{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

typedef struct VNode{
      PtrToAdjVNode FirstEdge;
      DataType Data;
} AdjList[MaxVertexNum];


typedef struct GNode *PtrToGNode;
struct GNode{

      int Nv, Ne;
      AdjList G;
};
typedef PtrToGNode LGraph;




//-------创建空图-----------------
LGraph CreateGraph( int VertexNum ){

    LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for(int i=0; i< VertexNum; i++){
        Graph->G[i].FirstEdge = NULL;
        Graph->G[i].Data = 0;    // 0 表示该顶点未被访问过
    }

    return Graph;
}

//-------插入边------------------------
typedef struct ENode *PtrToENode;

struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};

typedef PtrToENode Edge;


void InsertEdge( LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;

    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    //若是无向图，还要插入边 <V2, V1>
    /*为 V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;

    /* 将v1插入v2的表头*/
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

//--------构造图-------------------------
LGraph BuildGraph(){

int nv, ne, i;
LGraph Graph;

scanf("%d %d", &nv, &ne);
Graph = CreateGraph (nv);

for(i = 0 ; i < ne; i++){
  Edge E =(Edge)malloc(sizeof( struct ENode));
  scanf("%d %d", &(E->V2), &(E->V1));       E->Weight = -1;   //Weight not needed in this example
  InsertEdge( Graph, E );
  }

  return Graph;
}

//---------DFS-----------------------------
void DFS(LGraph Graph, Vertex V)
{
      int Sorted[VertexNum];
      Graph->G[V].Data = 1;
      printf("%d ", V);

      PtrToAdjVNode W = Graph->G[V].FirstEdge;
      for( ; W!=NULL; W = W->Next){
        if(Graph->G[W->AdjV].Data == 0){
          DFS(Graph, W->AdjV);
        }
      }
}

//---------BFS--------------------------------
void BFS(LGraph Graph, Vertex V)
{
      Vertex Queue[MaxVertexNum] = { -1 } ;
      Vertex pop;
      int front=0, rear=0, CurrentSize=0 ;

      Graph->G[V].Data = 1;
      printf("%d ", V);

      //Enqueue first Vertex
      Queue[rear]=V;
      rear++;
      CurrentSize++;

      while(CurrentSize != 0){

      //Dequeue
      pop = Queue[front];
      front = (front+1)%MaxVertexNum;
      CurrentSize--;

      PtrToAdjVNode W = Graph->G[pop].FirstEdge;
      for( ; W!=NULL; W = W->Next){
        if(Graph->G[W->AdjV].Data == 0){
        Graph->G[W->AdjV].Data = 1;
        printf("%d ", W->AdjV);

        //Enqueue
        Queue[rear]= W->AdjV;
        rear = (rear+1)%MaxVertexNum;
        CurrentSize++;
        }
        }
      }

}





//---------List Component--------------------------------
void ListComponent(LGraph Graph, std::function<void (LGraph, Vertex)> func){
        for(int i=0; i< Graph->Nv; i++){
          if(Graph->G[i].Data == 0){
            printf("{ ");
            func(Graph,i);
            printf("}\n");
          }
        }
}




//----------Main--------------------------------------


int main(){

    LGraph Graph = BuildGraph();

    ListComponent(Graph, DFS);

    //reset Graph
    for(int i=0; i < Graph->Nv; i++)
    {
        Graph->G[i].Data = 0;
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
