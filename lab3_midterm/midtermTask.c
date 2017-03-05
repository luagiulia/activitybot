#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"
#include <stdlib.h>

// change according to track
// valid now for task5 map 1 in simulator
#define FORWARD_SPEED 10
#define BACKWARD_SPEED 82
#define KP_FORWARD 1.5
#define KP_BACKWARD 3.7
#define RETURN_BIAS 1

#define INC_DELAY_FACTOR 30

#define ROBOT_WIDTH 105.8
#define TICKS_TO_MM 3.249

typedef struct node {
  int leftTicks;
  int rightTicks;
  struct node *next;
} TicksDiffLinked;


/////////////
// GLOBALS //
/////////////

TicksDiffLinked *head = NULL;
int speedCorrection;
int previousLeftTicks = 0; 
int previousRightTicks = 0;

double spotDistance[2]={0,0};
double prevDistance[2]={0,0};
double dX = 0;
double dY = 0;
double spotAngle = 0;
// mm distance for left and right wheel
double distanceWheels[2]={0,0};
// x, y, angle array
double coord[3]={0,0,0};
FILE* fp;

////////////////
/// Functions //
////////////////

// gets ticks for each wheel, converts to milimeters
void getDistanceWheels()
{
  int ticksList[2];
  drive_getTicks(&ticksList[0], &ticksList[1]);
  distanceWheels[0] = (double) (ticksList[0]) * TICKS_TO_MM;
  distanceWheels[1] = (double) (ticksList[1]) * TICKS_TO_MM;
}

// distanceTravelled[left] - distanceTravalled[right] / distanceBtwWheels
double getAngleChange()
{
  return (distanceWheels[0] - distanceWheels[1]) / ROBOT_WIDTH;
}

// distance center circle (position change) to middle of robot
double radiusMiddle(double spotAngle)
{
  double radiusLeft = spotDistance[0] / spotAngle;
  double radiusRight = spotDistance[1] / spotAngle;
  return (radiusLeft + radiusRight) / 2;
}

// main coord function : gets distance travelled, angle, it updates coord
void getCoordinates()
{
  getDistanceWheels();
  double deltaAngle = getAngleChange();
  double r = radiusMiddle(spotAngle);

  if (deltaAngle == 0) {
    coord[0] = spotDistance[0];
    coord[1] = 0;
  }
  else {
    coord[0] = r * sin(spotAngle + deltaAngle) - r * sin(spotAngle);
    coord[1] = r * cos(spotAngle + deltaAngle) - r * cos(spotAngle);
  }
  coord[2] = deltaAngle;
  spotAngle = deltaAngle;
}

// add dx and dy, gets spot distance, updates sum through getCoordinates()
void calculateCoordinates()
{
  getDistanceWheels();
  spotDistance[0] = distanceWheels[0] - prevDistance[0];
  spotDistance[1] = distanceWheels[1] - prevDistance[1];
  prevDistance[0] = distanceWheels[0];
  prevDistance[1] = distanceWheels[1];

  getCoordinates();
  dX += coord[0];
  dY += coord[1];
  spotAngle = coord[2];
}

int infraredDelta() {
  int left = 0;
  int right = 0;

  // Calculating the distances from the right and left walls
  for (int dacVal = 0; dacVal < 160; dacVal += 8) {
    dac_ctr(26, 0, dacVal);
    freqout(11, 1, 38000);
    left += input(10);

    dac_ctr(27, 1, dacVal);
    freqout(1, 1, 38000);
    right += input(2);
  }
  return right - left;
}

// Calculate the left and right wheels' ticks 
// since last call of the function
void tickDeltas(int *leftTicks, int *rightTicks) {
  int currentLeftTicks;
  int currentRightTicks;
  drive_getTicks(&currentLeftTicks, &currentRightTicks);

  *leftTicks = currentLeftTicks - previousLeftTicks;
  *rightTicks = currentRightTicks - previousRightTicks;

  previousLeftTicks = currentLeftTicks;
  previousRightTicks = currentRightTicks;
}

