// EE261 Progressive Programming Project
// Part 2
// Cal Poly, SLO
// Starter code

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 256
char lineArray[BUFFER_LENGTH];

size_t readLine(FILE *f, char *lineArray); //function prototype

int main()
   {
   char line[300];
   FILE *fptr; //file pointer

   //open the file
   if ((fptr = fopen("..\\APRSIS_DATA.txt","r")) == NULL){
       printf("Error opening input file\n");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   //keep going until the end of the file
   while (readLine(fptr, &line) != -1) //get next line and check if EOF
      {
        printf("%s\n", line);       //print the line on the screen
      }

   //Close the file and exit
   fclose(fptr);
   return 0;
   }

// read a line from the file, ignoring the terminating 0x0a
// place characters read into specified array
// return number of characters read
// return -1 if EOF
size_t readLine(FILE *f, char *lineArray)
{
char readChar;
char count=0;
//read the first character
readChar = getc(f);
//continue until EOF
while(readChar != EOF)
{
if (readChar==0x0a)
{
//we have reached the end of the line
*lineArray++ = 0; //null terminate the string

return(count); //return the count
}

*lineArray++ = readChar; //store the character
if(++count==BUFFER_LENGTH) return 0; //increment the count under buffer length

readChar = getc(f); //get the next character
}
if(readChar == EOF) return(-1); //return a -1 if we reached the end of the file
}
