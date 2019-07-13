


/* SOURCE  : http://ranger.uta.edu/~weems/NOTES5311/ff.c
/* HOUDA BELEFQIH, 1001511875, SPRING 2018, LAB2
*/


/*  ON OMEGA SERVER
*
*  COMPILE WITH : gcc -o lab2 lab2.c
*
*  RUN PROGRAM WITH : ./lab2 < testfile.txt (with file of data)
*           OR WITH : ./lab2 (for direct user input)
*/

// Derived from
// http://www.aduni.org/courses/algorithms/handouts/Reciation_09.html#25630

// The Ford-Fulkerson Algorithm in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// Basic Definitions

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_VERTICES 3000
#define MAX_EDGES 10000
#define MAX_CAPACITY 10000
#define oo 1000000000

// Declarations

int n;  // number of nodes
int e;  // number of edges
int capacity[MAX_VERTICES][MAX_VERTICES]; // capacity matrix
int flow[MAX_VERTICES][MAX_VERTICES];     // flow matrix
int color[MAX_VERTICES]; // needed for breadth-first search
int pred[MAX_VERTICES];  // array to store augmenting path

int min (int x, int y) {
    return x<y ? x : y;  // returns minimum of x and y
}

// A Queue for Breadth-First Search

int head,tail;
int q[MAX_VERTICES+2];

void enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

// Breadth-First Search for an augmenting path

int bfs (int start, int target) {
    int u,v;
    for (u=0; u<n; u++) {
        color[u] = WHITE;
    }
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head!=tail) {
        u = dequeue();
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
        for (v=0; v<n; v++) {
            if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0) {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

int* bfs_2(int start, int target) {
    int *S_set = malloc (sizeof (int) * MAX_VERTICES);
    int T_set[MAX_VERTICES];
	 int u,v,i;
    for (u=0; u<n; u++) {
        color[u] = WHITE;
    }
    for(i=0; i<n; i++)
    {S_set[i]=-99; T_set[i]=1; }

    head = tail = 0;
    enqueue(start);
    S_set[start]=1;
    T_set[start]=-1;
    T_set[target]=1;
    pred[start] = -1;

    while (head!=tail) {
        u = dequeue();
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
        for (v=0; v<n; v++) {
            if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0) {
                enqueue(v);

                S_set[v]=1;
                T_set[v]=-1;

                pred[v] = u;
            }

    }

	}

   /* FOR TESTING
	printf("S set: ");
   for(i=0; i<n; i++)
    {if (S_set[i]!=-1) printf("%d ",i); }
   printf("\n");
   */
    return S_set;


}
// Ford-Fulkerson Algorithm


//Compute the maximum flow (min cut) from given source and target
int max_flow (int source, int sink) {
    int i,j,u;
    // Initialize empty flow.
    int max_flow = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            flow[i][j] = 0;
        }
    }
    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) {
        // Determine the amount by which we can increment the flow.
        int increment = oo;
        for (u=sink; pred[u]!=(-1); u=pred[u]) {
            increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
        }
        // Now increment the flow.
        for (u=sink; pred[u]!=(-1); u=pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;  // Reverse in residual
        }
        // Path trace
        for (u=sink; pred[u]!=(-1); u=pred[u]) {
            //printf("%d<-",u);
        }
        //printf("%d adds %d incremental flow\n",source,increment);
        max_flow += increment;
    }
    // No augmenting path anymore. We are done.
    return max_flow;
}


//Function to check if given value val appears in array arr
bool isinArray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++)
    {
        if (arr[i] ==1 && i== val)
            return true;
    }
    return false;
}

// Reading the input file and the main program

void read_input() {
    int a,b,c,i,j;
    // read number of nodes and edges
    scanf("%d %d",&n,&e);

    if (n> MAX_VERTICES || e> MAX_EDGES )
    { printf("Error in number of vertices or edges \n");
      printf("vertices number will not exceed 3000. edges number will not exceed 10000.\n");
      exit(0);
    }

    // initialize empty capacity matrix
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            capacity[i][j] = 0;
        }
    }
    // read edge capacities
    for (i=0; i<e; i++) {
        scanf("%d %d %d",&a,&b,&c);

        if (a > (n-1) || a< 0 || b > (n-1) || b< 0 || c> MAX_CAPACITY || c<0 )
          { printf("Error in vertices adjacent to an edge \n");
            printf("Vertices are positive and < %d \n", (n-1));
            printf("Edges capacity is positive and < %d \n", MAX_CAPACITY);

            exit(0);
          }

        capacity[a][b] = c;
        capacity[b][a] = c;

    }
}

int main () {
   int i,j;
   read_input();
   int s;//start
   int p[n]; //p vector in paper
   int fl[n]; //fl vector in paper
   int* X;


   //Initialize p vector from the article to 0
   for(i=0;i<n;i++)
    {p[i]=0;}

   for(s=1;s<n;s++){

      int t = p[s];//t the sink

      //Compute a minimum cut between nodes s and t=p[sl
      int F= max_flow(s,t);

      //TESTING: print maximum flow for s,t
      //printf("max_flow (%d,%d) :%d\n",s,t,F);

      //Let the s-side of the min cut be X, and the value of the min-cut be F
      X = bfs_2(s,t);

      fl[s]= F;

      for (i=0;i<n;i++)
         {
            //if (i is different from s and i is in X and p[il=t)
            if ( (i != s) &&(isinArray(i,X,n)) && p[i]==t )
               {p[i]=s;}
         }

      //if p[t] is in X
      if (isinArray(p[t],X,n))
         {
             p[s] = p[t];
             p[t] = s;
             fl[s] = fl[t];
             fl[t] = F;
         }

    }// end of for loop s from 1 to n-1 (the n-1 computations)


   /********************************************************************/
   /**   Print the edges of T ie the final pairs (i,p[i]) for from 1 to n
   /**   and edge (i,p[i]) has value fl(i)
   /**      Print results :                                                       **/
   /********************************************************************/

   //printf("_____________________________________________________________________\n");
      for(i=1;i<n;i++)
         {printf("%d %d %d \n", i,p[i], fl[i]);}

         free(X);

    return 0;
}
