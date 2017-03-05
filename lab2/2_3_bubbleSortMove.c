#include "simpletools.h"
#include "abdrive.h"

/* distance in ticks between the middle of the two extreme pegs */
int pegsDistance = 320;
/* initialized in main; distance between two pegs (middles) */
int onePeg;
/* at which peg does the robot start */
int startPeg = 0;
/* length of array */
int n=5;

/** drives from peg old to peg new
returns the id of the new peg
*/
int movePegs(int old, int new)
{
  /* getting nb of moves and direction */
  int delta = new - old;
  
  if (delta == 0) return new; /* if same pos return */
  int direction = (delta>0) ? 1 : -1;
  delta = (delta>0) ? delta : -delta;

  /* calculating ticks */
  int ticks = direction*delta*onePeg;
  
  /* moving the robot */
  drive_goto(ticks,ticks);
  return new;
}


int bubbleSort(int array[], int n)
{
  int swap;
  for (int i = 0; i < n - 1; i++){
    for (int j = 0; j < n - i - 1; j++){
      if (array[j] > array[j+1]){
        /* bubble sort */
        printf("Element %i swapped with %i\n", array[j], array[j+1]);
        swap = array[j];
        array[j] = array[j+1];
        array[j+1] = swap;

        /* moving the robot */
        startPeg = movePegs(startPeg,j);
        high(26); /* turning 1st LED to indicate 1st to change */
        pause(1000);
        startPeg = movePegs(startPeg,j+1);
        high(27); /* turning 2nd LED to indicate 2nd to change */
        pause(1000);
        low(26);low(27); /* LEDs off */

        /* displaying the new state of array (bubble sort step) */
        for (int i = 0; i < n; i++){
          printf("%i\n", array[i]);
        } 
      }
    }
  }
  return 0;
}

int main()
{  
  onePeg = (int) pegsDistance/(n-1);

  int array[n];
  /* input the array manually
    DON'T FORGET TO MODIFY N */
  array[0] = 15;
  array[1] = 33;
  array[2] = 23;
  array[3] = 45;
  array[4] = 3;

  bubbleSort(array, n);
  /* moving to the middle */
  movePegs(startPeg,(int) (n/2));
  /* at the end rotate 90 deg to face down */
  drive_goto(26,-25);
  return 0;  
}