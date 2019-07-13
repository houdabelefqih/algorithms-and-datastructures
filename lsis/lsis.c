/*
*  CSE5311 SPRINNG 2018 LAB1
*  HOUDA BELEFQIH 1001511875
*
*
*  ON OMEGA SERVER
*
*  COMPILE WITH : gcc -o lcs lab1.c
*
*  RUN PROGRAM WITH : ./lcs < datafile.txt (with file of data)
*           OR WITH : ./lcs (for direct user input)
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#define maxInputLength 25000

//Structure to hold the distance & LCS computed by both methods
typedef struct result_methods {
   short int length;
   short int* result_array;

}result_methods;


//Structure to hold indexes for the LSIS method
typedef struct indexes {
   short int occurences;
   short int current_position;
   short int* indexes_array;

}indexes;

/*_________________Functions declaration______________________*/

//Function to calculate the elementary cost matrix
void cost_matrix_solution(short int** LS_cost_matrix, short int cols, short int rows,
                          result_methods* ptr);

//function to prshort int matrix
void print_matrix(short int** LS_cost_matrix, short int cols,
                  short int rows, short int* LCS, short int size_of_LCS);

//Function to calculate LCS using the LSIS method
void LSIS_method(short int* sequence1,short int* sequence2,short int N1, short int N2,
                 result_methods* ptr);

//Function to print results of the LSIS method
void print_lsis(short int* lcs_array, short int lcs_size);

//Function to free the space allocated for a 2D matrix
void free_2D(short int** matrix, short int cols, short int rows);

//Function that calculates the max between two integers
short int get_maximum(short int a, short int b);

//Function to compare two arrays
short int compare_arrays(result_methods* ptr,short int size_);


