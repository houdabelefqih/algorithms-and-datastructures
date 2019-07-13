/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"


struct node_struct {
    Item item;
    link next;
};

struct list_struct {
    link first;
    int length;
};


// ------------- link functions

/* Creates a new link, that contains the value specified in the argument,
 * and that points to next_in.
 */
link newLink(Item value, link next_in) {
    link result = (link) malloc(sizeof (struct node_struct));
    result->item = value;
    result->next = next_in;
    return result;
}

void destroyLink(link the_link)  {
    if (the_link != NULL) {
        free(the_link);
    }
}

Item getLinkItem(link the_link) {
    if (the_link != NULL) {
        return the_link->item;
    }
    else {
        printf("\n getLinkItem: Empty link. Returned -1.");
        return -1;    // NOTE: This line can be improved.
    }
}


link getLinkNext(link the_link) {
    if (the_link != NULL) {
        return the_link->next;
    }
    else {
        return NULL;
    }
}

void setLinkItem(link the_link, Item value) {
    if (the_link != NULL) {
        the_link->item = value;
    }
}

void setLinkNext(link the_link, link next) {
    if (the_link != NULL) {
        the_link->next = next;
    }
}



/*    --------  LIST functions    */

int listIsNULL(list the_list) {
    if (the_list == NULL) {
        printf("\nThe list pointer is NULL)\n");
        return 1;
    }
    else {
        return 0;
    }
}

/* Creates and returns an empty list. */
list newList() {
    list result = (list) malloc(sizeof (*result));
    result->first = NULL;
    result->length = 0;
    return result;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroyList(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }

    link current = the_list->first;
    while (1) {
        if (current == NULL) {
            break;
        }

        link next = current->next;
        destroyLink(current);
        current = next;
    }
    free(the_list);
}

link getFirst(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return NULL;
    }

    return the_list->first;
}

int getLength(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return -1;
    }

    return the_list->length;
}


/* Sets the data to empty (first is null, length is 0,...)
 * It does NOT free any memory.
 */
void setEmpty(list the_list) {
    the_list->first = NULL;
    the_list->length = 0;
}


/* Inserts new_link to the specified list, at the position right after
 * the link called "previous". */
void insertLink(list my_list, link previous, link new_link) {
    if (listIsNULL(my_list) == 1) {
        return;
    }

    /* We need a special case when we want to insert to the beginning.
     * In that case, the previous link is NULL. */
    if (previous == NULL) {
        new_link->next = my_list->first;
        my_list->first = new_link;
    } else {
        new_link->next = previous->next;
        previous->next = new_link;
    }

    my_list->length += 1;
}

/* Inserts new_link to the beginning of the list. */
void insertAtBeginning(list my_list, link new_link) {
    setLinkNext(new_link, getFirst(my_list));  // replaces: new_link->next = my_list->first;
    my_list->first = new_link;
    my_list->length += 1;
}

/* Removes from the list and returns the link coming AFTER link x.
 * This function DOES NOT remove link x itself.
 */
link removeNext(list my_list, link x) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link temp;
    if (x == NULL) // try to delete the first node
    {
        temp = my_list->first;
        if (my_list->first != NULL) // There is at least one node in the list.
        {
            my_list->first = my_list->first->next;
            my_list->length -= 1;
        }
    } else {
        temp = x->next;
        x->next = x->next->next;  // IS THIS CODE SAFE? JUSTIFY YOUR ANSWER.
        my_list->length -= 1;
    }
    return temp;
}

/* Removes from the list and returns the link at the beginning of the list.
It does not free the memory for that node. */
link removeFirst(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link first_node = my_list->first;
    if (first_node != NULL) {
        my_list->first = first_node->next;
        my_list->length -= 1;
    }
    return first_node;
}

void reverse(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }

    link current = the_list->first;
    link previous = NULL;
    while (current != NULL) {
        link temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    the_list->first = previous;
}

void printList(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("item %d: %d\n", i, curr->item);
        i++;
    }
    printf("\n");
}


