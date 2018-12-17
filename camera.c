#include <stdio.h>

#include "definitions.h"

int main()
{
	FILE *file;

	file = fopen(DOC, "w+");
	fprintf(file, "%d %d %d", 40, 0, 0);
	fclose(file);
		
	printf("Camera has updated situation, there is a ball\n");
	
	return 0;
}