#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    /*
    //original code:
    int x, y, output;
    printf("Enter (x y)\n");
    scanf("%d %d", &x, &y);
    output = (15*((x+1)/2))+(x/2)+y*((x+1)%2)-y*(x%2);
    printf("Grid number is %d\n", output);
    */
    //start timing algorithm
    int rows = 32;  //set up constants for rows, columns
    int columns = 8;
    int Xin[rows];  //populate x and y rows and columns
    int Yin[columns];
    int OutIn;
    for (int i = 0; i < rows; i++)Xin[i]=i;
    for (int j = 0; j < columns; j++)Yin[j]=j;
    int Z = 1;
    double startTime, endTime, elapsedTime, perCalc;
    clock_t start, end; //set up itterations and timing
    printf("Enter how many itterations of 32x8 to time over: \n");
    scanf("%d", &Z);
    //start clock
    start = clock();
    for (int m = 0; m < Z; m++)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
            OutIn = (15*((Xin[i]+1)/2))+(Xin[i]/2)+Yin[j]*((Xin[i]+1)%2)-Yin[j]*(Xin[i]%2);
            }
        }
    }
    end = clock();
    //calculate results
    startTime = ((double)start)/CLOCKS_PER_SEC;
    endTime = ((double)end)/CLOCKS_PER_SEC;
    elapsedTime = endTime - startTime;
    perCalc = (elapsedTime / ((double)(unsigned long)(Z * rows * columns)))*1.0E9;
    //print results
    printf("Start Time: %f S\n", startTime);
    printf("End Time: %f S\n", endTime);
    printf("Elapsed Time: %f S\n", elapsedTime);
    printf("Time Per Calculation in nanoseconds~ %f nS\n", perCalc);
    printf("\n");
    return 0;
}
