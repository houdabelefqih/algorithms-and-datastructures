/*
Skeleton of Graycode from :
http://www.geeksforgeeks.org/given-a-number-n-generate-bit-patterns-from-0-to-2n-1-so-thatsuccessive-patterns-differ-by-one-bit/

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "perm.h"


void perm_helper(int position, int nr_vals, int* values, int current);
void perm2_helper(int N, int nr_vals,int * arr2, matrix_ptr mat ,int current_i, int current_j);

// Prints the 2D data.
void print_2D(matrix_ptr mat){
    int i, j;
    if (mat == NULL || mat->data_arr == NULL) {
        return;
    }

    printf("\nrows = %d, columns = %d\n", mat->rows, mat->cols);
    int ct = 0;
    for(i = 0; i < mat->rows; i++){
        for(j = 0; j < mat->cols; j++, ct++) {
            printf("%5d", mat->data_arr[i][j] );
        }
        printf("\n");
    }
}

// Prints the 2D data. Ignores -1: prints empty space instead of -1.
// This will make it show the constructed part of the Gray code.
void print_Gray_2D(matrix_ptr mat, int nr_rows){
    int i, j;
    if (mat == NULL || mat->data_arr == NULL) {
        return;
    }

    printf("\nrows = %d\n", nr_rows);
    int ct = 0;
    for(i = 0; i < nr_rows; i++){
        for(j = 0; j < mat->cols; j++, ct++) {
			if (mat->data_arr[i][j] != -1)
				printf("%1d", mat->data_arr[i][j] );
			else
				printf("%1s", " " );
        }
        printf("\n");
    }
}



// Implement the functions below.
// You can add any helper function you need.


// Use this method to create and run any tests you want. It is called from main so
// you do can still test your code, without modifying main.
void student_tests(){
	printf("\n------------------------------------------\n");
	printf("Tests for Task1 :recursive reverse method");
	printf("\n-----------------------------------------\n");

	printf("\nIf the string is empty : \n\n");
	char str1 []= "";
	printf("Original string :%s\n", str1);
	reverse_str(str1, sizeof(str1));
	printf("Reversed string :%s\n", str1);

   printf("\nIf the string is only one character : \n\n");
   char str2[]= {'N'};
   printf("Original string :%s\n", str2);
	reverse_str(str2, sizeof(str2));
	printf("Reversed string :%s\n", str2);

   printf("\nFor a whole sentence : \n\n");
   char str3[]=
   {'I',' ','s','c','r','e','a','m',',','y','o',
   'u',' ','s','c','r','e','a','m',',',' ','w','e',' ','a','l','l',' ',
   's','c','r','e','a','m',' ','f','o','r',' ','i','c','e','c','r','e','a','m','\0'};
   printf("Original string :%s\n",str3);
	reverse_str(str3, sizeof(str3)-1);
	printf("Reversed string :%s\n", str3);


   printf("\n------------------------------------------\n");
	printf("Tests for Task2 :GRAY CODE");
	printf("\n-----------------------------------------\n");

   printf("\n Gray code for N = 1: ");
	Gray_code(1);
   printf("\n Gray code for N = 2: ");
	Gray_code(2);
	printf("\n Gray code for N = 5: ");
   Gray_code(5);

   //uncomment for tests for bigger N

   /*
   printf("\n Gray code for N = 6: ");
   Gray_code(6);
   printf("\n Gray code for N = 10: ");
   Gray_code(10);
   */

    int N = 3;
    int nr_vals = 3;


    printf("\nIn Main, called : perm_rec_2(%d, %d);\n", N, nr_vals);
    matrix_ptr res = perm_rec_2(N, nr_vals);
    print_2D(res);
    free_matrix_ptr(res);
    free(res);

}


/* Recursive function that reverses the string str.
 * N is the length of the string.
 */
void reverse_str(char * str, int N)
{
   char temp =' ';
   //Because we won't be flipping the last character \0,the actual size of the array
   //we are going to process will be N-1
   int n = N-1;

   if (n <= 1)
      return;

   //swapping elements
   temp = str[0];
   str[0] = str[n];
   str[n] = temp;

    //the pointer str moves to the next position in the array
    reverse_str(str +1 , n - 1);

}


