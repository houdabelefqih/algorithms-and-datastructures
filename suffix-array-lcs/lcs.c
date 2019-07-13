

/* SOURCE  : http://ranger.uta.edu/~weems/NOTES5311/LAB/LAB3SPR18/SAcommonSubStr2.c
** HOUDA BELEFQIH
** 1001511875
** SPRING 2018
** LAB3 :
*/


/*  ON OMEGA SERVER
*
*  COMPILE WITH : gcc -o lab3 1001511875.c
*
*  RUN PROGRAM WITH : ./lab3 < testfile.txt (with file of data)
*           OR WITH : ./lab3 (for direct user input)
*/



// Use suffix array and LCP to compute
// longest common substring of two input strings. BPW

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char s[1000000],s1[501],s2[501],s3[501];
int n,           // length of s[] including \0
  sa[1000000],   // suffix array for s[]
  rank[1000000], // rank[i] gives the rank (subscript) of s[i] in sa[]
  lcp[1000000];  // lcp[i] indicates the number of identical prefix symbols
                 // for s[sa[i-1]] and s[sa[i]]

int whichString(int dollarPos, int poundPos, int stringStart)
{
   if (stringStart < dollarPos){return 0;}
   else if (stringStart >dollarPos && stringStart< poundPos){return 1;}
   else if (stringStart > dollarPos  && stringStart> poundPos){return 2;}
   else return -1;

}

int suffixCompare(const void *xVoidPt,const void *yVoidPt)
{
// Used in qsort call to generate suffix array.
int *xPt=(int*) xVoidPt,*yPt=(int*) yVoidPt;

return strcmp(&s[*xPt],&s[*yPt]);
}

void computeRank()
{
// Computes rank as the inverse permutation of the suffix array
int i;

for (i=0;i<n;i++)
  rank[sa[i]]=i;
}

void computeLCP()
{
//Kasai et al linear-time construction
int h,i,j,k;

h=0;  // Index to support result that lcp[rank[i]]>=lcp[rank[i-1]]-1
for (i=0;i<n;i++)
{
  k=rank[i];
  if (k==0)
    lcp[k]=(-1);
  else
  {
    j=sa[k-1];
    // Attempt to extend lcp
    while (i+h<n && j+h<n && s[i+h]==s[j+h])
      h++;
    lcp[k]=h;
  }
  if (h>0)
    h--;  // Decrease according to result
}
}

int fibIndex=0;

void fib(k)
int k;
{
if (k==0)
  s[fibIndex++]='1';
else if (k==1)
  s[fibIndex++]='0';
else
{
  fib(k-1);
  fib(k-2);
}
}

