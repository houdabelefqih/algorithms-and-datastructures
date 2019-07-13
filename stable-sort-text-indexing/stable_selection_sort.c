#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MaxRecords 2000

struct records //structure to hold all the records
 {
   int number;
   char word[101]; //array that can contain a word of 100 characters + the \0 terminator

 };

//Declaration of the method to print Data
void DisplayData(struct records PasssedRecords[MaxRecords+1],int NumberOfRecords);

//Declaration of the method to print Data
void UnstableSelectionSort(struct records PassedRecords[MaxRecords+1],int NumberOfRecords);

//Declaration of the method to print Data
void StableSelectionSort(struct records PassedRecords[MaxRecords+1],int NumberOfRecords);



int main ()
{
   int numberOfRecords=0,i=0;

do {

   printf("Enter the number of records: \n");

   //Read number of Records
   scanf("%d",&numberOfRecords);

   //verify that the number of records is not greater than 2000
   if (numberOfRecords > 2000)
   {  printf("Sorry, the number of records must be inferior to 2000.");
      printf("\n");
      printf("\n");
      }

   else {

   struct records recordEntered[numberOfRecords+1];
   struct records sortedRecordsUnstable[numberOfRecords+1];
   struct records sortedRecordsStable[numberOfRecords+1];

   printf("Enter the data pairs(number string):\n");

   //Read all inputs and stores them in a strcuture called record
      for(i=0;i<numberOfRecords; i++)
         {
            scanf("%d %s",&recordEntered[i].number, &recordEntered[i].word);

         /*Copy of the original into the structure
         which will be sorted with UNstable selection sort */
         sortedRecordsUnstable[i].number= recordEntered[i].number ;
         strcpy(sortedRecordsUnstable[i].word,recordEntered[i].word );

         /*Copy of the original into the structure
         which will be sorted with Stable selection sort */
         sortedRecordsStable[i].number= sortedRecordsUnstable[i].number ;
         strcpy( sortedRecordsStable[i].word, sortedRecordsUnstable[i].word );

         }

   printf ("\n");

   //Display loaded Data
   printf ("Loaded data: \n");
   DisplayData(recordEntered,numberOfRecords);
   printf ("\n");

   // Sort original data and then display the result
   UnstableSelectionSort(sortedRecordsUnstable,numberOfRecords);
   printf ("Data sorted with UNSTABLE selection sort: \n");
   DisplayData(sortedRecordsUnstable,numberOfRecords);

   printf ("\n");

   //printf ("Sorted Data (Stable)\n");
   StableSelectionSort(sortedRecordsStable,numberOfRecords);
   printf ("A copy of the original data, sorted with STABLE selection sort:: \n");
   DisplayData(sortedRecordsStable,numberOfRecords);

   }

   } while (numberOfRecords>2000); //Repeat if the number of records is not greater than 2000

return 0;

}//end of main




//Method to print Data, has as arguments the records entered and their size
void DisplayData (struct records PassedRecords[], int NumberOfRecords)

   {  int i;
      for(i=0;i<NumberOfRecords; i++)
         {
            printf("%d, %s", PassedRecords[i].number, PassedRecords[i].word );
            printf ("\n \n");
         }//end of i loop
   }//end of method

//Method to sort Data using the selection sort: UNstable version
void UnstableSelectionSort(struct records PassedRecords[],int NumberOfRecords)
{
   //This code is taken from the course's slides and modified for the purpose of this task

   int i, j, temp;
   char tempWord[101];//temporary array that can contain a word of 100 characters + the \0 terminator

for (j = 0; j < NumberOfRecords-1; j++)
 {
   int min_idx = j; //min_idx: index of the smallest remaining item.

         for (i = j+1; i < NumberOfRecords; i++)

            {
               if ( PassedRecords[i].number < PassedRecords[min_idx].number)

               min_idx = i;
            }

   //swapping of elements
   temp = PassedRecords[min_idx].number;
   PassedRecords[min_idx].number = PassedRecords[j].number;
   PassedRecords[j].number = temp;

   //swapping of elements : words associated with numbers
   strcpy(tempWord, PassedRecords[min_idx].word);
   strcpy(PassedRecords[min_idx].word, PassedRecords[j].word);
   strcpy(PassedRecords[j].word, tempWord);


 }//end of j loop
}// end of method

//Method to sort Data using the selection sort: UNstable version
void StableSelectionSort(struct records PassedRecords[],int NumberOfRecords)
{
   //This code is taken from the course's slides and modified for the purpose of this task

   int i, j, temp;
   char tempWord[101];//temporary array that can contain a word of 100 characters + the \0 terminator

for (j = 0; j < NumberOfRecords-1; j++)
 {
   int min_idx = j; //min_idx: index of the smallest remaining item.

         for (i = j+1; i < NumberOfRecords; i++)

           { if ( PassedRecords[i].number < PassedRecords[min_idx].number)

               min_idx = i;
           }

   //we store the smallest item in a temporary variable
   temp = PassedRecords[min_idx].number;
   strcpy(tempWord, PassedRecords[min_idx].word);


         for (i = min_idx; i > j; i--)
         {
         // Instead of swapping we shift all the elements to the right -->
         PassedRecords[i].number = PassedRecords[i-1].number;
         strcpy(PassedRecords[i].word, PassedRecords[i-1].word);

         }

   //We copy the content of the temporary variable in the index j (the index we started the first loop with)
   PassedRecords[j].number = temp;
   strcpy(PassedRecords[j].word, tempWord);



 }//end of j loop
} //end of method
