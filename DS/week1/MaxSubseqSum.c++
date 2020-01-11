/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <functional>


// Passing interger Array "A[]" to the fucntion "func", matching the "Timer( Array, size )" at main function.
int Timer(int A[], int N, int j,std::function<int (int[] , int)> func)
{
	clock_t start_t, end_t;
	double total_t;
	int max;

	for(int i = 0; i < j; i++ )
	{
    //Start the timer
	start_t = clock();

	//Run the function with two arguments
	max = func( A, N);

	//Stop the timer
	end_t = clock();

	//Calculate the duration of time elapsing
	total_t += (double)(end_t - start_t);
	}

	total_t = total_t / CLOCKS_PER_SEC;
	//printf("The running time is %f \n", total_t);


	return max;
}

//Brutal force method, loop through all of the subarrays to calculate the maxSum
int MaxSubseqSum1( int A[], int N )
{
	int ThisSum, MaxSum = 0;
	int i, j, k;
	for( i = 0; i < N; i++){         //Lower boundary i
		for( j = i; j < N; j++ ){         //Upper boundary j
			ThisSum = 0;
			for( k = i; k <= j; k++){          //Calculate the subsequence sum between A[i] and A[j]
			ThisSum += A[k];
			}
			if( ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
    return MaxSum;
}
//T[N] = O[N^3]


int MaxSubseqSum2( int A[], int N )
{
	int ThisSum, MaxSum = 0;
	int i, j, k;
	for( i = 0; i < N; i++){
		ThisSum = 0;
		for( j = i; j < N; j++ ){
			ThisSum += A[j];              //Given the lower boundary i, calculate the subsequence sum by adding the A[j] to the previous sum.
			if( ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
    return MaxSum;
}
//T[N] = O[N^2]


//Divide-and-Conquer
int Max3(int A, int B, int C){

	return A > B ? A > C ? A : C : B > C ? B : C;

}

int DivideAndConquer( int A[], int left, int right )
{
	int LeftMax, RightMax, BoundaryLeftMax = 0, BoundaryRightMax = 0;

    //Only one item in the subset
	if( left == right ){

		return A[left];

	}

	//Divide the set
	int center = ( left + right ) / 2;
    int i ;

	//Conquer the subset
	LeftMax = DivideAndConquer(A, left, center );
	RightMax = DivideAndConquer(A, center + 1, right );



	//Find the left Max Across Boundary (from center to left)
	int BoundaryLeftSum = 0;
	for( i = center; i >= left; i-- ){

		BoundaryLeftSum += A[i];

		if(BoundaryLeftSum > BoundaryLeftMax){
			BoundaryLeftMax = BoundaryLeftSum;
		}

	}




	//Find the right Max Across Boundary (from center to right)
	int BoundaryRightSum = 0;
	for( i = center + 1; i <= right; i++ ){

		BoundaryRightSum += A[i];

		if(BoundaryRightSum > BoundaryRightMax){
			BoundaryRightMax = BoundaryRightSum;
		}

	}

	return Max3(LeftMax, RightMax, BoundaryLeftMax + BoundaryRightMax);

}

int MaxSubseqSum3 (int A[], int N )
{
	if ( N < 1 ){

	 return -1;           //No value in the Arrary.

	 }

	return DivideAndConquer(A, 0, N - 1 );

}
/*T[N] = O[NlogN]
T(N) = 2T(N/2) + cN, T(1) = O(1)
     = 2[2T(N/2^2) + cN/2] + cN
     = 2^k O(1) + ckN   where N/(2^k) = 1 or k = log(2)N
     = O(NlogN)
*/

//online processing
int MaxSubseqSum4 (int A[], int N){

		int ThisSum= 0, MaxSum= 0;
		int tip=0, tail=0;
		int counter= 0, distance= 0;
		int allneg = 1, j=0;

    for(int i= 0; i< N; i++){
				if(A[i]>=0){
					allneg = 0;
					break;
				}
		}


		if(!allneg){
			for (int i = 0; i < N; i++ ){
				ThisSum += A[i];  /*cumulating values from left to right*/
				counter++;
				if(ThisSum > MaxSum){   /*Update the maximum sum*/
					MaxSum = ThisSum;
					tail = A[i];
					distance = i - counter + 1;
					tip = A[distance];
				}
				else if(ThisSum < 0){		/*Adding the right value will result in a negative sum value  */
					ThisSum = 0;					/*Can't have a bigger sum by adding the A[i], then start over from A[i+1]*/
					counter = 0;
				}

			}
		}else{
			MaxSum = A[0];
			for (int i = 0; i < N; i++ ){
				if(A[i] >= MaxSum ){
					MaxSum = A[i];
					tip = A[i];
					tail = A[i];
					}
				}
			}

			printf("%d %d %d\n",MaxSum, tip, tail);
			return MaxSum ;
}




int main(void)
{
	int i, size, result1, result2, result3, result4;
  int iteration = 10000;

	//printf("Enter the number of the array:\n");
	scanf("%d", &size);

  int Array[size];
  //printf("Enter the array:\n");
	for (i=0; i < size; i++)
	scanf("%d" , &Array[i]);  //Scanf %d requires the address of an integer variable to pass the entered value

//	result1 = Timer( Array, size, iteration, MaxSubseqSum1);
//  result2 = Timer( Array, size, iteration, MaxSubseqSum2);
//	result3 = Timer( Array, size, iteration, MaxSubseqSum3);
//	result4 = Timer( Array, size, iteration, MaxSubseqSum4);

//	printf("the result1 is %d\n", result1);   //Prinf %d requires the value of an integer
//	printf("the result2 is %d\n", result2);   //Prinf %d requires the value of an integer
//	printf("the result3 is %d\n", result3);   //Prinf %d requires the value of an integer
//  printf("the result4 is %d\n", result4);   //Prinf %d requires the value of an integer

	int result = MaxSubseqSum4(Array, size);

	return 0;

}