int main()
{
int i,j,l,k,p,dollarPos,poundPos,LCSpos=0,LCSlength=0;


scanf("%s",s1);
scanf("%s",s2);
scanf("%s",s3);

for (i=0;s1[i]!='\0';i++)
  {s[i]=s1[i];}

dollarPos=i;
s[i++]='$';

for (j=0;s2[j]!='\0';j++)
  {s[i+j]=s2[j];}

poundPos=i+j;
s[i+j]='#';
j++;


for (l=0;s3[l]!='\0';l++)
  {s[i+j+l]=s3[l];}

s[i+j+l]='\0';

n=i+j+l+1;

/*
fib(4);
fib(6);
dollarPos=fibIndex;
s[fibIndex++]='$';
fib(5);
fib(7);
s[fibIndex]='\0';
n=fibIndex+1;
*/


/*
for (i=0;i<1000;i++)
  s[i]='a';
s[1000]='b';
s[1001]='\0';
*/
/*
s[0]='a';
for (i=1;i<1000;i++)
  s[i]='b';
s[1000]='\0';
*/

//n=strlen(s)+1;
printf("n is %d\n",n);

// Quick-and-dirty suffix array construction
for (i=0;i<n;i++)
  sa[i]=i;
qsort(sa,n,sizeof(int),suffixCompare);
computeRank();
computeLCP();
if (n<200)
{
  printf("i   sa  suffix                              lcp s rank lcp[rank]\n");
  for (i=0;i<n;i++)
    printf("%-3d %-3d %-35.35s %-3d %c  %-3d  %-3d\n",
      i,sa[i],&s[sa[i]],lcp[i],s[i],rank[i],lcp[rank[i]]);
}

int s1s2s3[3]={0,0,0};
int xyz_in[3]={-1,-1,-1};
int final_xyz[3]={-1, -1,-1};



for (i=3;i<n;i++)
  {
     int j = whichString(dollarPos, poundPos,sa[i]);

      /*
     //for testing
     printf("i=%d j=%d\n",i,j);
     printf("j%2=%d j+1%%2=%d\n",(j+1)%3,(j+2)%3);

     printf("s1s2s3[0]= %d s1s2s3[1]= %d s1s2s3[2]= %d\n",s1s2s3[0],s1s2s3[1],s1s2s3[2]);
     printf("xyz[0]= %d xyz[1]= %d xyz[2]= %d\n",xyz_in[0],xyz_in[1],xyz_in[2]);
      */

           if (s1s2s3[j]== 0 && s1s2s3[(j+1)%3]== 0 && s1s2s3[(j+2)%3]== 0)
           {s1s2s3[j]=1;
            xyz_in[0]=i;
           }

           else if (s1s2s3[j]== 0 && s1s2s3[(j+1)%3]== 0 && s1s2s3[(j+2)%3]== 1)
           {s1s2s3[j]=1;

            xyz_in[1]=i;
           }

           else if (s1s2s3[j]== 0 && s1s2s3[(j+1)%3]== 1 && s1s2s3[(j+2)%3]== 0)
           {s1s2s3[j]=1;
            xyz_in[1]=i;
           }

           else if (s1s2s3[j]== 0 && s1s2s3[(j+1)%3]== 1 && s1s2s3[(j+2)%3]== 1)
           {s1s2s3[j]=1;
            xyz_in[2]=i;
           }


           else if (s1s2s3[j]== 1 && s1s2s3[(j+1)%3]==1  && s1s2s3[(j+2)%3]== 0
               && (whichString(dollarPos, poundPos, sa[i-1]) !=j ))
           {
              xyz_in[1]=i;
              xyz_in[0]=i-1;

           }

           else if (s1s2s3[j]== 1 && s1s2s3[(j+1)%3]==0  && s1s2s3[(j+2)%3]== 1
               && (whichString(dollarPos, poundPos, sa[i-1]) != j))
           {
              xyz_in[1]=i;
              xyz_in[0]=i-1;

           }

            else
               {
                  //printf("No combination at %d\n",i);
               }

            /*
            //for testing
            printf("\nAFTER\n");
            printf("s1s2s3[0]= %d s1s2s3[1]= %d s1s2s3[2]= %d\n",s1s2s3[0],s1s2s3[1],s1s2s3[2]);
            printf("xyz[0]= %d xyz[1]= %d xyz[2]= %d\n",xyz_in[0],xyz_in[1],xyz_in[2]);
            printf("\n________________________________________________________________________\n");
            */


   if (s1s2s3[0]== 1 && s1s2s3[1]== 1 && s1s2s3[2]== 1)
   {
     int w, minIndex=0, minLCP =999999;

     for(w=xyz_in[1]; w<=xyz_in[2]; w++)
     {
        if (lcp[w] < minLCP)
        {minLCP = lcp[w]; minIndex =w;}
     }

     if (minLCP > LCSlength)
        {
           LCSpos=minIndex;
           LCSlength=lcp[minIndex];

           //KEEPING TRACK OF XYZ
           final_xyz[0]= xyz_in[0];
           final_xyz[1]= xyz_in[1];
           final_xyz[2]= xyz_in[2];

        }


   int ignored = whichString(dollarPos, poundPos, sa[xyz_in[0]]);
   s1s2s3[ignored]= 0;
   xyz_in[1] = xyz_in[2];
   xyz_in[0] = xyz_in[2] -1;




  }// end if all three suffix strings present


  }//end for loop

printf("Length of longest common substring is %d\n",LCSlength);
//printf("at position %d\n",LCSpos);

printf("x at: %d, y at: %d, z at: %d\n", final_xyz[0], final_xyz[1],final_xyz[2]);
for (i=0;i<LCSlength;i++)
  printf("%c",s[sa[LCSpos]+i]);
printf("\n");
}
