#ifndef obstacles
#define obstacles

//Takes care of avoiding obstacles and path correction

//The main function that corrects the path
void avoid(int *remainingX, int *remainingY, int *orientation, int caller, int *devPointX, int *testcounter);

//The function that rotates the vehicle and updates itscase orientation
void reorient(int angle, int *orientation);

//Function returns the vehicle to the correct path
void returntoPath(int *remainingX, int *remainingY, int *orientation, int *devPointX, int *testcounter);

//Returns X distance to devPointX 
int disFromDevPoint(int *remainingX, int *devPointX);

#endif