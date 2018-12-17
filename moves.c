#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include"definitions.h"
#include"moves.h"
#include "obstacles.h"


//Rotates the vehicle
void rotate(int angle)
{
	printf("Turn %i degrees \n", angle);
	return;
}

//Initializes all the values for movement control
void start(int distance)
{
	int orient = FORWARD;
	int *orientation;
	orientation = &orient;
	
	int moved = 0;
	int toDoX, toDoY;
	int *remainingX, *remainingY;
	
	toDoX = distance - moved;
	toDoY = 0;

	remainingX =  &toDoX;
	remainingY = &toDoY;
	
	int devPoint = 0;		//Used by pointer 
	int *devPointX;			//It is the X axis point at which the very first deviation from the correct path occurs
	devPointX = &devPoint;
	
	//These values are used exclusively for testing
	int count = 0;
	int *testcounter;
	testcounter = &count;

	forward(0, remainingX, remainingY, orientation, START, devPointX, testcounter);
	
	return;
}

//Moves the vehicle forward
//Will take care of moving in a straight line
//If an obstacle is encountered, it will call the avoid function
//The Caller IDs are:
//	START: is the initial call, and is aiming for the ball
//	AVOID: is the avoid function, and moves a fixed distance only
//	NESTED: is used to return that the ball encountered additional obstacles
//******THE testcounter IS ONLY FOR TESTING*********
int forward(int distance, int *remainingX, int *remainingY, int *orientation, int caller, int *devPointX, int *testcounter)
{
	int *determinant;			//It is the value used to decide whether a called forward function accomplished it's task
	
	if(caller == START)
	{
		determinant = remainingX;
	}
	else
	{
		determinant = &distance;
		distance = abs(distance);
	}
	
	//The movement part
	while(*determinant > 0 )
	{
		*testcounter = *testcounter + 1;

		if(*testcounter == 3 || *testcounter == 5 || *testcounter == 8 || *testcounter == 190 )
		{
			printf("\nObstacle detected\n");
			
			if(caller == START)
			{
				*devPointX = *remainingX;	//Saves the X position of the first deviation. Used to find way back
			}
			
			avoid(remainingX, remainingY, orientation, caller, devPointX,testcounter);
			
			if(caller == AVOID)
			{	
				caller = NESTED;
				break;
			}
		}
		else	
		{
			updateDis(10, remainingX, remainingY, orientation);
			printf("Moved 10 cm. remainingX is %d, remainingY is %d\n", *remainingX, *remainingY);
			
			if (caller != START)
			{
				distance = distance - 10;
			}

			//logic when crossing y-axis
			if((*orientation == LEFT || *orientation == RIGHT) && *remainingY == 0)
			{
				if(disFromDevPoint(remainingX, devPointX) >= 0 && distance < 20)
				{
					forward(20, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				}

				return NESTED;
			}
		}
	}

	return caller;
}

//Updates the correct remaining distance
void updateDis(int moved, int *remainingX, int *remainingY, int *orientation)
{
	switch(*orientation)	
	{
		case FORWARD :
			*remainingX = *remainingX - moved;
			break;
		case BACKWARD :
			*remainingX = *remainingX + moved;
			break;
		case RIGHT :
			*remainingY = *remainingY - moved;
			break;
		case LEFT :
			*remainingY = *remainingY + moved;
			break;
	}

	return;
}