void printListHoriz(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%5d    ", curr->item);
        i++;
    }
    printf("\n");
}

void printListHorizPointer(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\nList items:    ", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%-11d  ", curr->item);
        i++;
    }
    printf("\n");
	printf("List pointers: ");
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
    printf("\n");
}


int computeLength(list my_list) {
     if (listIsNULL(my_list) == 1) {
        return -1;
    }

    int counter = 0;
    link i;
    for (i = my_list->first; i != NULL; i = i->next) {
        counter++;
    }
    return counter;
}

list listDeepCopy(list input) {
    list result = newList();
    link in = getFirst(input);
    link previous = NULL;
    while (in != NULL) {
        link out = newLink(getLinkItem(in), NULL);
        insertLink(result, previous, out);
        previous = out;
        in = getLinkNext(in);
    }

    return result;
}

/* returns a new list that contains all values of input1 and all values
 * of input2
 */
list concatLists(list input1, list input2) {
    list result = listDeepCopy(input1);
    list temp2 = listDeepCopy(input2);
    concatListsDestructive(result, temp2);
    free(temp2);
    return result;
}

/* Modifies target, by inserting at the end of it all links from source.  */
void concatListsDestructive(list target, list source) {
    link previous = NULL;
    link c;

    /* find the last link of target*/
    for (c = getFirst(target); c != NULL; c = getLinkNext(c)) {
        previous = c;
    }

    /* at this point, previous is the last link of target */
    setLinkNext(previous, getFirst(source));
    target->length = target->length + source->length;  // important

    /* Source should not link to the moved nodes any more (when target and source
     * lists get destroyed, each of them will attempt to free the nodes in
     * source).
     */
    setEmpty(source);
}



/*----------------------------------------------------------------
 New functions for HW3.
 Finish their implementation below.
 If you need to use helper functions you can define them and use them in this file.
 You should not change the behavior of any of the functions defined above.
 */
void insertAtPosition(list A, Item val, int pos){

if (listIsNULL(A) == 0) //if the link of A list is not NULL

{  link temp = A->first;
   link previous = NULL;
   int position =0, i=0;

   link newLinkCreated = newLink(val, NULL);//new node creation with specified item value

      //check if either the list is empty, or it is not AND we want to insert in the beginning
   if (temp != NULL && pos <= 0 || temp == NULL)
         {insertAtBeginning(A,newLinkCreated);
         return;}

   else if (pos >= (A->length)) //if position is last one or is greater than length of list
            {
               while(temp->next!=NULL)
                    {temp = temp->next;}//move in list until temp is NULL

               temp->next = newLinkCreated;
               A->length += 1;
               return;
            }

else {
   while (temp != NULL)
         {
            //moving in the list while keeping track of previous and current link
            for (i=0; i< A->length; i++)
            {
               if (position != pos)
                {
                  previous =temp;
                  temp= temp->next;
                  position ++;}

               else
                 {
                  insertLink(A,previous,newLinkCreated);
                  free(temp);
                  return;
                 }
            }

            temp = temp->next;//update temp

         }

}//end of else
}//end of first if(checking if the list is not null)
else
   return;

}//end of method

void deleteOccurrences(list A, Item V) {

if (listIsNULL(A)== 0)
   { // temp to store the head node
    link temp = A->first;

   //previous to store the previous node passed
   link previous = NULL;

    // Case 1 : the first node contains the value V
    while (temp != NULL && temp->item == V)
    {
        A->first = temp->next;   // change head
        destroyLink(temp);      // destroy old head
        temp = A->first;       // change temp to the new head
        A->length -= 1;        // decrement by 1 length of the list
    }

    // Case 2 : delete other occurences besides head
    while (temp != NULL)
    {
        // Look for the value V to be deleted and at the same time
        // keep track of the previous node
        while (temp != NULL && temp->item != V)
        {
            previous = temp;
            temp = temp->next; //move on
        }//end inner while loop

        // If we get to the end of the list and the value V was not found
        if (temp == NULL) {return;}


         //if the temp is not null but the value V was found
        // destroy the node with item V AFTER updating previous node to skip that node
        previous->next = temp->next;
        destroyLink(temp);
         A->length -= 1;        // decrement by 1 length of the list

        //Update temp for outer while loop's next iteration
        temp = previous->next;

    }//end outer while loop

   }//end of if list is not null

   else
      return;
}

