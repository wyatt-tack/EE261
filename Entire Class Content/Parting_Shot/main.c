#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
	{
    //opens file and checks for error
	FILE *fptr;
    if((fptr = fopen("..//Project_Part_5//bin//Debug//Project_Part_5.exe", "rb")) == NULL)
		{
		printf("Error opening input file\n");
		exit(1);
		}
    //set cursor to 0;
    fseek(fptr, 0, SEEK_SET);

    //variables for reading and printing
	unsigned char byte[2];
	char charline[16];
	//variables for intitializing progress through file
	int line = 0;
	int end = 0;
	int value;
    int endCursor =0;
    //loop till end of file
	while(end != 1)
		{
        //reset default character line
		strcpy(charline, "................");
		//print offset into file
		printf("%-10.8x ", line);
        //loop for 16 bytes each line
		for(int cursor = 0; cursor < 16; cursor++)
			{
            //read next byte if end of file set flag
			if(fread(byte, sizeof(unsigned char), 1, fptr) != 1)
				{
                endCursor = cursor;
				cursor = 16;
				end = 1;
				continue;
				}
            //send byte to index in character line if printable
			if(isprint(byte[0]) != 0) charline[cursor] = byte[0];
            //print byte
			printf(" %02x", byte[0]);
			if(cursor == 7) printf("   ");
			}
		//Formatting for end of file
        if(end == 1)
            for (int spaces = 0; spaces < 16-endCursor; spaces++)
                printf("   ");
        //at end of 16 byte line print character line
		printf("   [%s]\n", charline);
        //increment file index
		line = line + 16;
		}
    //close file and exit
	fclose(fptr);
	return 0;
	}
