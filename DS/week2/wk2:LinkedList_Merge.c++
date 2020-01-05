#include <stdio.h>
#include <stdlib.h>



typedef int ElementType;
typedef struct Node *PtrToNode;

/* Structure of the Node */
struct Node{

    ElementType Value;     /*Save Node Value*/
    PtrToNode Next;       /*Pointer of the next Node*/
};

//typedef PtrToNode List;         /*Define single direction Linked List*/
typedef PtrToNode Position;     /*Pointer of a Node*/

/*--------------------------优雅分割线------------------------------------------*/
/*Node constructor and functions*/
Position createNode( ElementType value){
      Position p = (Position)malloc(sizeof(struct Node));
      p->Value = value;
      p->Next = NULL;
      return p;
}

void AttachNode( ElementType value, Position *pRear){
    Position P = createNode(value);
    (*pRear)->Next = P;   /*Attach the New Node*/
    *pRear = P;         /*Update last node Pointer*/
};

void FreeCurrentNodeSpace( Position *node) {
  Position temp = *node; (*node) = (*node)->Next; //Take the next node to be new hearder
  free(temp);       //clean up the space
}

/*--------------------------优雅分割线------------------------------------------*/
/*Take User input*/
Position Read()
{
  int InputValue[50]={0};
  int n=0;
  while (scanf("%d",&InputValue[n]) != EOF && getchar() != '\n') //循环读入多组整型数据，都以空格分隔。
  n++;

  if(InputValue[0] == -1){
    printf("Empty List\n");       /*Check if the first node is -1, then return NUll*/
    return NULL;
  }

  Position P1 = createNode(0); /*create an empty temperaroy header term*/
  Position temp, rear = P1, L1 = P1;

  for(int i = 0 ; i < n ; i++){    /*last value of -1 is not part of the list*/
    AttachNode(InputValue[i], &rear);
  }

  temp = L1; L1 = L1->Next;   /*remove the empty header term and free space*/
  free(temp);

  return L1;
};

/*--------------------------优雅分割线------------------------------------------*/
/*Display User input*/
void Display(Position L){
if(!L){
  printf("List is empty\n");
  return;
}


while(L){
  printf("%d ",L->Value);
  L = L->Next;
}

printf("\n");

return;
};


/*Merge two List*/
Position Merge(Position L1, Position L2){

    Position t3=createNode(0);
    Position t1 = L1, t2 = L2, *Rear = &t3, L3 = t3, temp;

    if(!t1 || !t2){
      printf("One of the list is empty\n");
      return NULL;
    } //check if any list is empty


    while(t1 && t2){

      if(t1->Value >= t2->Value){
        (*Rear)->Next = t2;     //Attach new node to the t3
        *Rear = t2;             //Update last node Pointer
        t2 = t2->Next;
      }

      if(t1->Value < t2->Value){
        (*Rear)->Next = t1;
        *Rear = t1;
        t1 = t1->Next;
      }
    }         //Meger two list by comparing each values

    while(t1){
      (*Rear)->Next = t1;
      *Rear = t1;
      t1 = t1->Next;
    }         //attach the rest of t1 nodes, if t1 has more values than t2

    while(t2){
      (*Rear)->Next = t2;
      *Rear = t2;
      t2 = t2->Next;
    }        //attach the rest of t2 nodes, if t2 has more values than t1

    FreeCurrentNodeSpace(&L3);  /*remove the empty header term and free space*/
    return L3;

};


/*Main function*/
int main(){

Position l1 = Read();
Position l2 = Read();
Display(l1);
Display(l2);

printf("Merging l1 and l2 \n");

Position l3 = Merge(l1, l2);
Display(l3);

return 0;
}
