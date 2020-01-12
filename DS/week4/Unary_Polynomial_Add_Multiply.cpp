#include<stdio.h>
#include<stdlib.h>


typedef struct PolyNode *PtrToNode;
typedef PtrToNode PolyNomial;

struct PolyNode{      //create a Node struct
    int Cons;
    int Expo;
    PtrToNode Next;
};


PtrToNode create(){                 //create a Node with default values
  PtrToNode PtrN = (PtrToNode)malloc(sizeof(struct PolyNode));
  PtrN->Cons = 0;
  PtrN->Expo = 0;
  PtrN->Next = NULL;
  return PtrN;
}

PolyNomial Read(){                //Enter the number of terms in the PolyNomial
    int N, cons, expo;
    scanf("%d", &N);

    if(N == 0 ){    //if PolyNomial has 0 term, return NULL
      return NULL;
    }

    PtrToNode header = create();  //create an empty header Node

    PtrToNode rear = header;

    for(int n=0; n<N; n++){
      PtrToNode NewNode = create();  //create new node
      if(getchar() != '\n'){
        scanf("%d %d", &NewNode->Cons,&NewNode->Expo);              //assign values to the new NewNode
        rear->Next = NewNode;                                       //linking NewNode
        rear = NewNode;                                             //update tail node
      }
    }

    PtrToNode temp = header;                                          //save the empty header node and free the space
    header = header->Next;                                  //move to the actual header node
    free(temp);
    return header;
}

PolyNomial Copy(PolyNomial original)        //creating sets of clone PolyNodes
{

    if(!original) return NULL;

   PolyNomial p =  original;
   PolyNomial copy = create();                //create a new PolyNode
   PolyNomial head = copy;
   while(p){                                  //check every single Node in the orignial list
   copy->Cons = p->Cons;
   copy->Expo = p->Expo;
   if(!p->Next){copy->Next = NULL;break;}     //If this is the last Node,set Next to be NULL and stop looping
   else{
     copy->Next = create();                   //Create a new empty node as the next to be cloned
     copy = copy->Next;                       //Move rear pointer to the new rear
     p = p->Next;}                            //Move on to the next PolyNode in the orignial list
   }
   return head;
}



void Display(PolyNomial Head){
    PolyNomial temp = Head;     //create a temp pointer so that original head wont be modified.

    if( temp == NULL){
      printf("0 0\n");
      return;
    }

    while(temp->Next != NULL)   // keep printing until hit the last node
    {
      printf("%d %d ", temp->Cons, temp->Expo);
      temp = temp->Next;
    }
    printf("%d %d\n", temp->Cons, temp->Expo);  //print last node without space at the end
}       //This Display function will return a set of integer values,using space as delimiter,
                                      //however wihtout a space character at the end of the output line.

PolyNomial Addition(PolyNomial P1, PolyNomial P2){

  if( !P1 && !P2 ) return NULL;      //Both Input lists are empty, then return NULL

  PolyNomial temp1 = Copy(P1);        //Copy the original Polynomial
  PolyNomial temp2 = Copy(P2);
  PolyNomial P3 =create();            //create a new PolyNode as the header of result Polynomial

  PolyNomial rear = P3;               //Create a rear pointer

  while( temp1 && temp2 ){            //temp1 and temp2 still have terms to be summed

    if(temp1->Expo > temp2->Expo){rear->Next = temp1; temp1= temp1->Next; rear = rear->Next;}
    else if(temp1->Expo < temp2->Expo){rear->Next = temp2; temp2 = temp2->Next; rear = rear->Next;}
    else if(temp1->Expo == temp2->Expo){
      int sum = temp1->Cons + temp2->Cons;     //coefficients summation given same exponetial values
      if(sum != 0){                                  //sum is not 0
        PolyNomial temp = create();             //create a New Polynode after summation
        temp->Cons = sum;
        temp->Expo = temp1->Expo;
        rear->Next = temp;
        rear = rear->Next;

        PolyNomial cleaner = temp1;             //delete the used Node from temp1
        temp1 = temp1->Next;
        free(cleaner);

        cleaner = temp2;                        //delete the used Node from temp2
        temp2 = temp2->Next;
        free(cleaner);
      }else{                                    //if sum is 0
        PolyNomial cleaner = temp1;             //delete both used Nodes directly
        temp1 = temp1->Next;
        free(cleaner);

        cleaner = temp2;
        temp2 = temp2->Next;
        free(cleaner);
      }
    }
  }

  while(temp1){                              //directly copying the remaing terms from temp1, if temp2 is empty
    rear->Next = temp1;
    rear = rear->Next;
    temp1= temp1->Next;
  }
  while(temp2){                               //directly copying the remaing terms from temp2, if temp1 is empty
    rear->Next = temp2;
    rear = rear->Next;
    temp2= temp2->Next;
  }

  PolyNomial janitor = P3;
  P3 = P3->Next;
  free(janitor);

  return P3;

}         //desceding coefficients

PolyNomial Multiplication(PolyNomial P1, PolyNomial P2){

  PolyNomial temp1 = Copy(P1);
  PolyNomial temp2 = Copy(P2);
  PolyNomial P3 = NULL;


  if( !temp1 || !temp2 ) return NULL;

  PolyNomial temp2_header = temp2;

  while(temp1){
    PolyNomial head = create();
    PolyNomial rear = head;
    temp2 = temp2_header;   //startover with temp2

    while(temp2){
      PolyNomial P4 = create();
      P4->Cons = temp1->Cons * temp2->Cons;
      P4->Expo = temp1->Expo + temp2->Expo;
      rear->Next = P4;
      rear = P4;
      temp2 = temp2->Next;    //move on to the next Node in temp2
    }

    head = head->Next;        //move to the actual header node
    P3 = Addition(P3, head);
    temp1 = temp1->Next;        //move on to the next Node in temp1

  }

  return P3;
}






int main(){


PolyNomial p1 = Read();
PolyNomial p2 = Read();
PolyNomial p3 = Addition(p1,p2);
PolyNomial p4= Multiplication(p1,p2);
Display(p4);
Display(p3);




  return 0;
}
