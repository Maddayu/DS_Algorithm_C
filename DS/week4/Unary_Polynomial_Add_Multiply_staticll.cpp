#include<stdio.h>
#include<stdlib.h>


typedef struct PolyNode *PtrToNode;
typedef PtrToNode PolyNomial;

struct PolyNode{
    int Cons;
    int Expo;
//    PtrToNode Next;
};   //静态链表

PolyNomial Read(){
    int N, cons, expo;
    scanf("%d", &N);

    if(N == 0 ){    //if PolyNomial has 0 term, return NULL
      return NULL;
    }

    PolyNomial *p = (PtrToNode*)malloc(N*sizeof(PtrToNode));   //initialize an array of pointers to PolyNode
    for(int n=0; n<N; n++){
      p[n] = (PtrToNode)malloc(sizeof(struct PolyNode));      //assign each pointer elemet to an empty polynode
      if(getchar() != '\n'){
        scanf("%d %d", &p[n]->Cons,&p[n]->Expo);
        printf("%d %d\n",p[n]->Cons,p[n]->Expo);
      }
    }


    return p[0];
}










int main(){


PolyNomial p1 = Read();
//PolyNomial p2 = Read();
//Addition();
//Multiplication();





  return 0;
}
