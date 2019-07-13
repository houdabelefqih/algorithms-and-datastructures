/*
*
* To compile : gcc -o med3QS median3_quick_sort.c
* To run with data file : med3QS < student_tests.txt
*
*/


#include <stdio.h>
#include <stdlib.h>

struct arrays_Quicksort
{
   int sizeOfArray;
   int* data_array;

};

void Quick_Sort(int* A, int sizeOfArray, int startIndex, int endIndex);
int Partition(int* A,int sizeOfArray, int startIndex, int endIndex);
void print_array(int* A, int sizeOfArray, int start_i, int end_i);
int get_median(int* A, int start_i, int end_i);


int main()
{
   struct arrays_Quicksort arrays_QS[3000];
   int infinite_loop_exec = 0; //to count each time we enter the while loop
   int i=0;
   int sizeOfarray=0;
   int element =0;

     while (1==1)
      {
        //scan size of array
        scanf("%d", &sizeOfarray);

        if(sizeOfarray == -1){break;}

         //put the scanned size in structure and allocate memory for the array accordingly
         arrays_QS[infinite_loop_exec].sizeOfArray = sizeOfarray;
         arrays_QS[infinite_loop_exec].data_array = malloc(sizeOfarray * sizeof(int));
         //ok

         //scan element fill the allocated array with them
            for (i=0; i<sizeOfarray; i++)
               {
                 scanf("%d", &element);
                 arrays_QS[infinite_loop_exec].data_array[i] = element;
               }

         infinite_loop_exec ++;

     }//end infinite while loop

   for (i=0; i< infinite_loop_exec; i++)
   {
      //Calling QuickSort for each of the arrays scanned
      printf("\nARRAY %d:\n\n", i+1);

      if (arrays_QS[i].sizeOfArray==0)
      {
         printf ("Array is empty\n");
         printf("\n______________________________________________\n");
         continue;
      }

      if (arrays_QS[i].sizeOfArray==1)
      {
         printf ("Array is one element only : %d \n", arrays_QS[i].data_array[0]);
         printf("\n______________________________________________\n");
         continue;
      }


      Quick_Sort(arrays_QS[i].data_array,
                 arrays_QS[i].sizeOfArray,
                 0, arrays_QS[i].sizeOfArray -1);

      printf("\nSorted array : \n");
      //printing sorted aray
      print_array(arrays_QS[i].data_array,
                  arrays_QS[i].sizeOfArray,
                   0, arrays_QS[i].sizeOfArray -1);
      printf("\n______________________________________________\n");
   }

   //Freeing arrays
   for (i=0; i< infinite_loop_exec; i++)
   {
      free(arrays_QS[i].data_array);
   }

}//end main

void Quick_Sort(int* A, int sizeOfArray, int startIndex, int endIndex)
{
   if (startIndex < endIndex)
   {
      //partition will return the index at which the pivot is currently at
      int pivot_atIndex = Partition(A, sizeOfArray, startIndex, endIndex);

      Quick_Sort(A, sizeOfArray, startIndex, pivot_atIndex-1);//sort left of the pivot
      Quick_Sort(A, sizeOfArray, pivot_atIndex+1, endIndex);//sort right of the pivot

   }
}

int Partition(int* A, int sizeOfArray, int startIndex, int endIndex)
{
   int i = startIndex -1, j, temp;
   //print original array + elements considered for the median
   print_array(A,sizeOfArray, startIndex, endIndex);
   printf("%6c %d, %d, %d",' ', A[startIndex], A[(startIndex+endIndex)/2],A[endIndex]);

   int pivot_index = get_median(A, startIndex, endIndex);

   //swapping last element in array with median
   temp = A[pivot_index];
   A[pivot_index]= A[endIndex];
   A[endIndex]= temp;

   //printing array after putting median in last index
   printf("\n");
   print_array(A, sizeOfArray, startIndex, endIndex);

   //Actual sorting
   int pivot = A[endIndex];

   for(j=startIndex; j< endIndex; j++)
         {
            if (A[j]<= pivot)
            {
               //swapping plus incrementing index i
               i++;
               temp = A[j];
               A[j]= A[i];
               A[i]= temp;
            }
         }

      temp = A[i+1];
      A[i+1] = A[endIndex];
      A[endIndex] = temp;

      printf("\n");
      print_array(A, sizeOfArray, startIndex, endIndex);
      printf("\n");

  return i+1;
}

//Function to print the arrays
void print_array(int* A,int sizeOfArray, int start_i, int end_i)
{
   int i=0;

   for (i=0; i<start_i; i++)
   {
      printf("%5c",' ');
   }

   for (i=start_i; i<=end_i; i++)
   {
      printf("%*d,", 4, A[i]);
   }

   for(i=end_i+1; i< sizeOfArray; i++)
   {
       printf("%5c",' ');
   }


}

//Function to calculate the median of 3 numbers
int get_median(int* A, int start_i, int end_i)
{
   if ((A[start_i]-A[(start_i+end_i)/2])* (A[(start_i+end_i)/2]-A[end_i]) >= 0)
      return (start_i+end_i)/2;

   if ((A[start_i]-A[(start_i+end_i)/2])* (A[start_i]-A[end_i]) >= 0)
      return end_i;

   return start_i;

}




