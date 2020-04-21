#include<stdio.h>
#include<stdlib.h>


#define MaxTree 10
#define Tree int
#define Null -1

//---------------------------------------------
//typedef struct TreeNode *Position;
//typedef Position BinTree;

struct TreeNode{
    //Tree Element;
    Tree Left;
    Tree Right;

}T1[MaxTree];

Tree TreeBuilder(struct TreeNode T[], int n){

    int Check[MaxTree]={0};
    char Nl, Nr;
    char c;
    Tree Root = Null;

    //printf("Please Enter the tree \n");
    int N = n;

    if(N){
      int i;
            //for(i=0; i<N; i++) Check[i] = 0;
      for(i=0; i<N; i++){
        scanf("\n%c %c", &Nl, &Nr);  // scanf will use \n as a pause until it found non-spacing character
        if(Nl != '-'){
          T[i].Left = Nl-'0';     //Cast char type to be int by - '0'
          Check[T[i].Left] = 1;
        }else{
          T[i].Left = Null;
        }

        if(Nr != '-'){
          T[i].Right = Nr-'0';     //Cast char type to be int by - '0'
          Check[T[i].Right] = 1;
        }else{
          T[i].Right = Null;
        }
      }

      for(i=0; i<N; i++) {

        if(!Check[i]) break;
      }

      Root = i;
    }


    return Root;

}


//---------------------------------------------
typedef struct Queue *QPointer;
typedef QPointer PtrQ;

struct Queue{

    int Front, Rear, CurrentSize;
    unsigned Capacity;
    Tree* array;
};
//---------------------------------------------
PtrQ CreateQueue(unsigned capacity){

      PtrQ Q =(PtrQ)malloc(sizeof(struct Queue));
      Q->Capacity = capacity;
      Q->Front = Q->CurrentSize = 0;
      Q->Rear = capacity - 1;
      Q->array =(Tree*)malloc(capacity*sizeof(Tree));
      return Q;
}

int IsFull(PtrQ q){
      return (q->CurrentSize == q->Capacity);}

int IsEmpty(PtrQ q){
      return (q->CurrentSize == 0);}

void Enqueue(PtrQ q, Tree t){

      if(IsFull(q)) {
        printf("Queue is full\n");
        return;
      }
      (q->CurrentSize)++;
      q->Rear = (q->Rear + 1)%q->Capacity;
      q->array[q->Rear] = t;
}

Tree Dequeue(PtrQ q){

      if(IsEmpty(q)){
        printf("Queue is empty\n");
        return NULL;
      }
      (q->CurrentSize)--;
      Tree t= q->array[q->Front];
      q->Front = (q->Front + 1)%(q->Capacity);
      return t;
}
//---------------------------------------------


//----------------------------------------------
int main(){

  int N;
  Tree front;
  Tree Root;
  scanf("%d", &N);

  Root = TreeBuilder(T1, N);
  PtrQ q = CreateQueue(N);

  Enqueue(q,Root);
  int leaves[N];
  int i = 0;

  while(!IsEmpty(q)){

    front = Dequeue(q);
    if( (T1[front].Left == Null) && (T1[front].Right == Null) ){
      leaves[i]=front;
      i++;
    }

    if(T1[front].Left!=Null){
      Enqueue(q,T1[front].Left);
    }

    if(T1[front].Right!=-1){
      Enqueue(q,T1[front].Right);
    }
  }

  printf("%d",leaves[0]);
  for(int j = 1; j < i; j++){
    printf(" %d",leaves[j]);
  }


  return 0;
}
