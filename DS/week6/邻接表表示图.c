#include <stdio.h>
#include <stdlib.h>
#define Vertex int

// G[n] 为指针数组，对应矩阵每行一个链表

typedef struct AdjVNode *PtrToAdjVNode;

struct AdjVNode{                                    //AdjList -> Vnode -> AdjVNode
    Vertex AdjV;      /* 邻接点下标 */
    WeightType Weight;   /* 边权重 */
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
    DataType Data; /* 存顶点的数据 */
}AdjList[MaxVertexNum];
/* AdjList 是邻接表类型*/

typedef struct GNode *PtrToGNode;
Struct GNode{
  int Nv;         /* 顶点数 */
  int Ne;         /* 边数  */
  AdjList G;      /* 邻接表 */
};

typedef PtrToGNode LGraph;
/* 以邻接表的方式存储的图类型  */



//------------------------------------------------
/*LGraph 初始化*/
typedef int Vertex;
LGraph CreateGraph (int VertexNum)
{
  Vertex V, W;
  LGraph Graph;

  Graph = (LGraph)malloc(sizeof(struct GNode));
  Graph->Nv = VertexNum;
  Graph->Ne = 0;


  for( V=0; V<Graph->Nv; V++)
      Graph->G[V].FirstEdge = NULL;

  return Graph;
}

//------------------------------------------------
/*向LGraph 中插入边*/
typedef struct ENode *PtrToENode;

struct ENode{

      Vertex V1，V2;        /* 有向边<V1, V2> */
      WeightType Weight;   /* 权重 */

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
