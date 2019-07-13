#include<stdio.h>
#include<stdlib.h>

#include "list_hw.h"

/* Builds and returns a list with integers read from standard input.
 * Note that it assumes the Item is int.
 * Notice that all the list access is done through it's interface (functions).
 */

list buildListOfInts() {
   list the_list = newList();

   link current_link = NULL;
   while(1)
   {
      Item number;
      printf("please enter an integer: ");
      int items_read = scanf("%d", &number);
      if (items_read != 1)
      {
         break;
      }

      /* allocate memory for the next link */
      link next_item = newLink(number, NULL);
      insertLink(the_list, current_link, next_item);
      current_link = next_item;
   }
   return the_list;
}


list arrayToList(int arr[], int sz)  {
	int i;
	link p, new_p;
	list A = newList();

	p = newLink(arr[0], NULL);
	insertLink(A, NULL, p);

	for (i = 1; i < sz; i++)
	{
		new_p = newLink(arr[i], NULL);
		insertLink(A, p, new_p);
		p = new_p;
	}

	return A;
}


int test_sublist(list A)  {
    printf("\n\n--------------------------------------\n");
    printf("Testing sublist (for lists of ints).\n\n");
	 printList(A);

	int arr_pos[] = {3,0,6,4};
	list pos_list = arrayToList(arr_pos, 4);
	printf("List with positions pos_list:");
	printList(pos_list);

    list res = sublist(A, pos_list);
	printf("LIST new list:");
	printList(res);
	destroyList(res);

	destroyList(pos_list);
	return 0;
}

