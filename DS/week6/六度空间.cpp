#include <stdio.h>
#include <stdlib.h>
#include <functional>


#define MaxVertexNum 100001
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

    for(int i=1; i<= VertexNum; i++){
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


//---------BFS--------------------------------
float BFS_6deg(LGraph Graph, Vertex V)
{
      float result,counter=0;
      int layer=6;

      Vertex Queue[MaxVertexNum] = { -1 } ;
      Vertex pop;
      int front=1, rear=1, CurrentSize=0 ;

      Graph->G[V].Data = 2;

      //Enqueue first Vertex
      Queue[rear]=V;
      rear++;
      CurrentSize++;


      while(CurrentSize != 0 && layer >= 0){

      //Dequeue
      pop = Queue[front];
      front = (front+1)%MaxVertexNum;
      CurrentSize--;
      counter++;               //六度内的点包括 v（自己） + 其他六度内的点
    //  printf("pop:%d\n", pop);

      PtrToAdjVNode W = Graph->G[pop].FirstEdge;

      for( ; W!=NULL; W = W->Next){
        if(Graph->G[W->AdjV].Data == 0){
        Graph->G[W->AdjV].Data = 1;

        //Enqueue
        Queue[rear]= W->AdjV;
        rear = (rear+1)%MaxVertexNum;
        CurrentSize++;
        }
      }
        //Update last Vertex of the layer
        if(Graph->G[pop].Data == 2){
           Graph->G[Queue[rear-1]].Data = 2;
           layer--;                    //BFS 完成一层，就重新确定下一层的最后一个点。反复操作直至完成六次，此时剩余layer = 0，第七层数据不会被dequeue
        }
      }

      for(int i=1; i <= Graph->Nv; i++)
      {
            Graph->G[i].Data = 0;
      }

      result = counter*100 / Graph->Nv;
      return result;
}



//----------Main--------------------------------------
int main(){

    LGraph Graph = BuildGraph();
    float result;

    //reset Graph
    for(int i=1; i <= Graph->Nv; i++)
    {
        result = BFS_6deg(Graph, i );
        printf("%d: %.2f%%\n", i, result);
    }


    return 0;
}
