// EE261 Progressive Programming Project
// Part 3
// Cal Poly, SLO
// Starter code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_LENGTH 256
#define WANTED_RECORD ":="

char lineArray[BUFFER_LENGTH];
size_t readLine(FILE *f, char *lineArray); //function prototype
void extractCallsign(char *inputData, char *outputData);

int main()
	{
	char lineArray[BUFFER_LENGTH];
	char callSign[16];
	FILE *fptr; //file pointer
	int packetCount = 0;

	//open the file
	if((fptr = fopen("..\\APRSIS_DATA.txt", "r")) == NULL)
		{
		printf("Error opening input file\n");
		// Program exits if the file pointer returns NULL.
		exit(1);
		}
	//keep going until the end of the file
	//get next line and check if EOF
	while(readLine(fptr, lineArray) != -1)
		{
        //filter out comment lines
		if(lineArray[0] == '#') continue;
		if(strstr(lineArray, WANTED_RECORD)!= NULL && strstr(lineArray, ":`") == NULL)
			{
            //extract call sign and print with packet index
			packetCount++;
			extractCallsign(lineArray, callSign);
			printf("%16s: %06d records processed\n", callSign, packetCount);
			}
		}
	//Close the file and exit
	fclose(fptr);
	return 0;
	}

// extract call sign from each line
void extractCallsign(char *inputData, char *outputData)
	{
	char *callSignAdd = strchr(inputData, '>');
	int z = (int)(callSignAdd - inputData);
	strncpy(outputData, inputData, z);
	outputData[z] = '\0';
	return 0;
	}

// read a line from the file, ignoring the terminating 0x0a
// place characters read into specified array
// return number of characters read
// return -1 if EOF
size_t readLine(FILE *f, char *lineArray)
	{
	char readChar;
	char count = 0;
//read the first character
	readChar = getc(f);
//continue until EOF
	while(readChar != EOF)
		{
		if(readChar == 0x0a)
			{
//we have reached the end of the line
			*lineArray++ = 0; //null terminate the string

			return(count); //return the count
			}

		*lineArray++ = readChar; //store the character
		if(++count == BUFFER_LENGTH) return 0; //increment the count under buffer length

		readChar = getc(f); //get the next character
		}
	if(readChar == EOF) return(-1); //return a -1 if we reached the end of the file
	}
