/*
* Spanish.txt is HARCODED, the file must be in the same folder as the .exe
* Compile with : gcc -o hw6 hw6.c
* Run with valgrind : valgrind --leak-check=full ./hw6
* Code for perfect tree inspired from :
*  http://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


struct english_words_struct
{
   char* english_word;
   char* word_lookup;
   int probes_perfect_BST;

};

struct spanish_words_sturct
{
   char* spanish_word;
};

//Binary tree node
typedef struct node_perfect * perfectBT_node;
struct node_perfect
{
  int value;
  int cost;
  perfectBT_node left;
  perfectBT_node right;

};


//Function to create new nodes and NULL left and right pointers.
perfectBT_node node_creation(int index);

perfectBT_node construct_perfect_BT(int start, int end);

perfectBT_node search_in_tree(perfectBT_node root, struct english_words_struct* eng_word, char* word_lookup);

//To free every node in BST
void free_tree(perfectBT_node node);

/*_____________________________________________________________________________________*/
int main()
{
   FILE* file;
   char line[600];
   char english_string[101];
   char spanish_string[301];
   int numberOfLines = -1;
   int numberOfWords = -1;

   file = fopen("Spanish.txt", "r"); //open file for reading

       if(file == NULL)
            {
               perror("Error opening file");
               return(-1);
            }


      //This fist while loop is just to count the number of entries in the dictionnary
      //and allocate struct memory accordingly

      while (fgets(line, sizeof(line), file))
         {
            if (line[0] != '#')
               {numberOfWords++;}
         }

      struct english_words_struct english_words_struct[numberOfWords+1];
      struct spanish_words_sturct spanish_words_struct[numberOfWords+1];

   file = fopen("Spanish.txt", "r");

      //read line by line
      while (fgets(line, sizeof(line), file))
         {
            if (line[0] != '#')

            {  numberOfLines++;
               //using sscanf to split the english word and its translation(s)
               //the first string would be the english word
               // then the second string is everything after the english word
               //until the \n new line character is found

               sscanf(line, "%s %[^\n]%s" , english_string, spanish_string);

               english_words_struct[numberOfLines].english_word
               = malloc(101 * sizeof(char));

               english_words_struct[numberOfLines].word_lookup
               = malloc(101 * sizeof(char));

               spanish_words_struct[numberOfLines].spanish_word
               = malloc(301 * sizeof(char));


               //storing words in respective english/spanish structures
               strcpy(english_words_struct[numberOfLines].english_word, english_string);
               strcpy(spanish_words_struct[numberOfLines].spanish_word, spanish_string);

            }
         }

   fclose(file);

   printf("\nResults for building the structures:\n\n");

   /* _____________________perfect BST _____________________*/

   perfectBT_node perfect_tree = construct_perfect_BT(0, numberOfWords);
   printf("Perfect BST:\n");
   float total_cost_perfect = perfect_tree->cost;
   printf("\taverage cost   : %.2f\n",total_cost_perfect/numberOfWords);
   printf("\ttotal cost     : %.2f\n",total_cost_perfect);

   /*_____________________randomized BST_____________________*/


   /*______________________Hashing : Quadratic probing_________*/

/*********************************************************************/
/*______________________ SEARCH FOR ITEMS____________________________*/
/*********************************************************************/

char word_lookup[101];
int number_of_lookup=0;

printf("\nEnter words to look-up. Enter -1 to stop.\n");

   while (1==1)
   {
      scanf("%s", word_lookup);
      if (strcmp(word_lookup, "-1")== 0)
         {break;}

      //Storing the words to look for in the structure
      strcpy(english_words_struct[number_of_lookup].word_lookup, word_lookup);
      number_of_lookup++;

   }

int i=0;
int not_found_perfect_BST =0;
int total_probes_perfect_BST=0;
english_words_struct->probes_perfect_BST =0;

//Looking up spanish definition of every english word entered
for (i=0; i<number_of_lookup; i++)
{
 perfectBT_node result =search_in_tree(perfect_tree, english_words_struct, english_words_struct[i].word_lookup);

   if (result == NULL)
   {  //IF WORD IS NOT FOUND
      printf("%s \t --- NOT FOUND ---\n ", english_words_struct[i].word_lookup);
      printf("\t %d probes (perfect BST)\n\n", english_words_struct->probes_perfect_BST);
      total_probes_perfect_BST = total_probes_perfect_BST + english_words_struct->probes_perfect_BST;
      english_words_struct->probes_perfect_BST =0;//reinitialization
      not_found_perfect_BST++;
      continue;
   }

  int index = result->value;
  printf("%s \t %s\n", english_words_struct[i].word_lookup, spanish_words_struct[index].spanish_word);
  printf("\t %d probes (perfect BST)\n\n", english_words_struct->probes_perfect_BST);
  total_probes_perfect_BST = total_probes_perfect_BST + english_words_struct->probes_perfect_BST;
  english_words_struct->probes_perfect_BST =0;//reinitialization


}

printf("\n\n\n");
printf("SEARCH RESULTS:\n");
printf("PERFECT BST:\n");
float average_perfect_BST =total_probes_perfect_BST/number_of_lookup;
printf("\t average : %.2f\n",average_perfect_BST);
printf("\t not found %d out of %d\n\n",not_found_perfect_BST ,number_of_lookup);


int k=0;
for(k=0; k<numberOfWords+1; k++)
{
   free(english_words_struct[k].word_lookup);
   free(english_words_struct[k].english_word);
   free(spanish_words_struct[k].spanish_word);

}

free_tree(perfect_tree);
    return 0;
}

//Construction of perfect binary tree
perfectBT_node construct_perfect_BT(int start, int end)
{
   static int cost = 0;
    //Base case
    if (start > end)
    {return NULL;}

      cost ++;
    //Middle element = root
    int middle = (start + end)/2;
    perfectBT_node root = node_creation(middle);

    //Recursively construct the left/right subtree and make it left/right child of root
    root->left =  construct_perfect_BT(start, middle-1);
    root->right = construct_perfect_BT(middle+1, end);

    root -> cost = cost;
    return root;
}

//Function to create new nodes and NULL left and right pointers.
perfectBT_node node_creation(int index)
{
    perfectBT_node node = (perfectBT_node)malloc(sizeof(struct node_perfect));//allocating space for nodes
    node -> value = index;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}


//Searching in a BST
perfectBT_node search_in_tree
(perfectBT_node root, struct english_words_struct* eng_word, char* word_lookup)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || strcmp(eng_word[root->value].english_word, word_lookup)==0 )
    {
         eng_word->probes_perfect_BST ++;
         return root;
    }

      eng_word->probes_perfect_BST ++;
    // Key is greater than root's key
    if (strcmp(eng_word[root->value].english_word, word_lookup) < 0)
      {return search_in_tree(root->right,eng_word, word_lookup);}

    // Key is smaller than root's key
    return search_in_tree(root->left,eng_word, word_lookup);


}



//To free every node in BST
void free_tree(perfectBT_node  node){
   //post-order like FatalError hinted at
       if (node != NULL) {
        free_tree(node->right);
        free_tree(node->left);

        free(node);
     }
     }

