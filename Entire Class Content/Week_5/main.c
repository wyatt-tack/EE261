#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Part1:\n");
    //initialize array
    const int ARRAY_LENGTH = 6;
    int myArray[6];
    //fill array
    printf("Enter numbers:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)scanf("%d", &myArray[i]);
    //print array
    printf("\nYour array:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)printf("%d, ", myArray[i]);



    printf("\n\nPart2:\n");


    printf("\nYour array:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)printf("%d, ", myArray[i]);
    //reverse array
    for (int i = 0; i < ARRAY_LENGTH/2; i++)
    {
      int temp =  myArray[i];
      myArray[i] = myArray[ARRAY_LENGTH - 1 - i];
      myArray[ARRAY_LENGTH - 1 - i] = temp;
    }
    printf("\nYour reversed array:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)printf("%d, ", myArray[i]);



    printf("\n\nPart3:\n");

    //sum array and print
    printf("\nYour array's sum: ");
    int arraySum = 0;
    for (int i = 0; i < ARRAY_LENGTH; i++) arraySum = arraySum + myArray[i];
    printf("%d\n", arraySum);


       printf("\n\nPart4:\n");

    //copy array
    int array2 [ARRAY_LENGTH];
    for (int i = 0; i < ARRAY_LENGTH; i++) array2[i] = 0;
    printf("\nArray 1:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)printf("%d, ", myArray[i]);
    printf("\nArray 2:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)printf("%d, ", array2[i]);
    for (int i = 0; i < ARRAY_LENGTH; i++)array2[i] = myArray[i];
    printf("\nFixed Array 2:\n");
    for (int i = 0; i < ARRAY_LENGTH; i++)printf("%d, ", array2[i]);



   printf("\n\nPart5:\n");

    //Array insert
    int array3[ARRAY_LENGTH+1];
    for (int i = 0; i < ARRAY_LENGTH+1; i++)array3[i] = i+1;

    array3[ARRAY_LENGTH] = 0;
    printf("\nArray start:\n");
    for (int i = 0; i < ARRAY_LENGTH+1; i++)printf("%d, ", array3[i]);

    for (int i = ARRAY_LENGTH+1; i > 4; i--)
    {
        array3[i] = array3[i-1];
    }

    array3[4] = 1000;


    printf("\nArray insert:\n");
    for (int i = 0; i < ARRAY_LENGTH+1; i++)printf("%d, ", array3[i]);
    printf("\n");


   printf("\n\nPart6:\n");

    //3d Array
    printf("3D array:\n");
    int array3D [3][3][3] = {{{1,2,3},{4,5,6},{7,8,9}},             //i = 0
                             {{10,11,12},{13,14,15},{16,17,18}},    //i = 1
                             {{19,20,21},{22,23,24},{25,26,27}}};   //i = 2
    for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
        printf("%{");
        for (int k = 0; k < 3; k++){
        printf("%d, ", array3D[i][j][k]);
        }
        printf("%},");
        }

    printf("\n");
}

    return 0;
}
