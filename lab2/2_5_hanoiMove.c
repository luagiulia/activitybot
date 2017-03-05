#include "simpletools.h"
#include "abdrive.h"

/* task 2.5 robotics
    input : n (no of disks)
            char A, B or C (first peg)
    peg order : C B A
*/

char idToLetter(int i);
int letterToId(char i);
int movePegs(int old, int new);
void hanoi(int size, int start, int end, int other);
int middleId (int s, int e);

enum{LETTER_A = 3, LETTER_B = 2, LETTER_C = 1};

////////////////////////////
/// Enter the constants ! //
////////////////////////////

/* distance in ticks between the middle of the two extreme pegs */
int pegsDistance = 130;
/* initialized in main; distance between two pegs (middles) */
int onePeg;
/* at which peg does the robot start */
int startPeg = 1;
/* where the disks are at the beginning */
int startId = LETTER_C;
/* where we want them in the end */
int endId = LETTER_A;
/* no of disks */
int size = 3;

char idToLetter(int i)
{
  switch(i){
    case LETTER_C: return 'C';
    case LETTER_B: return 'B';
    case LETTER_A: default: return 'A';
  }
}

int letterToId(char i)
{
  switch(i){
    case 'C': return LETTER_C;
    case 'B': return LETTER_B;
    case 'A': default: return LETTER_A;
  }
}


/** drives from peg old to peg new
returns the id of the new peg
*/
int movePegs(int old, int new)
{
  /* getting nb of moves and direction */
  int delta = new - old;
  /* if same pos return */
  if (delta == 0) return new;
  int direction = (delta>0) ? 1 : -1;
  delta = (delta>0) ? delta : -delta;
  /* calculating ticks */
  int ticks = direction*delta*onePeg;
  /* moving the robot */
  drive_goto(ticks, ticks);
  return new;
}

/* recursive hanoi, moves the robot as well */
void hanoi(int size, int start, int end, int other)
{
  if (size == 0){
    return;
  }
  
  hanoi(size - 1, start, other, end);

  char printLeft = idToLetter(start);
  char printRight = idToLetter(end);

  /* going to start */
  startPeg = movePegs(startPeg,start);
  high(26); /* turning 1st LED to indicate 1st to change */
  pause(1000);

  /* going to end */
  startPeg = movePegs(startPeg,end);
  high(27); /* turning 2nd LED to indicate 2nd to change */
  pause(1000);

  low(26);low(27); /* LEDs off, mission accomplished */
  
  hanoi(size - 1, other, end, start);
}

/* gives the id of the other peg */
int middleId (int s, int e)
{
  for (int i = 1;i<=3;i++){
    if (!(i==s || i==e)){
      return i;
    }
  }
  return 0;
}

int main()
{
  /* input the (start/end pegs)/(size) manually !! */
  
  onePeg = (int) pegsDistance/2;

  int midId;
  if (startId==endId){
    midId = startId;
    size = 0;
  }
  else{
    midId = middleId(startId,endId);
  }

  startPeg = startId;
  int hanSize = size;
  hanoi(hanSize, startId, endId, midId);
  return 0;
}