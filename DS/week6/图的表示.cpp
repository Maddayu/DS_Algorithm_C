/*
用 邻接矩阵 实现 图
*/


#include <stdio.h>
#include <stdlib.h>
#define WeightType int



//-------------------------定义图-------------------------
typedef struct GNode *PtrToGNode;

struct GNode{
    int Nv;         /*  顶点数 */
    int Ne;         /*  边数  */

    WeightType G[MaxVertexNum][MaxVertexNum];  /*  二维数组存储  */
    DataType Data[MaxVertexNum];     /* 存顶点的数据 */

}；

typedef PtrToNode MGraph;    /*  以邻接矩阵存储的图类型 */
//------------------------------------------------------------------------------

//-------------------------MGraph 初始化-------------------------
typedef int Vertex;

MGraph CreateGraph （ int VertexNum ）            /*  初始化一个有VertexNum 个顶点但没有边的图  */
{
    Vertex V,W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    /* 默认顶点编号从 0 开始 到 Graph->Nv -1  */
    for(V=0; V<Graph->Nv; V++)
      for(W=0; W<Graph->Nv; W++)
        Graph->G[V][W] = 0;     /* 或 INFINITY  */

    return Graph;
}
//------------------------------------------------------------------------------


//-------------------------向 MGraph 中插入边-------------------------
typedef struct ENode *PtrToENode;

struct ENode{

      Vertex V1，V2;        /* 有向边<V1, V2> */
      WeightType Weight;   /* 权重 */

};
typedef PtrToENode Edge;

void InsertEdge (MGraph Graph, Edge E)
{

      /* 插入边 <V1,V2> */
      Graph[E->V1][E->V2] = E->Weight;

      /* 若是无向边，还要插入边<V2, V1> */
      Graph->G[E->V2][E->V1] = E->Weight;
}
//------------------------------------------------------------------------------


//-------------------------向 MGraph 中插入边-------------------------
MGraph BuildGraph()
{
      MGraph Graph;
      Edge E;
      Vertex V;
      int Nv, i;

      scanf("%d", &Nv);
      Graph = CreateGraph(Nv);
      scanf("%d", &(Graph->Ne));
      if (Graph->Ne != 0){
          E  = (Edge)malloc(sizeof(struct ENode));
          for( i=0; i<Graph->Ne; i++){
            scanf("%d %d %d",
                  &E->V1, &E->V2, &E->Weight);
                  InsertEdge( Graph, E);
          }
      }

      /* 如果顶点有数据的话，读入数据 */
      for( V=0; V<Graph->Nv; V++){
        scanf( " %c", &(Graph->Data[V]);
      }

      return Graph;
}
//------------------------------------------------------------------------------
