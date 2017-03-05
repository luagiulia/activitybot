#include "simpletools.h"

/* task 2.5 robotics
    input : n (no of disks)
            char A, B or C (first peg)
    peg order : C B A
*/

char idToLetter(int i);
int letterToId(char i);
void hanoi(int size, int start, int end, int other, int * pegs[]);
int middleId (int s, int e);
int initPegs(int * pegs[]);
int movePegArray(int old, int new, int * pegs[]);
int printPegArray(int * pegs[]);

enum{LETTER_A = 3, LETTER_B = 2, LETTER_C = 1};

////////////////////////////
/// Enter the constants ! //
////////////////////////////

/* at which peg does the robot start */
int startPeg = 1;
/* where the disks are at the beginning */
int startId = LETTER_C;
/* where we want them in the end */
int endId = LETTER_A;
/* no of disks */
int size = 4;

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

/* recursive hanoi, moves the robot as well */
void hanoi(int size, int start, int end, int other, int * pegs[])
{
  if (size == 0){
    return;
  }
  
  hanoi(size - 1, start, other, end, pegs);

  char printLeft = idToLetter(start);
  char printRight = idToLetter(end);
  /* we move start to end */
  printf("===================\n\n");
  printf("move %c to %c\n\n",printLeft,printRight);
  movePegArray(start, end, pegs);
  printPegArray(pegs);
  hanoi(size - 1, other, end, start, pegs);
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

/* init peg array to know position at each step */
int initPegs(int * pegs[])
{
  for (int i=0;i<size*3;i++){
    if (i%3 == (startId-1)%3){
      (*pegs)[i] = 1;
    }
    else {
      (*pegs)[i] = 0;
    }
  }
  return 0;
}

/* doesn't check errors because hanoi algo is good */
int movePegArray(int old, int new, int * pegs[])
{
  for (int i=old-1;i<size*3;i+=3){
    if ((*pegs)[i]){
      (*pegs)[i] = 0;
      (*pegs)[i-(i%3)+new-1] = 1;
      return 0;
    }
  }
  printf("Error in movePeg : operation impossible.\n");
  return 1;
}

/* hey it's beautiful */
int printPegArray(int * pegs[])
{
  for (int i=0;i<size*3;i++){
    if ((*pegs)[i]){
      printf("X ");
    }
    else {
      printf("- ");
    }
    if (i%3==2){
      printf("   (size = %i)\n",(int)(i/3)+1);
    }
  }
  printf("C B A\n\n");
  return 0;
}

int main()
{
  /* input the (start/end pegs)/(size) manually !! */
  
  /* peg pos array */
  int *pegs[size*3];
  initPegs(pegs);
  
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
  hanoi(hanSize, startId, endId, midId, pegs);
  return 0;
}