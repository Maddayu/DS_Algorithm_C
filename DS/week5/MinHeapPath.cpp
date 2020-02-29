#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define MinGurdian -10001


typedef struct HeapStruct *MinHeap;
struct HeapStruct{
      ElementType *Elements;
      int CurrentSize;
      int Capacity;
};

MinHeap CreateHeap(int MaxSize){

    MinHeap Emptyheap = (MinHeap)malloc(sizeof(struct HeapStruct));
    Emptyheap->Elements = (ElementType*)malloc((MaxSize+1)*sizeof(ElementType));
    Emptyheap->CurrentSize = 0;
    Emptyheap->Capacity = MaxSize;
    Emptyheap->Elements[0] = MinGurdian;

    return Emptyheap;
}

void Insert( MinHeap H, ElementType item){
    if(H->CurrentSize == H->Capacity){
      printf("The MinHeap is full\n");
      return;
    }

    int i = ++H->CurrentSize;         //i 指向最小堆最后一位
    for( ; H->Elements[i/2] > item; i/= 2){   //向下过滤结点
        H->Elements[i] = H->Elements[i/2];
    }

    H->Elements[i] = item;
    H->CurrentSize++;
}

void PercDown( MinHeap H ,int p){    //下滤： 以H中 H[p] 为根的子堆调整成最小堆
      int parent, child;
      ElementType X;

      ElementType item = H->Elements[p];  //取出根结点存放的值

      for(parent = p; parent*2 <= H->CurrentSize; parent = child){
          child = parent*2;                 //哨兵位置为0； 左子结点位置是偶数，右子结点位置是奇数        i=0 -> i=1; i=2; i=3; i=4; i=5; i=6; i=7;

          if( (child != H->CurrentSize) && (H->Elements[child] > H->Elements[child+1])){
              child++;                      //右结点更小
          }
          if(item <= H->Elements[child]){
              break;        //found place
          }else{
            H->Elements[parent] = H->Elements[child];
          }
      }

      H->Elements[parent] = item;
}

void BuildHeap( MinHeap H ){

    for(int i = H->CurrentSize/2; i > 0; i--){       //从最后一个结点的父节点开始，到根结点1
        PercDown(H, i);
    }
}

void PrintPath( MinHeap H, int p){

    for(int i= p; i > 0; i /=2 ){
      printf("%d ", H->Elements[i]);
    }
    printf("\n");
}


int main(){

int N;
int M;
int temp;


scanf("%d %d", &N, &M);

MinHeap H = CreateHeap(N);

for(int i=1; i<= N; i++){
    scanf("%d", &temp);
    H->Elements[i]= temp;
    H->CurrentSize++;
    BuildHeap(H);
}

//BuildHeap(H);

for(int i=1; i<= N; i++){
    int temp = H->Elements[i];
    printf("%d ", temp);
}

printf("\n");



for(int i=0; i < M; i++){
    scanf("%d", &temp);
    PrintPath(H, temp);
}


  return 0;
}
