/*
*  COMPILE WITH : gcc -o ed edit_distance.c
*
*  RUN PROGRAM WITH : ./ed < data1.txt
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxString 101

/*____________________________________________Functions declaration______________________________________________*/

struct words{

char s1[maxString];
char s2[maxString];
};

//function to construct distance table
void my_function(struct words strings[2000], int k);

//function to print matrix
void print_distance_table(struct words strings[2000],int k, int** distance_matrix, int cols, int rows);

//function to construct backtracking matrix and print alignment
void backtracking_alignment(struct words strings[2000],int k, int** backtracking, int cols, int rows);

//for minimum distance calculation
int min_distance(int up, int left, int diago, int j, int i, int** backtracking);

/*________________________________________________________________________________________________________________*/


/*_______________________________ MAIN ___________________________________________*/
int main()
{
   struct words strings[2000];
   char s1[maxString];
   char s2[maxString];
   char two_strings[2*maxString]; //2 words of 100 max + space + /0
   int k=0;
   int numberOfCouples=0;

   printf("Enter two words separated by a space (e.g.: cat someone).\n");
   printf("Stop with: -1 -1 \n");

/*___________________READING COUPLES OF STRINGS UNTIL COUPLE (-1,-1) ______________________________________*/

   while(1 == scanf("%[^\n]%*c", two_strings))
      {
         sscanf(two_strings, "%s %s" ,s1,s2);

            if (strcmp(s1, "-1") == 0 || strcmp(s2, "-1") == 0 )
               break;

          strcpy(strings[numberOfCouples].s1, s1);
          strcpy(strings[numberOfCouples].s2, s2);

          numberOfCouples++;
      }//end while loop


/*___________________ EDIT DISTANCE TABLE ______________________________________*/

   for(k=0; k<numberOfCouples; k++)
   {
      my_function(strings, k);

   }//end k loop

    return 0;

}//end main

//edit distance table construction
void my_function(struct words strings[2000], int k )
{

   int rows=0;
   int cols=0;
   int i,j;

     printf("\n");
     printf("first: %s \n",strings[k].s1);
     printf("second: %s \n",strings[k].s2);
     printf("\n");

     rows = strlen(strings[k].s1)+1;
     cols = strlen(strings[k].s2)+1;

     /*Allocating proper memeory for matrixes*/
     int** distance_matrix;
     int** backtracking;

     distance_matrix=(int **)malloc(rows * sizeof(int *));

         for (i = 0; i < rows; i++)
            distance_matrix[i] = malloc(cols * sizeof(*(distance_matrix[i])));

     backtracking=(int **)malloc(rows * sizeof(int *));

         for (i = 0; i < rows; i++)
            backtracking[i] = malloc(cols * sizeof(*(backtracking[i])));


      // filling the left corner of matrixes
      distance_matrix[0][0] = 0;
      backtracking[0][0]= 0;//choosing diagonal


      //first row with 1 2 3 4 ... and backtracking with left arrow : -1
      for(i=1; i<cols; i++)
      {
         distance_matrix[0][i] = i;
         backtracking[0][i]= -1;
      }

      //firt column with 1 2 3 4 ... and backtracking with up arrow : 1
       for(j=1; j<rows; j++)
      {
         distance_matrix[j][0] = j;
         backtracking[j][0] = 1;
      }


      //filling the distance table
      for (j=1;j<rows;j++)
         {
            for (i=1; i<cols;i++)
             {
               //if characters match
               if (strings[k].s2[i-1] == strings[k].s1[j-1])
               {
                 distance_matrix[j][i] = min_distance(distance_matrix[j-1][i]+1,
                                                      distance_matrix[j][i-1]+1,
                                                      distance_matrix[j-1][i-1],
                                                      j,
                                                      i,
                                                      backtracking);

               }//end if match found

               //if characters don't match
               else
               {
                  distance_matrix[j][i] = min_distance(distance_matrix[j-1][i]+1,
                                                       distance_matrix[j][i-1]+1,
                                                       distance_matrix[j-1][i-1]+1,
                                                       j,
                                                       i,
                                                       backtracking);
               }//end else

            }//end j loop

         }//end i loop

 /*____________________________ PRINTING MATRIX ______________________________________*/

      print_distance_table(strings,k,distance_matrix,cols,rows);

/*________________________ EDIT DISTANCE AND ALIGNMENT ________________________________*/

     printf("\nEdit distance: %d \n", distance_matrix[rows-1][cols-1]);

     backtracking_alignment(strings, k,backtracking,cols,rows);

/*______________________________FREEING MATRIXES ______________________________________*/

           for (i=0; i<rows ; i++)
            {
               free(distance_matrix[i]);
               free(backtracking[i]);
            }
   }//end my_function function


