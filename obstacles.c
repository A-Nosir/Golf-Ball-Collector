#include <stdio.h>
#include <stdbool.h>

#include "definitions.h"
#include "obstacles.h"
#include "moves.h"

//avoid obstacles by makin a square around it
//******THE testcounter IS ONLY FOR TESTING*********
void avoid(int *remainingX, int *remainingY, int *orientation, int caller, int *devPointX, int *testcounter)
{	
	int multiAvoid;					//Used to check if avoid was called recursively.	
	int primary, secondary;			//Used to deteremine direction of turns based on mode

	if(*remainingY <= 0)	
	{	//This mode is the default
		primary = CLOCKWISE;			//sequence of turns: Right, Left, Left, Right
		secondary = ANTICLOCKWISE;
	}
	else
	{	//This mode is entered only if the default mode was not possible
		primary = ANTICLOCKWISE;		//Sequence of turns: Left, Right, Right, Left
		secondary = CLOCKWISE;
	}

	//Step 1 
	reorient(primary, orientation);
	multiAvoid = forward(20, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
	if(multiAvoid == NESTED)
	{
		returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
		return;
	}
	
	//Step 2
	reorient(secondary, orientation);
	multiAvoid = forward(20, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
	if(multiAvoid == NESTED || (*orientation == RIGHT && *remainingY > 0) || (*orientation == LEFT && *remainingY < 0))
	{
		returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
		return;
	}
	
	//Step 3
	reorient(secondary, orientation);
	multiAvoid = forward(20, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
	if(multiAvoid == NESTED)
	{
		returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
		return;
	}
	
	//Step 4 only done if not avoiding multiple obstacles, i.e. avoid is called by first forward
	if(caller == START)
	{
		reorient(primary, orientation);
	}

	return;
}

void reorient(int angle, int *orientation)
{
	rotate(angle);
	
	if(angle == 180)
	{
		switch(*orientation)	
		{
			case FORWARD :
				*orientation = BACKWARD;
				break;
			case BACKWARD :
				*orientation = FORWARD;
				break;
			case RIGHT :
				*orientation = LEFT;
				break;
			case LEFT :
				*orientation = RIGHT;
				break;
		}
	}
	else if(angle > 0)	//Checks if rotation is clockwise
	{
		switch(*orientation)	
		{
			case FORWARD :
				*orientation = RIGHT;
				break;
			case BACKWARD :
				*orientation = LEFT;
				break;
			case RIGHT :
				*orientation = BACKWARD;
				break;
			case LEFT :
				*orientation = FORWARD;
				break;
		}
	}
	else
	{
		switch(*orientation)	
		{
			case FORWARD :
				*orientation = LEFT;
				break;
			case BACKWARD :
				*orientation = RIGHT;
				break;
			case RIGHT :
				*orientation = FORWARD;
				break;
			case LEFT :
				*orientation = BACKWARD;
				break;
		}
	}

	return;
}

void returntoPath(int *remainingX, int *remainingY, int *orientation, int *devPointX, int *testcounter)
{
	int multiAvoid;

	switch(*orientation)	
	{
		case FORWARD :
			if(disFromDevPoint(remainingX, devPointX) >= 0)
			{
				multiAvoid = forward((disFromDevPoint(remainingX, devPointX) + 10), remainingX, remainingY, orientation, AVOID, devPointX);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX);
					return;
				}
			}
	
			if(*remainingY > 0)
			{
				reorient(90, orientation);
				multiAvoid = forward(*remainingY, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
					return;
				}
	
				reorient(-90, orientation);
			}    
			else if(*remainingY < 0)
			{
				reorient(-90, orientation);
				multiAvoid = forward(*remainingY, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
					return;
				}

				reorient(90, orientation);
			} 

			break;

		case BACKWARD :
			reorient(180, orientation);
			returntoPath(remainingX, remainingY, orientation, devPointX);
			break;

		case RIGHT :
			if (disFromDevPoint(remainingX, devPointX) > 0)
			{	//Face forward then recall returntoPath
				reorient(-90, orientation);
				returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
				return;
			}

			if(*remainingY > 0)
			{
				multiAvoid = forward(*remainingY, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
					return;
				}
	
				reorient(-90, orientation);
			}   
			else if(*remainingY < 0)
			{
				reorient(180, orientation);
				multiAvoid = forward(*remainingY, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
					return;
				}

				reorient(90, orientation);
			}
			else
			{
				reorient(-90,orientation);
			}

			break;

		case LEFT :
			if (disFromDevPoint(remainingX, devPointX) > 0)
			{	//Face forward then recall returntoPath
				reorient(90, orientation);
				returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
				return;
			}

			if(*remainingY > 0)
			{
				reorient(180, orientation);
				multiAvoid = forward(*remainingY, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
					return;
				}

				reorient(-90, orientation);
			}     
			else if(*remainingY < 0)
			{
				multiAvoid = forward(*remainingY, remainingX, remainingY, orientation, AVOID, devPointX, testcounter);
				if(multiAvoid == NESTED)
				{
					returntoPath(remainingX, remainingY, orientation, devPointX, testcounter);
					return;
				}

				reorient(90, orientation);
			}
			else
			{
				reorient(90,orientation);
			}

			break;
	}
	
}

int disFromDevPoint(int *remainingX, int *devPointX)
{
	return (*remainingX - *devPointX);
}
