#include "simpletools.h"
#include "abdrive.h"

#define TICKS_ANGLE 0.284

enum{right=1,left=-1};

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
}

int main(int argc, const char* argv[])
{
  int ticksForMeter = ticksDist(100);
  int i;
  for(i=0;i<4;i++){
  	drive_goto(ticksForMeter,ticksForMeter);
  	turnAngle(90,right);
  }
  return 0;
}