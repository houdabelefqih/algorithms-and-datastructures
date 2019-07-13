#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <string.h>
#define maxTextCharacters 10000


//declaration of methods
void readAndPrintOrignalWords (char []);
void toLowerCase (char []);
int stringsCompare (char [],char []);
void insertionSorting (char [], int[], int);
void BinarySearch(int [], int, char[]);


int main ()
{
   char text [maxTextCharacters+1];

    printf("Enter the text: \n");
    scanf("%[^\n]", text); //read entire characters until it hits the \n (another line)

    readAndPrintOrignalWords(text);
    //when all methods are finished

return 0;
}

/*
** DEFINITION OF METHODS USED**
*/

//method to print words of text and their indexes and calls insertion method
void readAndPrintOrignalWords (char text[])
{
   char word[101];
   int wordIndex[5000];//worst case we have all the words are one character only
   int index = 0;
   int j =0;//variable to count indexes i.e number of words in text


   printf("\nWords and indexes (the printed words are 'cleaned'): \n");
   printf("  i  |index[i]|  word \n");
   printf("-----|--------|------------------\n");


      for (index=0; index<strlen(text);index++)

         {
            while(text[index]== ' ') //skip multiple spaces
            {index++;}

            wordIndex[j]= index;
            sscanf(&text[index],"%s", word); // read characters until the space character, meaning read word by word

            toLowerCase(word); //convert entire word to lower case.

               //test if last character in word is not alphanumeric
               if (!isalnum(word[strlen(word)-1]))
               {word[strlen(word)-1]='\0';}//truncate the non-alphanumeric character

            printf("   %d |     %*d |  %s \n",j, 2, wordIndex[j],word); //the value 2 is for the numbers to align in display

            /* the next index is the previous index + the length of the word at previous
            ** index + 1 character to count the space between two words
            ** THE +1 WILL BE ADDED WHEN THE LOOP REITERES
            */
            index = index + strlen(word);
            j++;

         }//end of index loop

            int sizeofIndexArray=j;
               /*call method to perform insertion sort, takes as arguments :
               ** the text, the array of indexes and the array's size
               */
               insertionSorting(text, wordIndex,sizeofIndexArray);

}


//method to sort the indexes using INSERTION sort algorithm
void insertionSorting (char text[],int wordIndex[], int sizeOfIndexArray)
{
   int i=1,j=0,key=0,comparaisonValue=0, k=0;
   char word1[101];
   char word0[101];

   for (i=1; i<sizeOfIndexArray; i++ )
   {
      key =wordIndex[i];
      j=i-1;

      sscanf(&text[key],"%s", word1);
      sscanf(&text[wordIndex[j]],"%s", word0);

       while(j>=0 && ( stringsCompare(word1,word0))== -1 ) //compare word at i and i-1

         {
            wordIndex[j+1]=wordIndex[j];
            j=j-1;

            sscanf(&text[key],"%s", word1);
             if (j>=0)
             {sscanf(&text[wordIndex[j]],"%s", word0);}
         }//end of while loop

      wordIndex[j+1]=key;

   }//end of i loop

   //print all sorted indexes and their words
   printf("\nThe sorted data (the printed words are 'cleaned'):\n");
   printf("  i  |index[i]|  word\n");
   printf("-----|--------|------------------\n");

   for (k=0;k<sizeOfIndexArray;k++)
      {
         sscanf(&text[wordIndex[k]],"%s", word1);
         toLowerCase(word1); //convert entire word to lower case.

         //test if last character in word is not alphanumeric
         if (!isalnum(word1[strlen(word1)-1]))
            {word1[strlen(word1)-1]='\0';}//truncate the non-alphanumeric character

         printf("   %d |     %*d |  %s \n",k, 2, wordIndex[k],word1);

      }//end of k loop

         //call method to perform Binary search on SORTED array
         BinarySearch(wordIndex, sizeOfIndexArray, text);
}//END OF METHOD


//method to perform Binary search
void BinarySearch(int wordIndex[], int sizeOfArray, char text[])
{
   char wordToSearch[101]; //word entered by user
   char word[101];//word in the text
   int iterations =0;

   printf("\nBinary search. ---- Enter words to search for. Stop with -1.\n");

    while(scanf("%s[^\n]", &wordToSearch) == 1) //read word entered
    {
       printf("(original : %s)\n", wordToSearch);

       if(!(strcmp(wordToSearch, "-1")==0)) //condition to run the binary search if user didn't enter -1
          {
               int first = 0;
               int last = sizeOfArray - 1;
               int middle = (first+last)/2;

               //test if last character in word to search is not alphanumeric
               if (!isalnum(wordToSearch[strlen(wordToSearch)-1]))
               {wordToSearch[strlen(wordToSearch)-1]='\0';}//truncate the non-alphanumeric character
               toLowerCase(wordToSearch); //convertto lower case.

         while (first <= last)
            {

               iterations++;// each time the loop is entered the number of iterations increases by 1

               sscanf(&text[wordIndex[middle]],"%s", word); //put the string at the middle index in the string word

               //test if last character in to word in the text to compare with is not alphanumeric
               if (!isalnum(word[strlen(word)-1]))
               {word[strlen(word)-1]='\0';}//truncate the non-alphanumeric character
               toLowerCase(word); //convert lower case.

               if (strcmp(word,wordToSearch) == -1) //if the word in text at middle index is alphabetically BEFORE the word to search
                     first = middle + 1; //eliminate all left side

                  else if (strcmp(word,wordToSearch) == 0)//if the two words to compare MATCH
                     {
                     printf("cleaned: %s - found ( %d iterations)\n", wordToSearch, iterations);
                     break;
                     }
                  else //if the word in text at middle index is alphabetically AFTER the word to search
                     last = middle - 1; //eliminate all right side

                  middle = (first + last)/2;//change position of middle index if words don't match

               }//end of inner while loop

               if (first > last) //if all words have been inspected and no match was found
                  printf("cleaned: %s - not found ( %d iterations)\n", wordToSearch, iterations);

          }//end of first if condition

          else
            break;

            iterations =0; //reinitialize the number of iterations

    }//end of outer while loop

    //show that original text was NOT ALTERED (has punctuation and uppercases letter)
    printf("\nThe original text is still the same : %s \n \n", text);
}//END OF METHOD


//method to convert entire word to lower case
void toLowerCase (char passedWord[101])
{ int i=0;
   for(i = 0; passedWord[i]; i++)//for each character of the string passed
      passedWord[i] = tolower(passedWord[i]);

}//END OF METHOD


//method to compare strings which first characters are lowercases
int stringsCompare (char passedWord1[],char passedWord2[])
{
   int comparaisonValue=0;

   if (passedWord1[0]>='A' && passedWord1[0]<='Z') //if the first letter of the word is in the range [A-Z]
         {passedWord1[0]= tolower(passedWord1[0]);}

   if (passedWord2[0]>='A' && passedWord2[0]<='Z') //if the first letter of the word is in the range [A-Z]
         {passedWord2[0]= tolower(passedWord2[0]);}

   comparaisonValue =strcmp(passedWord1,passedWord2);

   return comparaisonValue;
}//END OF METHOD
