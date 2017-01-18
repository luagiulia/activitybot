#include "simpletools.h"
#include "abdrive.h"

#define TICKS_ANGLE 0.284
#define SQRT_2 1.4142

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
	int distanceTo = (diagonalSize(212));
	drive_goto(distanceTo,distanceTo);
	turnAngle(138,right);
}

int drawChar(char letter)
{
	switch(letter){
		case 'A' :
		break;
		case 'B' :
		break;
		case 'C' :
		break;
		case 'D' :
		break;
		case 'E' :
		break;
		case 'F' :
		break;
		case 'G' :
		break;
		case 'H' :
		break;
		case 'I' :
		break;
		case 'J' :
		break;
		case 'K' :
		break;
		case 'L' :
		break;
		case 'M' :
		break;
		case 'N' :
		break;
		case 'O' :
		break;
		case 'P' :
		break;
		case 'Q' :
		break;
		case 'R' :
		break;
		case 'S' :
		break;
		case 'T' :
		break;
		case 'U' :
		break;
		case 'V' :
		break;
		case 'W' :
		break;
		case 'X' :
		break;
		case 'Y' :
		break;
		case 'Z' :
		break;
		default : return 0;
	}
}

int main(int argc, const char* argv[])
{
  getToLowLeft();
  return 0;
}