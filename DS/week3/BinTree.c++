#include<stdio.h>


typedef struct TNode *Position
typedef Position BinTree
typedef int ElementType;

struct TNode{
      ElementType value;
      BinTree Left;
      BinTree Right;
}
