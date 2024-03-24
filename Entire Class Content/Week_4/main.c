#include <stdio.h>
#include <stdlib.h>


int main()
{

    while(1){
    int numTerms;
    int currentNum = 1;
    int lastNum = 0;
    int nextNum;
    printf("Print # of terms\n");
    scanf("%d", &numTerms);
    for (int i = 0; i < numTerms; i++)
    {
       printf("%d, ", lastNum);
       nextNum = lastNum + currentNum;
       lastNum = currentNum;
       currentNum = nextNum;


    }
    printf("\n");
    }
    return 0;
}
