// EE261 Progressive Programming Project
// Cal Poly, SLO
// Part 5, Debug Demo Version
// Filter for 1 callsign,
// Print call, location, distance moved since last.
// Write func to calc distance moved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES // for C
#include <math.h>

#include "EE261_Project.h"

int         stopHere = 0;               //debugging stuff

int         readLine(FILE *, char *);   //read a line from the file, stripping \n and \r
Location    *StringToCoords(char *);    //convert string of coord data to coord structs
double      CoordsToMiles(Location *, Location *); //distance between 2 coords

char        lineArray[256];             //data read from file
char        *coordStart;                //start of coord data
Location    *currentLocation;           //location data from current string
Location    *previousLocation;          //previous location data
double      distanceMoved;              //distance between previous and current

char        callsign[16];               //callsign buffer
unsigned long packetCount;              //count of packets processed

int         charactersRead = 0;         //number of characters read into buffer. -1 = EOF
FILE        *fptr;                      //File pointer
int         c;                          //character read from file
bool        firstLocation = false;      //we don't have a first location yet

int main()
	{
	printf("\r\nEE261 Debug Program\n");

	//open the input file
	if((fptr = fopen("DATA.txt", "r")) == NULL)
		{
		printf("Error! opening file");

		// Program exits if the file pointer returns NULL.
		exit(1);
		}

	//read and repeat until all data is read
	while(charactersRead != -1)
		{
		//read a line
		charactersRead = readLine(fptr, lineArray);

		//stop to debug specific callsign
		//To use this, set a breakpoint at the desired line,
		//then edit it to break when the expression
		//stopHere==1 is true
		stopHere = (strstr(lineArray, "KC6YIR-1")) ? 1 : 0;

		// we only want records with WANTED_RECORD
		coordStart = strstr(lineArray, WANTED_RECORD);
		if(coordStart != NULL && strstr(lineArray, ":`") == NULL)
			{
			//initialize the callsign array
			memset(callsign, 0, 16);

			//extract the callsign
			strncpy(callsign, lineArray, (int)(strchr(lineArray, '>') - lineArray));

			//skip this record if it isn't from the callsign we want
			if(strcmp(callsign, WANTED_CALLSIGN) != 0) continue;

			// point coordStart to the beginning of the coordinates
			coordStart += 2;

			//extract the coordinates
			currentLocation = StringToCoords(coordStart);
			if(!firstLocation)
				{
				previousLocation = StringToCoords(coordStart);
				firstLocation = true;
				}

			//calculate the distance
			distanceMoved = CoordsToMiles(previousLocation, currentLocation);

			//update previousLocation for next iteration
			previousLocation = currentLocation;

			//increment the packet counter
			packetCount++;

			//print the output
			printf("%18s: Lat: %3d %02d %02d  Long: %4d %02d %02d  Miles: %3.1f   %06lu records processed\n",
			       callsign,
			       currentLocation->Latitude.degrees,
			       currentLocation->Latitude.minutes,
			       currentLocation->Latitude.seconds,
			       currentLocation->Longitude.degrees,
			       currentLocation->Longitude.minutes,
			       currentLocation->Longitude.seconds,
			       distanceMoved,
			       packetCount
			      );
			}
		}

	//close the file and return when done
	fclose(fptr);
	return 0;
	}

//--------------------------------------------------------------------------------------------------------
// read a line frmo the file, ignoring the terminating 0x0a
// place characters read into specified array
// return number of characters read
// return -1 if EOF
int readLine(FILE *f, char *lineArray)
	{
	char readChar;
	int count = 0;

	readChar = getc(f);     //read the first character
	while(readChar != EOF)
		{
		if(readChar == 0x0a)
			{
			// 0x0a means we are at the end of a line of data
			*lineArray++ = 0; //null terminate the string
			return(count);    //return the count
			}

		*lineArray++ = readChar;   //put the character in the buffer
		count++;                   //increment the character count
		readChar = getc(f);        //get the next character
		}

	if(readChar == EOF) return(-1); //return a -1 if we reached the end of the file
	return(0); //keep the compiler happy
	}

