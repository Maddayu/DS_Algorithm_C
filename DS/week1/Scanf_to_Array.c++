#include <stdio.h>


   int main()
{
  /*
    int arr[100] = {0};
    int numdoll = 0;
    while (scanf("%d",&arr[numdoll]) != EOF && getchar() != '\n') //循环读入多组整型数据，都以空格分隔。
    numdoll++;

    for(int i = 0; i < numdoll+1; i++)
    printf("%d ", arr[i]);
    return 0;

    */


    int N,c,e;
    int Array[20][2];

    scanf("%d", &N);

    int i = 0;

    while( N--){
      scanf("%d %d", &c, &e);
      Array[i][0] = c;
      Array[i][1] = e;
      i++;
    }

    for(int j = 0; j < i; j++){
    printf("%d %d ", Array[j][0], Array[j][1]);
    }


    return 0;



}
