// EE261 Progressive Programming Project
// Part 1
// Cal Poly, SLO
// Starter code

#include <stdio.h>
#include <stdlib.h>

int main()
   {
   int c;      //character read
   FILE *fptr; //file pointer

   //open the file
   if ((fptr = fopen("..\\APRSIS_DATA.txt","r")) == NULL){
       printf("Error opening input file\n");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   //get the first character
   c = getc(fptr);

   //keep going until the end of the file
   while (c != EOF)
      {
      putchar(c);       //print the character on the screen
      c = getc(fptr);   //get the next character
      }

   //Close the file and exit
   fclose(fptr);
   return 0;
   }