// Time complexity: O(N�*(2^N))
void Gray_code(int N){

   int rows = pow(2,N);
   int cols = N;
   int i,j,k;
	int **data;

	//allocating necessary space for pointers
   data = (int **)malloc(rows * sizeof(int *));
   for (i = 0; i < rows; i++)//this will run 2^N times
    data[i] = malloc(cols * sizeof(*(data[i])));

   matrix_ptr matriX = (matrix_ptr) malloc(sizeof (struct matrix_2D_struct));

  //The loop for filling the matrix with -1 as an initialization step
   for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {

        data[i][j] = -1; //This will run rows*cols times i.e N*2^N times
    }
}

   matriX->rows = rows;
   matriX->cols = cols;
   matriX->data_arr= data;


   matriX->data_arr[0][N-1]=0;
   matriX->data_arr[1][N-1]=1;

   if (N==1)
   {
      print_Gray_2D(matriX, rows);
   }



for (i = 2; i < rows; i = i*2)
{
      for (k=0;k <(log(i)/log(2)) ;k++) //1 + 2 + 3+ ..+ N-1 = N(N-1)/2 = O(N�)
         {
            for (j = i-1 ; j >= 0; j--)
               matriX->data_arr[2*i-j-1][(cols-1)-k]= matriX->data_arr[j][(cols-1)-k];// N(N-1)/2 *(2+4+8+...+2^(N-1)) = O(N�)*O(2^N)
         }

        // append 0 to the first half
        for (j = 0 ; j < i ; j++)
            matriX->data_arr[j][(cols-1)-k] = 0; // 2+4+8+...+2^(N-1) = O(2^N)

        // append 1 to the second half
        for (j = i ; j < 2*i ; j++)
           {
            matriX->data_arr[j][(cols-1)-k] = 1;   //2+4+8+...+2^(N-1) = O(2^N)

           }

   print_Gray_2D(matriX, j);//This will run : lg(N-1)*rows*cols times = N * 2^N *lg(N-1)

}

free_matrix_ptr(matriX);//O(2^N)
free(matriX);
}

//  Time complexity: O(2^N)
void free_matrix_ptr(matrix_ptr my_matrix){

   if (my_matrix == NULL || my_matrix->data_arr == NULL)
      {
        return;
      }
   int i=0;
   int r = my_matrix->rows;

   if (my_matrix->data_arr == NULL || my_matrix ==NULL)
        return;


  for (i=0; i<r ; i++)
      {free(my_matrix->data_arr[i]);
      }

free(my_matrix->data_arr);
}

//  Time complexity: O(N*nr_val^N)
void perm_rec_1(int N, int nr_vals){

   int values[N];
   perm_helper(N, nr_vals, values, 0);

}

//Time complexity : O(N*nr_val^N)
void perm_helper(int N, int nr_vals, int* values, int current){

int i;
   if (current==N)
      {//print the array and return
         for(i=0;i<N;i++)//O(N)
            printf("%d ",values[i]);
            printf("\n");
            return;
      }

   //the recursion
   for(i=0;i<nr_vals;i++)
   {
      values[current] = i;
      perm_helper( N, nr_vals, values,current+1);
   }

}


//  Time complexity : O(N*nr_val^N)
matrix_ptr perm_rec_2(int N, int nr_vals) {

   matrix_ptr mat = (matrix_ptr) malloc(sizeof (struct matrix_2D_struct));
   //allocating necessary spaces
   int arr2[N];
   int i,j;
   int rows = pow(nr_vals,N);
   mat->data_arr = (int **)malloc(rows* sizeof(int *));
   for (i = 0; i < rows; i++)//this will run nr_vals^N times
    mat->data_arr[i] = malloc(N * sizeof(*(mat->data_arr[i])));

      mat->rows = rows;
      mat->cols = N;

      //The loop for filling the matrix with -1 as an initialization step
   for (i = 0; i < rows; i++) {
    for (j = 0; j < N; j++) {

        mat->data_arr[i][j] = -1; //This will run rows*cols times i.e N*2^N times
    }
}

   perm2_helper(N,nr_vals,arr2, mat, 0, 0);

   return mat;

}



//Time complexity : O(N*nr_val^N)
void perm2_helper(int N, int nr_vals, int * arr2, matrix_ptr mat, int current_i, int current_j)
{
   int i;

   if (current_i== N)
      {//write in matrix
         int j;
         for(j=0;j<N;j++)//O(N)
            mat->data_arr[current_j-N][j]= arr2[j];
            return;
      }

   //the recursion
   for(i=0;i<nr_vals;i++)
   {
      arr2[current_i] = i;
      current_j++;
      perm2_helper( N, nr_vals, arr2, mat, current_i+1,current_j);
   }



}
