#include "simpletools.h"
#include "abdrive.h"

#define TICKS_ANGLE 0.284
#define SQRT_2 1.4142
/* team 14 */

#define GRIDSIZE 200

enum{right=1,left=-1};
enum{up=1,down=-1};


/* truncating */
int ticksDist(int dist_mm)
{
	return (int) ((dist_mm * (1.0/3.25))+0.5);
}

int diagonalSize(int sideLength)
{
	return (int) ((sideLength*SQRT_2)+0.5);
}

int getToBeginning()
{
	int l = GRIDSIZE;
	drive_goto(-l,-l);
	return 0;
}

int turnRight()
{
	drive_goto(26,-25);
	return 0;
}

int turnLeft()
{
	drive_goto(-26,25);
	return 0;
}

int drawChar(char letter, int letterTicks)
{
	printf("drawChar : %c\n",letter);
	switch(letter){
		case 'A' :
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			turnRight();
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			drive_goto(-letterTicks,-letterTicks);
			turnRight();
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnRight();
			break;
		case 'E':
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			drive_goto(-letterTicks,-letterTicks);
			turnLeft();
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			drive_goto(-letterTicks,-letterTicks);
			turnLeft();
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			break;
		case 'F':
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			drive_goto(-letterTicks,-letterTicks);
			turnLeft();
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnRight();
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnLeft();
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			break;
		case 'H':
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			turnRight();
			drive_goto(letterTicks,letterTicks);
			turnLeft();
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			drive_goto(-letterTicks,-letterTicks);
			turnRight();
			break;
		case 'I':
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			turnLeft();
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			drive_goto(-letterTicks,-letterTicks);
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			turnLeft();
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			break;
		case 'K':
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			drive_goto(- (int) letterTicks/2,- (int) letterTicks/2);
			drive_goto(13,-13);
			drive_goto((int) ((letterTicks/2)*SQRT_2),(int) ((letterTicks/2)*SQRT_2));
			drive_goto(- (int) ((letterTicks/2)*SQRT_2),- (int) ((letterTicks/2)*SQRT_2));
			turnRight();
			drive_goto((int) ((letterTicks/2)*SQRT_2),(int) ((letterTicks/2)*SQRT_2));
			drive_goto(-25,0);
			break;
		case 'L':
			turnLeft();
			drive_goto(letterTicks,letterTicks);
			drive_goto(-letterTicks,-letterTicks);
			turnRight();
			drive_goto((int) letterTicks/2,(int) letterTicks/2);
			break;
		default : return 0;
	}
	printf("drawChar : %c done\n", letter);
	return 0;
}

int drawSpace(int lengthSpaces, int no_letters)
{
	int l = (int) (lengthSpaces / (no_letters));
	drive_goto(l,l);
	return 0;
}

int drawWord(char word[],int length)
{
  int letterSize = GRIDSIZE*2 / (length+1);
  for (int i=0;i<length;i++){
      drawChar(word[i],letterSize);
      drawSpace(letterSize,length);
  }
  return 0;
}

int main(int argc, const char* argv[])
{
  getToBeginning();
  int length = 4;
  drawWord("LIFE",length);
  return 0;
}