// Push right and left wheels' ticks into the stack
void pushTicks(int rightTicks, int leftTicks) {
  TicksDiffLinked *new = malloc(sizeof(TicksDiffLinked));
  (*new).leftTicks = leftTicks;
  (*new).rightTicks = rightTicks;
  (*new).next = head;
  head = new;
}

void driveForward() {
  // Checking the front distance (11 cm because of time to stop)
  // and keeping a delay_increment to simulate time delay with each push
  for (int delay_increment = 0; ping_cm(8) > 11; delay_increment++){
    // P controller
    speedCorrection = (infraredDelta() * KP_FORWARD) / 2;
    // Apply speed correction
    drive_speed(FORWARD_SPEED + speedCorrection, FORWARD_SPEED - speedCorrection);
    // Pushing right and left wheel's ticks in reverse order.
    // This is needed to return back correctly.
    if (delay_increment % INC_DELAY_FACTOR == 0) {
      int currentLeft;
      int currentRight;
      tickDeltas(&currentLeft, &currentRight);
      pushTicks(currentRight, currentLeft);
      calculateCoordinates();
    }
  }
  // Distance is around 10cm
  // Time to stop
  drive_speed(0, 0);
}

void updateTickDeltas() {
  int currentLeftTicks;
  int currentRightTicks;
  drive_getTicks(&currentLeftTicks, &currentRightTicks);
  previousLeftTicks = currentLeftTicks;
  previousRightTicks = currentRightTicks;
}

void returnBack() {
  // Adjust values of previousLeftTicks and previousRightTicks after 180° turn
  updateTickDeltas();

  // P error constants 
  int leftCorrection;
  int rightCorrection;

  // Current values of left and right ticks 
  int currentLeftTicks;
  int currentRightTicks;

  int leftTicksRemaining;
  int rightTicksRemaining;

  // Looping until the end of the stack
  // in which case it breaks out of loop
  TicksDiffLinked *iterator = head;
  while (iterator) {
    // Reset current tick values 
    currentLeftTicks = 0;
    currentRightTicks = 0;

    // Update target ticks
    leftTicksRemaining = (*iterator).leftTicks;
    rightTicksRemaining = (*iterator).rightTicks;

    // Automatically adjust the speed of the robot by continuosly comparing 
    // the current ticks with the corresponding target ticks previously stored on the stack.
    // The RETURN_BIAS is introduced because of possible errors in the sensors data.
    while (currentLeftTicks <= (leftTicksRemaining + RETURN_BIAS) 
            && currentRightTicks <= (rightTicksRemaining + RETURN_BIAS)) {
      // P Controller
      leftCorrection = KP_BACKWARD * (currentLeftTicks - (leftTicksRemaining + RETURN_BIAS));
      rightCorrection = KP_BACKWARD * (currentRightTicks - (rightTicksRemaining + RETURN_BIAS));
      // Apply speed corrections
      drive_speed(BACKWARD_SPEED + leftCorrection, BACKWARD_SPEED + rightCorrection);

      // Upating current left and right ticks since the beginning
      // of the iteration
      drive_getTicks(&currentLeftTicks, &currentRightTicks);
      currentLeftTicks -= previousLeftTicks;
      currentRightTicks -= previousRightTicks;
    }
    // Target ticks distances traversed.
    // Update the previous left and right ticks
    // and go on to the next target ticks on the stack.
    drive_getTicks(&previousLeftTicks, &previousRightTicks);
    iterator = (*iterator).next;
  }
  // Beginning position reached
  // Time to stop
  drive_speed(0, 0);
}

// Write the final displacement and the angle change to a file in the SD card
void outputSD(FILE* fp, double displacement, double angle) { 
  sd_mount(22, 23, 24, 25);
  fp = fopen("output.txt", "w");
  fprintf(fp, "%.2f,%.2f\n", displacement, angle);
  fclose(fp);
}

int main() {
  driveForward();

  double displacement = sqrt(pow(dX, 2) + pow(dY, 2));
  double angle = atan(dY / dX);
  // printf("displacement: %.2f, angle: %.2f\n", displacement, angle);

  // Turn 180° degrees
  drive_goto(52, -51);

  // SD only works in simulator
  outputSD(fp, displacement, angle);

  returnBack();
  return 0;
}