/*________________________ MAIN ____________________________*/
int main()
{
   //Initialization of variables
   short int _rows, rows=0;
   short int _cols, cols=0;
   short int i =0, j=0;
   bool correctsize = true;


/*** Reading user input, two numbers that represent the sizes of the respective sequences ***/
   /*** While checking the given inputs if they don"t execeed the 25000 maxlength***/

   //The do while loop keeps reading from standard input until given correct input sizes
   do
   {
      correctsize = true;
      scanf("%hd %hd",&_rows, &_cols);

      if(_rows > maxInputLength || _cols > maxInputLength)
         {
            printf("Please enter valid input size. Maximum is 25000\n");
            correctsize = false;
         }

   } while (!correctsize);

   /*** Allocating memory for the input sequences for LSIS ***/
   short int* sequence1= malloc(_rows * sizeof(short int));
   short int* sequence2= malloc(_cols * sizeof(short int));


   //The rows and cols of the elementary cost matrix
      rows = _rows+2;
      cols= _cols+2;

   /*** Allocating proper memory space for the elementary cost matrix ***/
   short int** LS_cost_matrix;

      LS_cost_matrix=(short int **)malloc(rows * sizeof(short int *));
      for (i = 0; i < rows; i++)
         {LS_cost_matrix[i] = malloc(cols * sizeof(*(LS_cost_matrix[i])));}

   /*** Initializing the cost matrix to the default value -1 ***/

      for (i=0; i<rows; i++)
      {
         for(j=0;j<cols;j++)
         {   LS_cost_matrix[i][j] = -1; }
      }


   /*** Reading the sequences inputs from the standard input ***/

   //Initialize the "input" variable that will hold one input at a time to zero
   short int input=0;
   bool correctvalue = true;

   /** Filling the first row and first column of matrix with sequences given **/


      for(i=2;i<rows;i++)
         {
            //Read inputs one at a time
            //The do while loop keeps reading from standard input until given correct input value
            //Then fill the first column with the values read

            do {
            correctvalue = true;
            scanf("%hd" ,&input);
               if (input > 255 || input < 0)
               {
                  printf("Please enter a value in the range [0, 255]\n");
                  correctvalue = false;
               }

            } while (!correctvalue);

            LS_cost_matrix[i][0] = input;
            sequence1[i-2]=input;
         }

      //Discard the -1 value in between inputs
      scanf("%hd" ,&input);

      for(i=2;i<cols;i++)
      {
         //Read inputs one at a time
         //The do while loop keeps reading from standard input until given correct input value
         //Then fill the first row with the values read

         do {
            correctvalue = true;
            scanf("%hd" ,&input);
               if (input > 255 || input < 0)
               {
                  printf("Please enter a value in the range [0, 255]");
                  correctvalue = false;
               }

            } while (!correctvalue);


         LS_cost_matrix[0][i] = input;
         sequence2[i-2]=input;

      }

      //Discard the last value -1
      scanf("%hd" ,&input);

      /****************************************************************/

      //Array of structure to hold the results of each method
      result_methods* methods_array = malloc(2 * sizeof(*methods_array));

      //initialize values of length to 0
      methods_array[0].length =0;
      methods_array[1].length =0;

      //Variable for computing CPU time for each method
      //get Time stamps in Milliseconds
         struct timeval startTime, endTime;
         double cpu_time_used1=0, cpu_time_used2=0;


      /********************* LCS with LSIS method *******************/
      gettimeofday(&startTime, NULL);
      LSIS_method(sequence1, sequence2, _rows, _cols, methods_array );
      gettimeofday(&endTime, NULL);

      cpu_time_used1 = (double)(endTime.tv_usec - startTime.tv_usec)/1000;

      /********************* LCS with matrix ************************/

      gettimeofday(&startTime, NULL);
      cost_matrix_solution(LS_cost_matrix, cols, rows, methods_array);
      gettimeofday(&endTime, NULL);

      cpu_time_used2 = (double)(endTime.tv_usec - startTime.tv_usec)/1000;

      /********************* CHECK BOTH RESULTS *********************/

      short int matched =0;

      //Check length of resulting sequences first
      if (methods_array[0].length != methods_array[1].length)
         {printf("\nRESULTS DON'T MATCH\n");}

      //If the lengths match, check that the LCS sequences match for both methods
      //The compare_arrays methods returns 1 if arrays match and 0 otherwise
      else {matched = compare_arrays(methods_array,methods_array[0].length);}

      if (matched ==0)
         {printf("\nRESULTS DON'T MATCH\n");}

      /****** Print results if they match for both methods **********/

      if(matched ==1)
      {
         //First print results with LSIS method
         print_lsis(methods_array[0].result_array, methods_array[0].length);


         //Then print the results with the matrix method
         print_matrix(LS_cost_matrix,cols,rows,
                      methods_array[1].result_array,methods_array[1].length);

      }

      /**********PRINT CPU TIME FOR BOTH METHODS************/
      printf("\n------------------------------------------------------------------------\n");
      printf("CPU time for the   LSIS method(in milliseconds): %.11f ms\n", cpu_time_used1);
      printf("CPU time for the matrix method(in milliseconds): %.11f ms", cpu_time_used2);
      printf("\n------------------------------------------------------------------------\n");


      //Free the cost matrix
      free_2D(LS_cost_matrix,cols,rows);

   free(methods_array);
   free(sequence1);
   free(sequence2);

return(0);

}//end main

