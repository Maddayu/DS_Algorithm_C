#include<stdio.h>
#include<stdlib.h>
#define ElementType int

int NotEqualSign = 0; //define a global variable

typedef struct TreeNode *TNodePtr;
typedef TNodePtr BST;

struct TreeNode{
  ElementType Value;
  BST Left;
  BST Right;
};


TNodePtr CreateTNode(ElementType value){
  TNodePtr TNode = (TNodePtr)malloc(sizeof(struct TreeNode));
  TNode->Value = value;
  TNode->Left = NULL;
  TNode->Right = NULL;
  return TNode;
}

TNodePtr InsertTNode(TNodePtr root, ElementType x){
    if(!x) return root;     //if Element is 0, return root without change

    if(!root){      //if root is null, newNode is the root
       TNodePtr newNode = CreateTNode(x);
       return newNode;
    }else{
      if(root->Value > x){
         root->Left = InsertTNode(root->Left, x);
      }
      else if(root->Value < x){
         root->Right = InsertTNode(root->Right, x);
      }
      //else root and newNode are the same, no need to insert newNode
    }

    return root;

}

BST BuildBST(int dataset[], int size){
    if(!dataset[0]){return NULL;}

    BST Root = CreateTNode(dataset[0]);

    for(int i=1; i < size; i++){
      if(!dataset[i]){      //stop inserting once found a zero node
        break;
      }else{
        Root = InsertTNode(Root, dataset[i]);
      }
    }

    return Root;
}

//----------------------------------Compare BSTs--------------------------------
void NotEqualBSTs(BST r1, BST r2){

    if(NotEqualSign == 0){

      if(!r1 || !r2){
        if(!r1 && !r2);                 //consider two empty BST as same, but do nothing until we checked all nodes
        else{printf("No\n");            //one BST is empty, not the same
        NotEqualSign = 1;               //Enable Inidicator, comparision is done
        }
        return;
      }
      else{    //Both are not empty
        if(r1->Value != r2->Value){     //TreeNodes for comparision found not same
          printf("No\n");
          NotEqualSign = 1;                //Enable Inidicator, comparision is done
          return;
        }else{
            NotEqualBSTs(r1->Left,r2->Left);
            NotEqualBSTs(r1->Right,r2->Right);
          }
        }
      }
  }

int main(){


  int N, L ;
  int InputValue[10]={0};
  NotEqualSign = 0;

   while(true){
     scanf("%d", &N);        //Enter N value
     if(N){                  //N != 0
       scanf("%d", &L);      //Enter L value

       BST r[L+1];          //Create an array of BST with size of L+1 (orginal + to be checked)
       for(int j=0; j<L+1; j++){
         for(int i =0; i < N; i++){
           scanf("%d",&InputValue[i]);
         }
         r[j] = BuildBST(InputValue, N);
       }

       for(int j=1; j<L+1; j++){
         NotEqualSign = 0;  //reset NotEqual Inidicator
         NotEqualBSTs(r[0],r[j]);
         if(NotEqualSign == 0){   //if Not NotEqual, then two BSTs are the same;
           printf("Yes\n");
         }
       }

     }
     else{                   //get N  = 0
       break;                //breka while loop and program completes
     }
   }

  return 0;
}
