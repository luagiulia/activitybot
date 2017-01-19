#include "simpletools.h"
#include "abdrive.h"

#define TICKS_ANGLE 0.284
#define SQRT_2 1.4142

#define GRIDSIZE 200

enum{right=1,left=-1};
enum{up=1,down=-1};

int ticksAngle(int angDeg)
{
	return (int) ((angDeg * TICKS_ANGLE)+0.5);
}

/* truncating */
int ticksDist(int dist_mm)
{
	return (int) ((dist_mm * (1.0/3.25))+0.5);
}

/* angle > 0 */
int turnAngle(int angDeg, int direction)
{
	int noTicks = ticksAngle(angDeg);
	drive_goto(direction*noTicks,-direction*noTicks);
	return 0;
}

int getToAngle(int *oldAngle, int newAngle)
{
	int delta = *oldAngle - newAngle;
	int sign;
	if(delta>0) {sign = 1;}
	else {sign = -1;delta = -delta;}
	turnAngle(delta,sign);
	return 0;
}

int diagonalSize(int sideLength)
{
	return (int) ((sideLength*SQRT_2)+0.5);
}

int getToLowLeft()
{
	turnAngle(135,right);
	int distanceTo = (diagonalSize(190));
	drive_goto(distanceTo,distanceTo);
	turnAngle(138,right);
}

int drawChar(char letter)
{
	switch(letter){
		case 'A' :
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(180,1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    // get back
    turnAngle(90,1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,1);
		break;

		case 'E' :
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);

    // Get back to starting position
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2); 
    turnAngle(90,1);
		break;

		case 'F' :
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
		break;

		case 'H' :
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE, GRIDSIZE);

    // Get back to starting position
    turnAngle(90,1);
    drive_goto(GRIDSIZE, GRIDSIZE); 
    turnAngle(90,1);
		break;

		case 'I' :
    turnAngle(90,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE,GRIDSIZE);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE, GRIDSIZE);

    // Get back to the starting position
    turnAngle(90,1);
		break;

		case 'J' :
    drive_goto(GRIDSIZE/8, GRIDSIZE/8);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/8, GRIDSIZE/8);
    turnAngle(90, -1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(90, -1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90, 1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180,1);
    drive_goto(GRIDSIZE, GRIDSIZE);

    // Get back to the starting position
    turnAngle(90, -1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(180, -1);
		break;

		case 'K' :
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(180,1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(135,-1);
    drive_goto(diagonalSize(GRIDSIZE/2), diagonalSize(GRIDSIZE/2));
    turnAngle(180,1);
    drive_goto(diagonalSize(GRIDSIZE/2), diagonalSize(GRIDSIZE/2));
    turnAngle(90,-1);
    drive_goto(diagonalSize(GRIDSIZE/2), diagonalSize(GRIDSIZE/2));
    turnAngle(180,1);
    drive_goto(diagonalSize(GRIDSIZE/2), diagonalSize(GRIDSIZE/2));

    // Get back to the starting position
    turnAngle(135,-1);
    drive_goto(GRIDSIZE/2, GRIDSIZE/2);
    turnAngle(180, -1);
		break;

		case 'L' :
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(180,1);
    drive_goto(GRIDSIZE, GRIDSIZE);
    turnAngle(90,-1);
    drive_goto(GRIDSIZE/4, GRIDSIZE/4);

    // Get back to the starting position
    turnAngle(180,1);
    drive_goto(GRIDSIZE/4, GRIDSIZE/4);
    turnAngle(90, 1);
		break;

		default : return 0;
	}
}

int drawWord(char word[])
{
    int length = sizeof(word)/sizeof(char);
    for (int i=0;i<length;i++){
        drawChar(word[i]);
    }
    return 0;
}

int main(int argc, const char* argv[])
{
  getToLowLeft();
  drawWord("AEFHIJKL");
  return 0;
}