list sublist(list A, list pos_list) {

   link previous = NULL;
   list resulting_List =newList();
   link current_resulting_List= resulting_List->first;
   int pos_in_A=0;


   if ( listIsNULL(A) == 1 || listIsNULL(pos_list)== 1)// list A or pos_list pointer is NULL

         {  setEmpty(resulting_List);
            listIsNULL(resulting_List);
            return;
         }

   //declaration of pointer to both lists
   link current = A->first;
   link current_pos_list = pos_list->first;

   if  (current == NULL || current_pos_list == NULL) //pos_list or list A is empty

         {  setEmpty(resulting_List);
            listIsNULL(resulting_List);
               return;
         }



      while (current != NULL && current_pos_list !=NULL)
         {
               //check if items in pos_list are out of bounds
               if (current_pos_list->item <0 || current_pos_list->item >= A->length)
                     {
                        setEmpty(resulting_List);
                        listIsNULL(resulting_List);
                        return;
                     }

               while (pos_in_A != current_pos_list->item)

                  {
                     current =current->next; //move in list
                     pos_in_A ++;//couunt number of moves in other words indexes
                  }

            //if a match has been found
            current_resulting_List = newLink(current->item,NULL);//create new node

            if(resulting_List->first == NULL)
               {resulting_List->first = current_resulting_List; //make head of new list point at first node
                previous = current_resulting_List;//keep track of previous link
               }


            resulting_List->length +=1;//increment length of the new list
            current_pos_list = current_pos_list->next;//move to the next node in pos_list
            previous->next=current_resulting_List;//link the nodes
            previous = current_resulting_List;
            pos_in_A =0;//to restart A from the beginning
            current = getFirst(A);//initialize current to point at first node of list A
         }

         return resulting_List;

}



void moveAllMaxAtEnd(list A) {

         if ( listIsNULL(A)== 1 //if A is NULL
              || A->first == NULL //if A is empty
              ||A->first->next == NULL) //A has only one item
                  return; //do nothing

   link current = A->first;
   int key = current->item; //initialize the max at first value


   while(current != NULL && current->next !=NULL)
            {
                //move in the list and store the max item in key
                  if (current->next->item > key)
                        {key = current->next->item;
                        }

                  current = current->next;
            }//end while

   //at this point key contains the max value

   //we are going to reverse the list, and insert the maximum value at the beginning

   reverse(A);
   current = A->first;//current points to head
   link previous = current;//previous is current at the beginning


         while(current != NULL && previous != NULL)
               {

                  //this case is if the current node we are at has NULL as next
                  //i.e if the list has only one element OR
                  //if we are at the last node of the list (reversed)
                  //the last node at the list reversed is the first node at the original list
                  //so this is to handle max at first node in original list
                   if (current->next == NULL &&
                       current->item == key &&
                       previous->item != key)
                        {
                           previous->next= NULL;//update of link to become last
                           insertAtBeginning(A,current);
                           A->length -=1;
                           current= NULL;
                           reverse(A);
                           return;
                        }


                  //normal case, the max is not at the beginning of the original list
                   if (current->item == key && previous->item != key)
                           {
                              previous->next= current->next;//update of links
                              insertAtBeginning(A,current);//insert at beginning
                              current = previous->next;//update of links
                              //because insert at beginning increments the length event though we didn't create a new link
                              A->length -=1;
                           }

               //move to next couple of links
                 previous = current;
                 current = current->next;

               } //end while
reverse(A);
  // after all the max value were inserted at the beginning,
  //by reversing the list they are going to be at the end
}