//Printing edit distance matrix
void print_distance_table(struct words strings[2000], int k, int** distance_matrix,int cols, int rows)
{
   int i=0;
   int j=0;
      printf("  |    |");
               for(i=0;i<cols-1; i++)
                  printf("  %*c|",2,strings[k].s2[i]);

            printf("\n");

              int m=0;
               for(m=0;m<(5*cols)+3;m++)
                  printf("-");


            printf("\n");


               for (i=0;i<rows;i++)
                  {  if (i==0){printf("  %c|", strings[k].s1[i-1]);}
                     else
                     {printf(" %c|", strings[k].s1[i-1]);}
                        for (j=0; j<cols; j++)
                           {printf("  %*d|", 2,distance_matrix[i][j]);}

                     printf("\n");

                        for(m=0;m<(5*cols)+3;m++)
                          {printf("-");}

                     printf("\n");

                  }

}//end print_distance_table function


//construct backtracking table and print alignment
void backtracking_alignment(struct words strings[2000],int k, int** backtracking, int cols, int rows)
{
   int i = cols-1;
   int j = rows-1;
   int sizeOfLongerString=0;

         //taking the bigger size of the two strings for size of alignment strings
         if (j>= i) sizeOfLongerString =j;
         else sizeOfLongerString= i;

         char alignment1[sizeOfLongerString+1];
         char alignment2[sizeOfLongerString+1];
         char cost[sizeOfLongerString+1];

         int n=1;

         while(i>=0 && j>=0)
         {
               //if the arrow is diagonal
               if (backtracking[j][i]== 0)
                 {
                  alignment1[n-1] = strings[k].s1[j-1];
                  alignment2[n-1] = strings[k].s2[i-1];
                  i--;
                  j--;
                 }

               //arrow pointing up
               else if(backtracking[j][i]== 1)
                  {
                     alignment1[n-1] = strings[k].s1[j-1];
                     alignment2[n-1] = '-';
                     j--;

                  }
               //arrow pointing left
               else {
                 alignment1[n-1] = '-';
                 alignment2[n-1] = strings[k].s2[i-1];
                 i--;


                  }

                  n++;//to keep track of number of our path

         }//end while loop

/*______________________________ COST OF ALIGNMENT ______________________________________*/

         for(i=0; i<sizeOfLongerString;i++)
                  {
                     if (alignment1[i] == alignment2[i])
                        cost[i]='.';
                     else
                        cost[i]='x';
                  }

/*______________________________ PRINTING ALIGNMENT ______________________________________*/

            for(i=sizeOfLongerString-1; i>=0;i--)
               {printf("%c ", alignment1[i]);}

            printf("\n");

            for(i=sizeOfLongerString-1; i>=0;i--)
                  {printf("%c ", alignment2[i]);}

            printf("\n");

            for(i=sizeOfLongerString-1; i>=0;i--)
                  {printf("%c ",cost[i]);}

            printf("\n");

     printf("\n================================================================================\n");

}//end backtracking_alignment function


//Calculating the min distance and at the same time filling the backtracking matrix
int min_distance(int up, int left, int diago, int j, int i, int** backtracking)
{
   int minimum=0;

   if (up<=left)
      {minimum = up;
      backtracking[j][i]= 1; //meaning arrow pointing up
      }
   else
     {
       minimum =left;
       backtracking[j][i]= -1; //-1 meaning arrow pointing left

     }

   if (minimum >diago)
      {minimum = diago;
      backtracking[j][i]= 0;//0 meaning a diagonal "\"
      }

   return minimum;
}//end min_distance function
