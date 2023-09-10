/*
Write a program using file handling functions to copy a file (Input1.txt). Write a program which converts entire file (obtained after copying) from lower case to upper case and vice versa.
*/

//CS21B2028
//NITIN REDDY K

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	FILE *fptr1, *fptr2;

	// Open one file for reading
	fptr1 = fopen("Input1.txt", "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	// Open another file for writing
	fptr2 = fopen("output1.txt", "w");
	if (fptr2 == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}

	// Read contents from file
    int k;
    printf("Convert to lower(0) or Upper(1)?? :");
    scanf("%d",&k);
	char c = fgetc(fptr1);
	while (c != EOF)
	{   
        if(k==0)
        {
            c=tolower(c);
        }
        else if(k==1)
        {
            c=toupper(c);
        }

		fputc(c, fptr2);
		c = fgetc(fptr1);
	}

	printf("Contents copied in required format :)\n");

	fclose(fptr1);
	fclose(fptr2);

	return 0;
}