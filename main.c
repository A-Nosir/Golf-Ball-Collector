#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "definitions.h"

int main()
{
	//The code to create a result text file during development
	/*
	FILE *file;		
	file = fopen(DOC, "w+");
	fprintf(file, "%d %d %d", 100, 50, 0);	
	fprintf(file, "%d %d %d", 40, 25, 0);
	fclose(file);
	*/
	
	pid_t id; //The variable used to store process id
	
	//Clear four areas
	for (int i = 0; i < 4; i++)
	{
		//fork() to create the process used for the camera
		id = fork();	

		if (id == 0)			
		{
			printf("\nRun camera\n");
			execl(CAM_PATH, CAM, NULL);	//Child runs camera code
		}
		else
		{//Parent waits for camera completion
			waitpid(id, 0, 0);			

			printf("\nCamera done\n");
		}

		//fork() to create the process used for vehicle Control
		id = fork();	

		if (id == 0)
		{//Child runs vehicle control program
			printf("\nRun vehicle control\n");
			execl(CTRL_PATH, VEH_CTRL, NULL);	
		}
		else
		{//Parent waits for vehicle control completion
			waitpid(id, 0, 0);

			printf("\nArea %i cleared\n", i);
		}
	}
	return 0;
}