//Function to calculate the LCS using the cost matrix method
void cost_matrix_solution(short int** LS_cost_matrix, short int cols, short int rows, result_methods* ptr)
{
   short int i=0, j=0;

    // Filling the cost matrix where second row and second columns always have cost 0
    for (i=1;i<cols;i++)
    {LS_cost_matrix[1][i] = 0;}

    for (i=1;i<rows;i++)
    {LS_cost_matrix[i][1] = 0;}

    /***** Longest common subsequence algorithm ****/
      for (i=2; i<rows; i++)
      {
         for(j=2;j<cols;j++)
         {
            if (LS_cost_matrix[0][j]== LS_cost_matrix[i][0])
            {
               LS_cost_matrix[i][j] = LS_cost_matrix[i-1][j-1] + 1;
            }

            else
            {
               LS_cost_matrix[i][j] = get_maximum(LS_cost_matrix[i-1][j],LS_cost_matrix[i][j-1]);
            }
         }
      }

   /**************Backtracking in the cost matrix to get the LCS********************/
   /** Source : https://www.geeksforgeeks.org/prshort inting-longest-common-subsequence/ **/


      //Size of the resulting LCS will be the value of LS_cost_matrix[rows-1][cols-1]
      short  int size_of_LCS = LS_cost_matrix[rows-1][cols-1];

      short int* LCS= malloc(size_of_LCS * sizeof(short int));

      i = rows -1;
      j = cols -1 ;
      short int k = size_of_LCS;

      while (i > 1 && j > 1)
      {
            if (LS_cost_matrix[0][j] == LS_cost_matrix[i][0])
            {
                LCS[k-1] = LS_cost_matrix[0][j];
                i--; j--; k--; //go diagonal
            }

            else if (LS_cost_matrix[i-1][j] <= LS_cost_matrix[i][j-1])
               j--;//go up

            else
               i--;
            }//end while loop

             //Put the length result AND the LCS in the array of structure
             // That holds the results of each method
             ptr[0].length = size_of_LCS;
             ptr[0].result_array =malloc(size_of_LCS * sizeof(*ptr[0].result_array));
             for(i=0;i<size_of_LCS;i++)
             {ptr[0].result_array[i] = LCS[i];}

}

//Prshort inting edit distance matrix
void print_matrix(short int** LS_cost_matrix, short int cols,short int rows,
                  short int* LCS, short int size_of_LCS)
{
   short int i=0;
   short int j=0;

   printf("\n\nMatrix version: \n");

   //Print the given sequences
   for (j=2; j<cols; j++)
         printf("%d",LS_cost_matrix[j][0]);

      printf("\n");

   for (i=2; i<rows; i++)
         printf("%d",LS_cost_matrix[0][i]);


      printf("\n");

      //Display the LCS
      printf("\nLCS is : ");

      for (i=0; i< size_of_LCS; i++)
      {
         printf("%d", LCS[i]);
      }

      printf(", length==%d", size_of_LCS);

      printf("\n");

      //Free the LCS array
       free(LCS);


   for (i=0; i<rows; i++)
   {
      for(j=0;j<cols;j++)
      {
         if (LS_cost_matrix[i][j] == -1 )
         {
            printf("%3c  ",' ');
         }

         else{printf("%3d  ",LS_cost_matrix[i][j]);}
      }
      printf("\n");

   }

}

