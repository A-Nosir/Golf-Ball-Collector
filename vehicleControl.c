// The vehicle control everything
// Integration into the whole project yet undetermined
// Exact vehicle controls pending

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

//My personal headers
#include "definitions.h"
#include "multiball.h"
#include "moves.h"

//Functions
void retrieveBall(int distance, int angle, int check, int offsetDis, int offsetAng);
void grabBall();
void dropBall();

int main()
{
	int  ballCount, actualDis, i;
	FILE *file;
	
	//Counting lines
	file = fopen(DOC, "r");
	ballCount = countBalls(file);

	Ball balls[ballCount] ;	//Create correctly sized array

	i = 0;		//Reset index

	file = fopen(DOC, "r");

	while(!feof (file) && i < ballCount && !ferror(file))
	{
			fscanf(file, "%d %d %d",  &balls[i].distance, &balls[i].angle, &balls[i].check);
			balls[i].offsetDis = 0;
			balls[i].offsetAng = 0;
			i++;
	}
	
	fclose(file);
	
	
	for( i = 0; i < ballCount; i++)
	{
		 if (balls[i].check == 1)
		{
			//The ball might be a lie
			actualDis = balls[i].distance / 2;
			balls[i].offsetDis = actualDis;
			balls[i].offsetAng = balls[i].angle;

			retrieveBall(actualDis, balls[i].angle, balls[i].check, balls[i].offsetDis, balls[i].offsetAng);
			
			pid_t id = fork();	//fork to reaccess camera
			
			if(id == 0)
			{
				printf("\nI am the camera bro!\n");
				
				//Remove the test text before calling the camera
				//In case there is no ball, the test text will not be updated
				//By removing it we can check whether there is a ball or not by checking for the doc's existence
				remove(DOC);		

				execl(CAM_PATH, CAM, NULL);
			}
			else
			{
				waitpid(id, 0, 0);
				
				//If test exists, program reads it, then goes for the ball
				if(access("/home/student/Desktop/Project/test.txt", F_OK) != -1)
				{
					file = fopen(DOC, "r");	//Update this ball's information
					while(!feof (file) && !ferror(file))
					{	
						fscanf(file, "%d %d %d",  &balls[i].distance, &balls[i].angle, &balls[i].check);
					}
			
					retrieveBall(balls[i].distance, balls[i].angle, balls[i].check, balls[i].offsetDis, balls[i].offsetAng);
				}
				else	//Else returns to base
				{
					retrieveBall(0, balls[i].angle, 0, balls[i].offsetDis, balls[i].offsetAng);
				}
			}
		}
		else
		{
			//The ball is not a lie
			retrieveBall(balls[i].distance, balls[i].angle, 0, balls[i].offsetDis, balls[i].offsetAng);
			balls[i].offsetDis = 0;
			balls[i].offsetAng = 0;	
		}
	}

	rotate(NEXTPOS); //Face next area's position	
	printf("Now in next camera position \n");
			
	remove(DOC);	//remove test now that it is done
	return 0;
}

//Does Overall movement 
void retrieveBall(int distance, int angle, int check, int offsetDis, int offsetAng)
{
	if(distance != 0)	//Steps 1-3 are only needed when approaching a ball or what seems like it
	{
		//Step 1
		rotate(angle);

		//Step 2
		start(distance);
	
		//Step 3
		if (check == 1)
		{
			printf("Back to Camera for check\n");
			return;
		}
		else
		{
			grabBall();
		}
	}
	
	//Step 4
	rotate(180);

	//Step 5
	start(distance + offsetDis);
	
	//Step 6
	if(distance != 0)
	{
		dropBall();
	}
	
	//Step 7
	rotate(180 - angle - offsetAng);
	printf("\n");

	return;
}


void grabBall()
{
	printf("Got the ball \n");
}

void dropBall()
{
	printf("Dropped the ball \n");
}
