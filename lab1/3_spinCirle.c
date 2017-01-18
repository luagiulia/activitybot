#include "simpletools.h"
#include "abdrive.h"

#define TICKS_ANGLE 0.284

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

int main(int argc, const char* argv[])
{
  turnAngle(360,right);
  return 0;
}