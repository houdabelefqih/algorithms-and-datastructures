/* compile : gcc -o hw4 hw4_a.c
*  run : ./hw4
*/

#include <stdio.h>
#include <stdlib.h>

int foo(int N);
int foo_helper(int N, int sol[N]);
int foo2(int* arr, int N);
void foo2_helper(int* arr,int N, int* sol);



int main()
{
   printf("For example : foo(6) : %d \n \n", foo(6));

   int data0[] = {3,6,1,8};

   int data1[] = {3, 6, 8, 50, 10000};
   int data2[] = {20,16, 9, 7, 3};
   int data3[] = {20,6,-1,-5};
   int data4[] = {4};


   int res = foo2(data0,sizeof(data0)/sizeof(data0[0]));
   printf("Result for array {3,6,1,8} : \n%d\n\n",res);

    res = foo2(data1,sizeof(data1)/sizeof(data1[0]));
   printf("Result for array {3, 6, 8, 50, 10000} : \n%d\n\n",res);

    res = foo2(data2,sizeof(data2)/sizeof(data2[0]));
   printf("Result for array {20,16, 9, 7, 3} : \n%d\n\n",res);

    res = foo2(data3,sizeof(data3)/sizeof(data3[0]));
   printf("Result for array {20,6,-1,-5}: \n%d\n\n",res);

    res = foo2(data4,sizeof(data4)/sizeof(data4[0]));
   printf("Result for array with one element= {4}: \n%d\n\n",res);

    return 0;
}


/* __________________________________FUNCTIONS FOR TASK 3________________________________*/

int foo(int N)
{  int sol[N];
   int j =0;
   for (j=0; j<N; j++)
   {
      sol[j] = -1;
   }

   return foo_helper( N, sol);
}

//helper
int foo_helper(int N, int sol[N]){
    if(sol[N-1]!= -1)
    {return sol[N];}

    if (N <= 1) return 5;
    int final_res;
    int res1 = 3*foo_helper(N/2, sol);
    sol[N-1]= res1;
    int res2 = foo_helper(N-1, sol);
    sol[N-1]= res2;

    if (res1 >= res2)
      {
         final_res= res1;
      }

    else
    {
      final_res =res2;
    }

    sol[N-1]= final_res;

    return final_res;
}


/* __________________________________FUNCTIONS FOR TASK 4________________________________*/


int foo2(int* arr, int N) //θ(N)
{
   int sol[N];
   int j =0;
   int desc=0;
   int asc=0;

   //initialize
   for (j=0; j<N; j++) //will run N times
   {sol[j] = -1;}

   //call helper
   foo2_helper(arr,N,sol); //will run O(N)

   if (N==1 || arr == NULL)
      return 1;

   for (j=1; j<N; j++)//will run N times
   {
      //count number of zeros
      if (sol[j]==0)
      {desc++;}

      //count number of ones
      if (sol[j]==1)
      {
       asc++;
      }
   }

   //if at all indexes we have the same value
   if (asc== N-1 || desc== N-1)
      return 1;

   //if not
   else
      return 0;

}

//Check recursively if array is sorted, store result in sol array
void foo2_helper(int* arr,int N, int* sol)
   {

      if (N==1)
         {sol[N-1]=1;
            return;}

      if (arr[N-2]< arr[N-1])
         {sol[N-1] = 1;}

      if (arr[N-2]>= arr[N-1])
         {sol[N-1] = 0;}

     foo2_helper(arr, N-1, sol);

     /*
         Recursion formula :
            T(N) = T(N-1) + constant

      */


   }
