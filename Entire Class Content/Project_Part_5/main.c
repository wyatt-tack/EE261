// EE261 Progressive Programming Project
// Part 5
// Cal Poly, SLO
// Author: Wyatt Tack

//include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "EE261_Project.h"

//define common terms
#define BUFFER_LENGTH 256
#define WANTED_RECORD ":="

//function prototypes, in order of use in main
Location *initCoords();
size_t readLine(FILE *f, char *lineArray);
void extractCallsign(char *inputData, char *outputData);
Location *extractLocation(char *lineArray);
float distanceTraveled(Location *, Location *);

//---------------------------------------------------------
int main()
	{
	//initialize storage for data, locations, and call sign
	char lineArray[BUFFER_LENGTH];
	char callSign[16];
	Location *myLocation;
	Location *lastLocation;
	float miles;
	int packetCount = 0;

	//initialize lastLocation to be common value among data set
	lastLocation = initCoords();

	//initialize file pointer and open file
	FILE *fptr;
	if((fptr = fopen("..\\Project_Part_5\\APRSIS_DATA.txt", "r")) == NULL)
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

		//if line is valid data line continue
		if(strstr(lineArray, WANTED_RECORD) != NULL
		   && strstr(lineArray, ":`") == NULL)
			{
			//extract call sign from line data
			extractCallsign(lineArray, callSign);
			//follow KE6GYD-5 call sign for location and travel
			if(strcmp(callSign, "KE6GYD-5") == 0)
				{
				//parse out location
				myLocation = extractLocation(lineArray);

				//calculate distance traveled from last location and update last location
				miles = distanceTraveled(myLocation, lastLocation);
				lastLocation = myLocation;

				//increment packet count
				packetCount++;

				//print extracted data
				printf("%18s: Lat: %3d %02d %02d Long: %4d %02d %02d "
                       "Miles: %3.1f %06d records processed\n",
				       callSign, myLocation->Latitude.degrees, myLocation->Latitude.minutes,
				       myLocation->Latitude.seconds, myLocation->Longitude.degrees,
				       myLocation->Longitude.minutes, myLocation->Longitude.seconds, miles,
				       packetCount);
				}
			}
		}

	//once finished close the file and exit
	fclose(fptr);
	return 0;
	}

//---------------------------------------------------------

//function initializes a Location struct to "average" location of KE6GYD-5
Location *initCoords()
	{
	Location *tempLocation = (Location *)malloc(sizeof(Location));
	tempLocation->Latitude.degrees = 34;
	tempLocation->Latitude.minutes = 30;
	tempLocation->Latitude.seconds = 0;
	tempLocation->Longitude.degrees = -117;
	tempLocation->Longitude.minutes = 20;
	tempLocation->Longitude.seconds = 0;
	return (tempLocation);
	}

// extract call sign from each line
void extractCallsign(char *inputData, char *outputData)
	{
	char *callSignAdd = strchr(inputData, '>');
	int callSignLength = (int)(callSignAdd - inputData);
	strncpy(outputData, inputData, callSignLength);
	outputData[callSignLength] = '\0';
	return 0;
	}

// function takes in data line and parses out location in long/lat
Location *extractLocation(char *lineArray)
	{
	//set temp variables for data processing
	Location *tempLocation = (Location *)malloc(sizeof(Location));
	char dumpString[BUFFER_LENGTH];
	char hemisphereLat;
	char hemisphereLong;

	//scan through data line for different numbers
	sscanf(lineArray,
	       "%[^=] = %2d%2d.%2d%c/%3d%2d.%2d%c%*[\n]s",
	       dumpString, &tempLocation->Latitude.degrees,
	       &tempLocation->Latitude.minutes,
	       &tempLocation->Latitude.seconds, &hemisphereLat,
	       &tempLocation->Longitude.degrees,
	       &tempLocation->Longitude.minutes,
	       &tempLocation->Longitude.seconds, &hemisphereLong);

	//convert longitude/latitude to negative/positive values
	if(hemisphereLat == 'S')
		tempLocation->Latitude.degrees = -1 * tempLocation->Latitude.degrees;
	if(hemisphereLong == 'W')
		tempLocation->Longitude.degrees = -1 * tempLocation->Longitude.degrees;

	//convert decimal minutes to seconds
	tempLocation->Longitude.seconds = 60 * tempLocation->Longitude.seconds / 100;
	tempLocation->Latitude.seconds = 60 * tempLocation->Latitude.seconds / 100;
	return (tempLocation);
	}

//function for distance traveled calculation
float distanceTraveled(Location *Location1, Location *Location2)
	{
//convert to decimal long/lat values
	double Lat1 = (double)abs(Location1->Latitude.degrees) +
	              ((double)(Location1->Latitude.minutes) / 60.0) +
	              ((float)(Location1->Latitude.seconds) / 3600.0);
	double Long1 = (double)abs(Location1->Longitude.degrees) +
	               ((double)(Location1->Longitude.minutes) / 60.0) +
	               ((float)(Location1->Longitude.seconds) / 3600.0);
	double Lat2 = (double)abs(Location2->Latitude.degrees) +
	              ((double)(Location2->Latitude.minutes) / 60.0) +
	              ((float)(Location2->Latitude.seconds) / 3600.0);
	double Long2 = (double)abs(Location2->Longitude.degrees) +
	               ((double)(Location2->Longitude.minutes) / 60.0) +
	               ((float)(Location2->Longitude.seconds) / 3600.0);

//determine if positive/negative
	if(Location1->Latitude.degrees < 0) Lat1 = Lat1 * -1.0;
	if(Location1->Longitude.degrees < 0) Long1 = Long1 * -1.0;
	if(Location2->Latitude.degrees < 0) Lat2 = Lat2 * -1.0;
	if(Location2->Longitude.degrees < 0) Long2 = Long2 * -1.0;

//use formula to calculate distance traveled and return
	float distance = 3963.0 * acos((sin(Lat1 / 57.29577951) *
	                                sin(Lat2 / 57.29577951)) + cos(Lat1 / 57.29577951) *
                                    cos(Lat2 / 57.29577951) * cos((Long2 / 57.29577951) -
                                    (Long1 / 57.29577951)));
	return distance;
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
			*lineArray++ = 0;

			return(count);
			}
//read each line and return 0 if count is higher than buffer length
		*lineArray++ = readChar;
		if(++count == BUFFER_LENGTH) return 0;
		readChar = getc(f);
		}
//return -1 if end of file
	if(readChar == EOF) return(-1);
	}
