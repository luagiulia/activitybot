#include "simpletools.h"


int bubbleSort(int array[], int n)
{
  int swap;
  for (int i = 0; i < n - 1; i++){
    for (int j = 0; j < n - i - 1; j++){
      if (array[j] > array[j+1]){
        /* show current array and change to appear with arrow */
        printf("bubbleSort\t: ");
        for (int i = 0; i < n; i++){
          printf("%3i", array[i]);
          if (i==j) printf(" <=> ");
          else printf("     ");
        }
        putchar('\n');                          
        /* bubble sort */
        swap = array[j];
        array[j] = array[j+1];
        array[j+1] = swap;
        /* displaying the new state of array */
        printf("new array\t: ");
        for (int i = 0; i < n; i++){
          printf("%3i     ", array[i]);  
        } 
        putchar('\n');
      }
    }
  }
  return 0;
}

int main()
{  
  int n;
  printf("Enter number of elements\n");
  scanf(" %i",&n);
  int array[n];
  printf("Enter %i integers\n",n);
  for (int i=0;i<n;i++){
    scanf(" %i", &array[i]);
  }
  bubbleSort(array, n);
  return 0;  
}