int test_insertAtPosition(list A) {
	printf("\n\n--------------------------------------\n");
	printf("Test insertAtPosition (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

	insertAtPosition(A, 12,0);

	printf("After calling insertAtPosition(A, 12, 0) .\n");
	printListHoriz(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}

int test_deleteOccurrences(list A) {
	printf("\n\n--------------------------------------\n");
	printf("Test deleteOccurrences (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

	deleteOccurrences(A, 7);

	printf("After calling deleteOccurrences(A,7).\n");
	printf("After you implement this function, list A (printed below) should not have any values of 7.\n");
	printListHoriz(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}

int test_moveAllMaxAtEnd(list A) {
	printf("\n\n--------------------------------------\n");
	printf("Test moveAllMaxAtEnd (for lists of ints).\n\n");
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);

	printf("After calling moveAllMaxAtEnd.\n");
	//printListHoriz(A);
	printListHorizPointer(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}


/*
****
****** FUNCTIONS FOR TESTING ALL CASES MENTIONNED IN abc1234.pdf
****
*/

int test_sublist_ALLcases(list A)  {

   printf("\n1) Tests sublist (for lists of ints).\n\n");
	printf("LIST A:");
	printList(A);

	/* Case 1 : index out of bound in pos_list*/

	int arr_pos[] = {3,-7,8000,4};
	list pos_list = arrayToList(arr_pos, 4);
	printf("\nList with positions pos_list:");
	printList(pos_list);

   list res = sublist(A, pos_list);
	printf("\nLIST new list with indexes out of bounds:");
	printList(res);
	destroyList(res);

	printf("\n____________________________________________ \n ");

	/* Case 2 : A is NULL */

   int arr_pos2[] = {3,0,6,4};
	pos_list = arrayToList(arr_pos2, 4);

   A= NULL;
   printf("LIST A:");
	printList(A);
	printf("\nList with positions pos_list:");
	printList(pos_list); //same sublist as case 1

   res=sublist(A, pos_list);
   printf("\nLIST new list with A NULL :");
	printList(res);
	destroyList(res);
	printf("\n____________________________________________ \n ");

	/* Case 3 : A is empty */
	A= newList();
	printf("LIST A:");
	printList(A);
	printf("\nList with positions pos_list:");
	printList(pos_list); //same sublist as case 1

   res=sublist(A, pos_list);
   printf("\nLIST new list with A being empty :");
	printList(res);
	destroyList(res);
	destroyList(pos_list);
	printf("\n____________________________________________ \n ");

	/* Case 4 : pos_list is empty */
   int arr[] = {15, 100, 7, 5, 100, 7, 30};
   A = arrayToList(arr, 7);
   pos_list= newList();

	printf("LIST A:");
	printList(A);
	printf("\nList with positions pos_list:");
	printList(pos_list); //same sublist as case 1

   res=sublist(A, pos_list);
   printf("\nLIST new list with pos_list being empty :");
	printList(res);
	destroyList(res);
	destroyList(pos_list);
	printf("\n____________________________________________ \n ");

	/* Case 5 : pos_list is NULL */
	pos_list= NULL;

	printf("LIST A:");
	printList(A);
	printf("\nList with positions pos_list:");
	printList(pos_list); //same sublist as case 1

   res=sublist(A, pos_list);
   printf("\nLIST new list with pos_list being NULL :");
	printList(res);
	destroyList(res);
	destroyList(pos_list);
	printf("\n____________________________________________ \n ");

	/* Case 6 : A is not modified by pos_list, TESTED IN MAIN */
	/* Case 7 : normal data -> ALREADY TESTED */

	/* Case 8 : repeated positions in pos_list */

	int arr_pos3[] = {0,0,0,0};
	pos_list = arrayToList(arr_pos3, 4);

	printf("LIST A:");
	printList(A);
	printf("\nList with positions pos_list:");
	printList(pos_list); //same sublist as case 1

   res=sublist(A, pos_list);
   printf("\nLIST new list with pos_list having repeated values :");
	printList(res);
	destroyList(res);
	destroyList(pos_list);
	printf("\n____________________________________________ \n ");

	printf("\n____________________________________________ \n ");
	printf("\n END OF TESTS FOR sublist \n");
	printf("\n____________________________________________ \n ");

	return 0;
}

int test_deleteOccurrences_ALLcases(list A) {

   printf("2) Tests deleteOccurrences (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

   /* Case 1 already tested  */
   /* Case 2 : V does not occur in A */
	deleteOccurrences(A, 9);
	printf("\nAfter calling deleteOccurrences(A,9):\n");
	printListHoriz(A);

	printf("\n____________________________________________ \n ");

   /* Case 3 : Repeated consecutives occurences of the value 7 */

   int arr[] = {15, 7, 7, 7, 7, 7, 30}; //multiple 7
   A = arrayToList(arr, 7);
   printf("\nIf a value occurs multiple times in list: \n");
	printf("\n LIST A:");
   printListHoriz(A);
   deleteOccurrences(A, 7);// delete value 7 from list

   printf("\nAfter calling deleteOccurrences(A,7) with consecutive 7 in the list:\n");
	printListHoriz(A);

	printf("\n____________________________________________ \n ");

	/* Case 4 : if list has one item and that item is V */

	arr[0] = 7; //only one item
   A = arrayToList(arr, 1);
   printf("\nIf the list has one item and that item is V: \n");
	printf("\n LIST A:");
   printListHoriz(A);
   deleteOccurrences(A, 7);// delete value 7 from list

   printf("\nAfter calling deleteOccurrences(A,7) with the only item in list is 7 :\n");
	printListHoriz(A);

	printf("\n____________________________________________ \n ");

	/* Case 5 : A has only one value in it */

	int arr2[] = {7, 7, 7, 7, 7, 7, 7}; //only 7
   A = arrayToList(arr2, 7);
   printf("\nIf the list is made of one value only: \n");
	printf("\n LIST A:");
   printListHoriz(A);
   deleteOccurrences(A, 7);// delete value 7 from list

   printf("\nAfter calling deleteOccurrences(A,7) with every value is the same:\n");
	printListHoriz(A);

	printf("\n____________________________________________ \n ");

	/* Case 6 : A is NULL*/

	A = NULL;
	printf("\n LIST A:");
   printListHoriz(A);
   deleteOccurrences(A, 7);// delete value 7 from list
   printf("\nAfter calling deleteOccurrences(A,7) with A pointer being NULL :\n");
	printListHoriz(A);

	printf("\n____________________________________________ \n ");

	/* Case 7 : A is empty */

   A = newList();
	printf("\n LIST A:");
   printListHoriz(A);
   deleteOccurrences(A, 7);// delete value 7 from list
   printf("\nAfter calling deleteOccurrences(A,7) with A being empty :\n");
	printListHoriz(A);

	printf("\n____________________________________________ \n ");
	printf("\n END OF TESTS FOR deleteOccurences \n");
	printf("\n____________________________________________ \n ");

	return 0;
}

int test_insertAtPosition_ALLcases(list A) {

	printf("\n3) Tests insertAtPosition (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

   /* Case 1 already tested  */
   /* Case 2 : A is NULL */

	A = NULL;
	printf("\n LIST A:");
   printListHoriz(A);
   insertAtPosition(A, 12, 0);
   printf("\nAfter calling insertAtPosition(A, 12, 0) with A being NULL:\n");
	printListHoriz(A);
	destroyList(A);

	printf("\n____________________________________________ \n ");

   /* Case 3 : A is empty */

   A = newList();
	printf("\n LIST A:");
   printListHoriz(A);
   insertAtPosition(A, 12, 0);
   printf("\nAfter calling insertAtPosition(A, 12, 0) with A being empty:\n");
	printListHoriz(A);
	destroyList(A);

	printf("\n____________________________________________ \n ");

	/* Case 4 : position is greater than length of A */
   int arr0[] = {15, 100, 5, 100, 30};
   A = arrayToList(arr0, 5);

	printf("\n LIST A:");
   printListHoriz(A);
   insertAtPosition(A, 12, 77);
   printf("\nAfter calling insertAtPosition(A, 12, 77):\n");
	printListHoriz(A);
	destroyList(A);

	printf("\n____________________________________________ \n ");

	/* Case 5 : position is negative */


   int arr2[] = {15, 100, 5, 100, 30};
   A = arrayToList(arr2, 5);

	printf("\n LIST A:");
   printListHoriz(A);
   insertAtPosition(A, 12, -7);
   printf("After calling insertAtPosition(A, 12, -7):\n");
	printListHoriz(A);


	printf("\n____________________________________________ \n ");
	printf("\n END OF TESTS FOR insertAtPosition \n");
	printf("\n____________________________________________ \n ");

	return 0;
}

int test_moveAllMaxAtEnd_ALLcases(list A){

   printf("\n\n--------------------------------------\n");
	printf("\n4)Test moveAllMaxAtEnd (for lists of ints).\n\n");

	/* Case 1 : A is NULL */

	A= NULL;
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);


	printf("After calling moveAllMaxAtEnd with A being NULL: \n");
	//printListHoriz(A);
	printListHorizPointer(A);

	printf("\n____________________________________________ \n ");

	/* Case 2 : A is empty */

	A= newList();
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);

	printf("After calling moveAllMaxAtEnd with A being an empty list: \n");
	//printListHoriz(A);
	printListHorizPointer(A);
   destroyList(A);
	printf("\n____________________________________________ \n ");

	/*Case 3 : Normal Data, already TESTED*/

	/*Case 4 : A has one item*/

   int arr0[] = {8};
   A = arrayToList(arr0, 1);
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);


	printf("After calling moveAllMaxAtEnd with A having one item only: \n");
	//printListHoriz(A);
	printListHorizPointer(A);
	destroyList(A);

	printf("\n____________________________________________ \n ");


	/*Case 5 : A hasonly items of same value*/

   int arr[] = {8,8,8};
   A = arrayToList(arr, 3);
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);

	printf("After calling moveAllMaxAtEnd with A having only items of same value: \n");
	//printListHoriz(A);
	printListHorizPointer(A);
	destroyList(A);

	printf("\n____________________________________________ \n ");

	/*Case 6 : The max is on the first position*/

   int arr2[] = {100,8,20};
   A = arrayToList(arr2, 3);
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);


	printf("After calling moveAllMaxAtEnd with the max is on the first position: \n");
	//printListHoriz(A);
	printListHorizPointer(A);
	destroyList(A);

	printf("\n____________________________________________ \n ");

	/*Case 7 : Already TESTED*/


   printf("\n____________________________________________ \n ");
	printf("\n END OF TESTS FOR moveAllMaxEnd \n");
	printf("\n____________________________________________ \n ");

	return 0;
}


/*
****
****** MAIN
****
*/

int main() {
    list A = NULL;
    int arr[] = {15, 100, 7, 5, 100, 7, 30};
    A = arrayToList(arr, 7);
    //A = buildListOfInts() ;  // use this line and redirect input to run test cases from data files. See posted example data file.
    printf("\nLIST A:");
    printList(A);

    test_sublist(A);
    printf("\nLIST A after sublist (should be intact):");
    printList(A);// TO MAKE SURE A WAS NOT ALTERED BY sublist function
    test_deleteOccurrences(A);
    test_insertAtPosition(A);
    test_moveAllMaxAtEnd(A);
    destroyList(A);

    printf("\nEND OF TESTS AS PROVIDED IN HOMEWORK \n");

    printf("\n \n \n ");

    /*
    *Tests of functions as requested in question 7 of TASK 1 of Homework2
    */
    printf("\n-------------------------------------------------\n");
    printf("\n-------------------------------------------------\n");
    printf("\n THOROUGH TEST OF FUNCTIONS \n ");
    printf("\n-------------------------------------------------\n");
    printf("\n-------------------------------------------------\n");

    // To test all functions thoroughly, uncomment the lines below


      /*
       A = arrayToList(arr, 7);

       test_sublist_ALLcases(A);
       test_deleteOccurrences_ALLcases(A);
       test_insertAtPosition_ALLcases(A);
       test_moveAllMaxAtEnd_ALLcases(A);

       destroyList(A);
       */





    return 0;
}
