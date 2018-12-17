#ifndef moves
#define moves

//Defines the basic movement control of the vehicle

//Rotates the vehicle
void rotate(int angle);

//Initializes movement
void start(int distance);

//Moves the vehicle forward
int forward(int distance, int *remainingX, int *remainingY, int *orientation, int caller, int *devPointX, int *testcounter);

//Updates the correct distance based on orientation
void updateDis(int moved, int *remainingX, int *remainingY, int *orientation);

#endif