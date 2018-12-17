#include <stdio.h>
#include <stdbool.h>

#include"definitions.h"
#include"multiball.h"

int countBalls(FILE *file)
{
	int c;
	int count = 1;
	
	while(!feof (file))
	{
		c = fgetc(file);
		if(c == '\n')
		{
			count++;
		}
			
	}	
	
	fclose(file);
	
	return count;
}	
