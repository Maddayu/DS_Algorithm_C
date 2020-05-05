#include<stdio.h>
#include<stdlib.h>


#define MaxVertexNum 102
#define Vertex int
#define WeightType int
#define DataType int
#define FULL 1001

typedef struct GNode *PtrToGNode;
typedef PtrToGNode MGraph;

typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;


struct GNode{
    int Nv;
    int Ne;

    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};

struct ENode{
    Vertex V1;
    Vertex V2;
    WeightType Weight;

};

MGraph CreateGraph(int nv){
    MGraph Graph =(PtrToGNode)malloc(sizeof(struct GNode));

    Graph->Nv = nv; Graph->Ne = 0;
    for(int v=1; v <= nv; v++){
      for(int w=1; w <= nv; w++){
        Graph->G[v][w]= FULL;
      }
    }
  return Graph;
};

void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
};


int main(){

//Read Input
int NumVertex;
int NumEdge;



scanf("%d %d", &NumVertex, &NumEdge);
int MaxEdgeNum;
MaxEdgeNum = NumVertex*(NumVertex - 1)/2;

if( NumEdge > MaxEdgeNum ){
    printf("0\n");         //Invalid number of Edges
    return 0;
}

if( NumVertex == 1){
    printf("0\n");         //can't take the exam, if there is only one animal
    return 0;
}

MGraph Graph = CreateGraph(NumVertex);

for(int i=0; i < NumEdge; i++ ){
    Edge E =(Edge)malloc(sizeof(struct ENode));
    scanf("%d %d %d",&(E->V1),&(E->V2),&(E->Weight));
    InsertEdge(Graph, E);
}

//floyd
for(int k=1; k<=NumVertex; k++){
  for(int i=1; i<=NumVertex; i++){
    for(int j=1; j<=NumVertex; j++){
      if(Graph->G[i][j] > (Graph->G[i][k] + Graph->G[k][j])){
        Graph->G[i][j] = Graph->G[i][k] + Graph->G[k][j];
      }
    }
  }
}

int MinofMax[NumVertex];
int Temp;

for(int i=1; i<=NumVertex; i++){
  MinofMax[i]=0;
  for(int j=1; j<=NumVertex; j++){
    if(i != j){
      Temp = Graph->G[i][j];
      if(Temp < FULL && Temp > MinofMax[i]){
          MinofMax[i] = Temp;}
    }
  }
//  printf("Vertex %d has max Length %d\n", i, MinofMax[i]);
}

Temp = MinofMax[1];
int m=1;

for(int n=2; n<=NumVertex; n++){
  if(Temp > MinofMax[n]){
    Temp = MinofMax[n];
    m = n;
//    printf("Update MinOfMax to %d %d\n", m, MinofMax[m]);
  }
}


printf("%d %d\n",m, Temp);
return 0;
}