//--------------------------------------------------------------------------------------------------------
// extract coordinates from input string
// placing them in a struct of type Location
// that contains 2 structs of type Coord
// returns pointer to Location struct
Location *StringToCoords(char *locationString)
	{
	char sDegrees[4], sMinutes[4], sSeconds[4], sHemi;

	//allocate the memory needed for the Location struct
	Location *newLocation = (Location *)malloc(sizeof(Location));
	if(newLocation == NULL)
		{
		fputs("Memory error", stderr);
		exit(2); // different error code from the earlier
		}

	//extract the strings needed for conversion
	strncpy(sDegrees, locationString,   2);
	sDegrees[2] = '\0';
	strncpy(sMinutes, locationString + 2, 2);
	sMinutes[2] = '\0';
	strncpy(sSeconds, locationString + 5, 2);
	sSeconds[2] = '\0';
	sHemi = locationString[7];

	//convert the Latitude degrees. Adjust for hemisphere
	newLocation->Latitude.degrees = (int)strtol(sDegrees, (char **)NULL, 10);
	newLocation->Latitude.degrees *= sHemi == 'S' ? -1 : 1;

	//extract the minutes
	newLocation->Latitude.minutes = (int)strtol(sMinutes, (char **)NULL, 10);

	//extract the fractions of a minute and convert to seconds
	newLocation->Latitude.seconds = (int)strtol(sSeconds, (char **)NULL, 10);
	newLocation->Latitude.seconds = (int)(((float)newLocation->Latitude.seconds / 100) * 60);

	//Longitude starts 9 chars after latitude
	//repeat above process
	strncpy(sDegrees, locationString + 9,  3);
	sDegrees[3] = '\0';
	strncpy(sMinutes, locationString + 12, 2);
	sMinutes[2] = '\0';
	strncpy(sSeconds, locationString + 15, 2);
	sSeconds[2] = '\0';
	sHemi = locationString[17];

	newLocation->Longitude.degrees = (int)strtol(sDegrees, (char **)NULL, 10);
	newLocation->Longitude.degrees *= sHemi == 'W' ? -1 : 1;

	newLocation->Longitude.minutes = (int)strtol(sMinutes, (char **)NULL, 10);
	newLocation->Longitude.seconds = (int)strtol(sSeconds, (char **)NULL, 10);
	newLocation->Longitude.seconds = (int)(((float)newLocation->Longitude.seconds / 100) * 60);

	return(newLocation);
	}

//--------------------------------------------------------------------------------------------------------
//calculate the distance between two coordinates
//https://www.geeksforgeeks.org/program-distance-two-points-earth/
double CoordsToMiles(Location *location1, Location *location2)
	{
	double Latitude1 = (abs(location1->Latitude.degrees) +
	                    ((float)location1->Latitude.minutes / 60) +
	                    ((float)location1->Latitude.seconds / 3600)) / (180 / M_PI);
	if(location1->Latitude.degrees < 0) Latitude1 *= -1;

	double Longitude1 = (abs(location1->Longitude.degrees) +
	                     ((float)location1->Longitude.minutes / 60) +
	                     ((float)location1->Longitude.seconds / 3600)) / (180 / M_PI);
	if(location1->Longitude.degrees < 0) Longitude1 *= -1;

	double Latitude2 = (abs(location2->Latitude.degrees) +
	                    ((float)location2->Latitude.minutes / 60) +
	                    ((float)location2->Latitude.seconds / 3600)) / (180 / M_PI);
	if(location2->Latitude.degrees < 0) Latitude2 *= -1;

	double Longitude2 = (abs(location1->Longitude.degrees) +
	                     ((float)location2->Longitude.minutes / 60) +
	                     ((float)location2->Longitude.seconds / 3600)) / (180 / M_PI);
	if(location2->Longitude.degrees < 0) Longitude2 *= -1;

	double Distance = 3963.0 * acos((sin(Latitude1) * sin(Latitude2)) +
	                                cos(Latitude1) * cos(Latitude2) * cos(Longitude2 - Longitude1));

	return(Distance);
	}