//Function that calculate the LCS using the LSIS method
void LSIS_method(short int* sequence1,short int* sequence2,short int N1, short int N2,
                  result_methods* ptr)
{
   short int i=0, j=0,k=0, maximum =0;
   /*
   *
   Source :
    https://www.codingeek.com/algorithms/counting-sort-explanation-pseudocode-and-implementation/
   *
   */


   /**** Get the maximum value in the second sequence array ***/
   for (i=0; i<N2; i++)
    { maximum= get_maximum(maximum, sequence2[i]);}

   //Array that will contain the numbers of occurences of each value in the second sequence
    short int count_array[maximum+1];

    //Initializing counting array count_array[i] to 0
    for (i=0; i<= maximum; i++)
        {count_array[i] = 0;}

    //Store count of each element in array C
    for (j=0; j<N2; j++)
       {count_array[sequence2[j]] = count_array[sequence2[j]] + 1;}

    /*** Get the maximum value in the count array ***/
    /*** This will tell us what's the maximum occurences we can have ***/
    int max_occurences =0;
      for (i=0; i<=maximum; i++)
       { max_occurences= get_maximum(max_occurences, count_array[i]);}

   //Array of structure indx_array
   indexes* indx_array = malloc(maximum * sizeof(indexes));

   /*** Go through the count array and fill the indexes structure ***/
   /*** Allocate proper memory for indexes array ***/

    for (i=0; i<=maximum; i++)
       {
          indx_array[i].occurences = count_array[i];
          indx_array[i].current_position = 0;
          indx_array[i].indexes_array =
                  malloc(indx_array[i].occurences * sizeof(short int));

       }

   for (j=N2-1; j>=0; j--)
   {
      indx_array[sequence2[j]].indexes_array[indx_array[sequence2[j]].current_position]=j;
      indx_array[sequence2[j]].current_position ++;
   }


   int lsis_size_array =0;
   int* lsis_array;
   lsis_array = malloc(lsis_size_array*sizeof(int));

   //Fill the intermediate sequence array
   for (j=0; j<N1; j++)
   {
      if (sequence1[j]>maximum)
      {continue;}

      else{
         //Put intermediate sequence in the LSIS array
         for (k=0; k < indx_array[sequence1[j]].occurences; k++)
         {
            lsis_size_array++;
            lsis_array = realloc(lsis_array, lsis_size_array * sizeof(int));
            lsis_array[lsis_size_array-1]= indx_array[sequence1[j]].indexes_array[k];

         }
            if(max_occurences-k != 0)
            {continue;}
         }

   }

/****************************************************************************/
/*************************** LSIS computing *********************************/
/****************************************************************************/
//Source: http://ranger.uta.edu/~weems/NOTES5311/LISgriesStrict.c                                             **/
/****************************************************************************/
/****************************************************************************/


//Input sequence is the lsis array

int MAX = lsis_size_array+1;
int* m = malloc(MAX*sizeof(int));      // m[i] is the smallest value for an SIS with i numbers
short int* seq = malloc(MAX*sizeof(short int));   // Result sequence
short int* sub = malloc(MAX*sizeof(short int));  // Predecessor to lsis_array[i] in  some SIS
short int* mLink = malloc(MAX*sizeof(short int));;  // The value j for the lsis_array[j] last used to set m[i]
short int mid,low,high;


      k=1;
      m[1]=lsis_array[0];
      sub[0]=(-1);
      mLink[1]=0;

      for (i=1;i<lsis_size_array;i++)
        if (lsis_array[i]==m[k])
        {continue;}

        else if (lsis_array[i]>m[k])
        {
          k++;
          m[k]=lsis_array[i];
          sub[i]=mLink[k-1];
          mLink[k]=i;
        }

        else if (lsis_array[i]<m[1])
        {
          m[1]=lsis_array[i];
          sub[i]=(-1);
          mLink[1]=i;
        }

        else
        {
          low=1;
          high=k;
          while (low!=high-1)
          {
            mid=(low+high)/2;
            if (m[mid]<=lsis_array[i])
              low=mid;
            else
              high=mid;
          }
          // Check search result
          if (m[low]>lsis_array[i] || m[high]<=lsis_array[i])
            printf("error\n");
          if (m[high-1]==lsis_array[i])
          {
            continue;
          }
          m[high]=lsis_array[i];
          sub[i]=mLink[high-1];
          mLink[high]=i;
        }



      // Get result sequence
      i=mLink[k];
      for (j=k-1;j>=0;j--)
      {
        seq[j]=lsis_array[i];
        i=sub[i];
      }

      /****************** STORE RESULTS IN RESULT STRUCTURE **************/

      //Put the length result AND the LCS in the array of structure
      // That holds the results of each method
       ptr[1].length = k;
       ptr[1].result_array =malloc(k * sizeof(ptr[1].result_array));

       for(i=0;i<k;i++)
       {ptr[1].result_array[i] = sequence2[seq[i]];}

}

/* Function that calculates the max between two short integers*/
void print_lsis(short int* lcs_array, short int lcs_size)
{
   short int i=0;
   printf("\n%d\n", lcs_size);

   for(i=0; i<lcs_size; i++)
   {
      printf("%d\n", lcs_array[i]);
   }
    printf("-1\n");

}

/* Function to free the 2D cost matrix*/
void free_2D(short int** matrix, short int cols, short int rows)
{
   short int i=0;

   for (i=0; i<rows ; i++)
            {
               free(matrix[i]);
            }
}

//Method to calculate max between two numbers
short int get_maximum(short int a, short int b)
{
    return (a > b)? a : b;
}

//Function to compare two arrays
short int compare_arrays(result_methods* ptr ,short int size_)
{
	short int i;
	for(i=0;i<size_;i++)
      {
		if(ptr[0].result_array[i]!= ptr[1].result_array[i])
			return 0;
      }
	return 1;
}

