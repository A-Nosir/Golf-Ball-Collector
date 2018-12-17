#ifndef multiball
#define multiball

//Defines the structures and functions needed to handle multiple balls

//The structure that define a ball attributes
typedef struct{
	
	int distance;			//distance = distance to detected ball in cm
	int angle;				//angle = signed angle to face detected ball
	int check;				//check =  whether a second object detection run is needed. True = needed. False = not needed
	int offsetDis;			//Distance from base to current location. 0 if starting at base
	int offsetAng;			//Angle between base and current location. 0 if starting at base
	
}  Ball; 

//Function that counts balls by counting lines in the cameras output
int countBalls(FILE *file);


#endif								
