#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */

BinTree CreatBinTree(){

    BinTree result =(BinTree)malloc(sizeof(TNode));

    BinTree TreeArray[9] = {result};  //9 TreeNodes

/*    for(int i=0; i<9; i++){
      TreeArray[i]=(BinTree)malloc(sizeof(TNode));
    }
*/


    TreeArray[8]->Data = 'H';
    TreeArray[8]->Left = NULL;
    TreeArray[8]->Right = NULL;

    TreeArray[7]->Data = 'E';
    TreeArray[7]->Left = NULL;
    TreeArray[7]->Right = NULL;

    //printf("lala\n");

    TreeArray[6]->Data = 'I';
    TreeArray[6]->Left = NULL;
    TreeArray[6]->Right = NULL;

    TreeArray[5]->Data = 'H';
    TreeArray[5]->Left = NULL;
    TreeArray[5]->Right = TreeArray[8];

    TreeArray[4]->Data = 'F';
    TreeArray[4]->Left = TreeArray[7];
    TreeArray[4]->Right = NULL;

    TreeArray[3]->Data = 'D';
    TreeArray[3]->Left = NULL;
    TreeArray[3]->Right = NULL;

    TreeArray[2]->Data = 'C';
    TreeArray[2]->Left = TreeArray[5];
    TreeArray[2]->Right = TreeArray[6];

    TreeArray[1]->Data = 'B';
    TreeArray[1]->Left = TreeArray[3];
    TreeArray[1]->Right = TreeArray[4];

    TreeArray[0]->Data = 'A';
    TreeArray[0]->Left = TreeArray[1];
    TreeArray[0]->Right = TreeArray[2];

    // BinTree result =(BinTree)malloc(sizeof(TNode));
  /*  result->Data = 'A';
    result->Left = NULL;
    result->Right = NULL; */
/*
    BinTree TA = (BinTree)malloc(sizeof(TNode));
    BinTree TB = (BinTree)malloc(sizeof(TNode));
    BinTree TC = (BinTree)malloc(sizeof(TNode));
    BinTree TD = (BinTree)malloc(sizeof(TNode));
    BinTree TE = (BinTree)malloc(sizeof(TNode));
    BinTree TF = (BinTree)malloc(sizeof(TNode));
    BinTree TG = (BinTree)malloc(sizeof(TNode));
    BinTree TH = (BinTree)malloc(sizeof(TNode));
    BinTree TI = (BinTree)malloc(sizeof(TNode));

    TA->Data = 'A';TA->Left = TB; TA->Right = TC;
    TB->Data = 'B';TB->Left = TD; TB->Right = TF;
    TC->Data = 'C';TC->Left = TG; TC->Right = TI;
    TD->Data = 'D';TD->Left = NULL; TD->Right = NULL;
    TF->Data = 'F';TF->Left = TE; TF->Right = NULL;
    TG->Data = 'G';TG->Left = NULL; TG->Right = TH;
    TI->Data = 'I';TI->Left = NULL; TI->Right = NULL;
    TE->Data = 'E';TE->Left = NULL; TE->Right = NULL;
    TH->Data = 'H';TH->Left = NULL; TH->Right = NULL;
*/
    return TreeArray[0];
}

void InorderTraversal( BinTree BT ){
  if(BT){
    InorderTraversal(BT->Left);
    printf(" %c",BT->Data);
    InorderTraversal(BT->Right);
    }
}

void PostorderTraversal( BinTree BT ){
  if(BT){
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf(" %c",BT->Data);
    }
}

void PreorderTraversal( BinTree BT ){
  if(BT){
    printf(" %c",BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
    }
}

typedef struct Queue *QPtr;
typedef QPtr PtrQ;
struct Queue{
      int Front, Rear, CurrentSize, Capacity;
      BinTree *TreeArray;
};

PtrQ CreateQueue(){
     PtrQ Q =(struct Queue*)malloc(sizeof(struct Queue));
     Q->Front = 0;
     Q->CurrentSize = 0;
     Q->Capacity = 9;
     Q->Rear = 0;    //UpperIndex = capacity - 1
     Q->TreeArray =(BinTree*)malloc(((int)sizeof(BinTree))*10);
     return Q;
}

int IssFull(PtrQ Q){
    if( Q->CurrentSize == Q->Capacity){return 1;}
    return 0;
}

int IssEmpty(PtrQ Q){
    if( Q->CurrentSize == 0 ){return 1;}
    return 0;
}

void Enqueue(PtrQ Q, BinTree BT){

    if(!IssFull(Q)){
      Q->TreeArray[Q->Rear] = BT;
      Q->Rear = (Q->Rear + 1)%Q->Capacity;
      (Q->CurrentSize)++;
    }

}

BinTree Dequeue(PtrQ Q){

     if(!IssEmpty(Q)){
       BinTree BT = Q->TreeArray[Q->Front];
       Q->Front = (Q->Front + 1)%Q->Capacity;
       (Q->CurrentSize)--;
       return BT;
     }

     return NULL;
}


void LevelorderTraversal( BinTree BT ){


      BinTree reader;
      ElementType symbol;

      struct Queue *ptrQ = CreateQueue();
      Enqueue(ptrQ, BT);

      while(!IssEmpty(ptrQ)){

        reader = Dequeue(ptrQ);
        symbol = reader->Data;
        printf(" %c",symbol);

        if(reader->Left!=NULL){
          Enqueue(ptrQ, reader->Left);
        }

        if(reader->Right!=NULL){
          Enqueue(ptrQ, reader->Right);
        }

      }



}
