#include<stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

//typedef struct TreeNode ;
struct TreeNode{
    ElementType Element;
    Tree Left;
    Tree Right;

}T1[MaxTree], T2[MaxTree];

Tree TreeBuilder(struct TreeNode T[]){

    int N;
    int Check[MaxTree]={0};
    char Nl, Nr;
    char c;
    Tree Root = Null;

    //printf("Please Enter the tree \n");
    scanf("%d", &N);

    if(N){
      int i;
            //for(i=0; i<N; i++) Check[i] = 0;
      for(i=0; i<N; i++){
        scanf("\n%c %c %c", &(T[i].Element), &Nl, &Nr);  // scanf will use \n as a pause until it found non-spacing character
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
//        printf("root is %d\n", i);
        if(!Check[i]) break;
      }

      Root = i;
    }


    return Root;

}


bool Isomorphic( Tree r1, Tree r2 ){

    //two empty Trees
    if( (r1 == Null)&&(r2 == Null) ) return true;

    //one Tree is empty
    if( ((r1 != Null)&&(r2 == Null)) || ((r1 == Null)&&(r2 != Null)) ) return false;

    //roots are different
    if( ((T1[r1].Element != T2[r2].Element ))) return false;

    //both have no left subtree, check right subtrees
    if( ((T1[r1].Left == Null) && (T2[r2].Left == Null)) )  return Isomorphic( T1[r1].Right, T2[r2].Right);

    //both left nodes match, no need to swap
    if(  ((T1[r1].Left != Null)&&(T2[r2].Left != Null)) && (T1[T1[r1].Left].Element == T2[T2[r2].Left].Element)){
       return ( Isomorphic( T1[r1].Left, T2[r2].Left) && Isomorphic( T1[r1].Right, T2[r2].Right) );
    }

    //need to swap the left and the right
    else{
      return ( Isomorphic( T1[r1].Right, T2[r2].Left) && Isomorphic( T1[r1].Left, T2[r2].Right) );
    }

}



int main()
{

  Tree R1, R2;

  R1 = TreeBuilder(T1);     //Build Tree1
  R2 = TreeBuilder(T2);    //Build Tree2

//  printf("r1 = %d\n", R1);
//  printf("r2 = %d\n", R2);
  //Check if Tree1 and Tree2 are isomorphic
  if(Isomorphic(R1,R2)) printf("\nYes \n");
  else printf("\nNo \n");

  return 0;


}
