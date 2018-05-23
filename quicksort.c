// ... ο κώδικάς σας για την υλοποίηση του quicksort
// με pthreads και thread pool...

#define MAX_ITEMS    100
// simple quicksort implementation
// compile with: gcc -O2 -Wall quicksort.c -o quicksort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
#define CUTOFF 10


void inssort(double *a,int n) {
int i,j;
double t;
  
  for (i=1;i<n;i++) {
    j = i;
    while ((j>0) && (a[j-1]>a[j])) {
      t = a[j-1];  a[j-1] = a[j];  a[j] = t;
      j--;
    }
  }

}


void quicksort(double *a,int n) {
int first,last,middle;
double t,p;
int i,j;

  // check if below cutoff limit
  if (n<=CUTOFF) {
    inssort(a,n);
    return;
  }
  
  // take first, last and middle positions
  first = 0;
  middle = n-1;
  last = n/2;  
  
  // put median-of-3 in the middle
  if (a[middle]<a[first]) { t = a[middle]; a[middle] = a[first]; a[first] = t; }
  if (a[last]<a[middle]) { t = a[last]; a[last] = a[middle]; a[middle] = t; }
  if (a[middle]<a[first]) { t = a[middle]; a[middle] = a[first]; a[first] = t; }
    
  // partition (first and last are already in correct half)
  p = a[middle]; // pivot
  for (i=1,j=n-2;;i++,j--) {
    while (a[i]<p) i++;
    while (p<a[j]) j--;
    if (i>=j) break;

    t = a[i]; a[i] = a[j]; a[j] = t;      
  }
   
  // recursively sort halves
  quicksort(a,i);
  quicksort(a+i,n-i);
  
}
//---------------------------
typedef struct circularQueue_s
{
    int     first;
    int     last;
    int     validItems;
    int     data[MAX_ITEMS];
} circularQueue_t;
void initializeQueue(circularQueue_t *theQueue)
{
    int i;
    theQueue->validItems  =  0;
    theQueue->first       =  0;
    theQueue->last        =  0;
    for(i=0; i<MAX_ITEMS; i++)
    {
        theQueue->data[i] = 0;
    }        
    return;
}
int isEmpty(circularQueue_t *theQueue)
{
    if(theQueue->validItems==0)
        return(1);
    else
        return(0);
}
int putItem(circularQueue_t *theQueue, int theItemValue)
{
    if(theQueue->validItems>=MAX_ITEMS)
    {
        printf("The queue is full\n");
        printf("You cannot add items\n");
        return(-1);
    }
    else
    {
        theQueue->validItems++;
        theQueue->data[theQueue->last] = theItemValue;
        theQueue->last = (theQueue->last+1)%MAX_ITEMS;
    }
}
int getItem(circularQueue_t *theQueue, int *theItemValue)
{
    if(isEmpty(theQueue))
    {
        printf("isempty\n");
        return(-1);
    }
    else
    {
        *theItemValue=theQueue->data[theQueue->first];
        theQueue->first=(theQueue->first+1)%MAX_ITEMS;
        theQueue->validItems--;
        return(0);
    }
}

void printQueue(circularQueue_t *theQueue)
{
    int aux, aux1;
    aux  = theQueue->first;
    aux1 = theQueue->validItems;
    while(aux1>0)
    {
        printf("Element #%d = %d\n", aux, theQueue->data[aux]);
        aux=(aux+1)%MAX_ITEMS;
        aux1--;
    }
    return;
}
int main(void)
{
	double *a;
	int i;
    int l;
    int readValue;
    circularQueue_t   myQueue;
    
    initializeQueue(&myQueue);
    for(l=0; l<MAX_ITEMS+1; l++)
    {
        putItem(&myQueue, l);
    }
    printQueue(&myQueue);
    
    for(l=0; l<MAX_ITEMS/2; l++)
    {
        getItem(&myQueue, &readValue);
        printf("readValue = %d\n", readValue);
    }
    printQueue(&myQueue);
    //exit(EXIT_SUCCESS);
    //---------------
    a = (double *)malloc(N*sizeof(double));
  if (a==NULL) {
    printf("error in malloc\n");
    exit(1);
  }

  // fill array with random numbers
  srand(time(NULL));
  for (i=0;i<N;i++) {
    a[i] = (double)rand()/RAND_MAX;
  }

  // simple quicksort
  quicksort(a,N);

  // check sorting
  for (i=0;i<(N-1);i++) {
    if (a[i]>a[i+1]) {
      printf("Sort failed!\n");
      break;
    }
  }  

  free(a);
  
  return 0;
    
    
}

