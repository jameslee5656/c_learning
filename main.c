#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "tests.h"

/*
* specification
* the array range would be -10^6 ~ 10^6 of the random number
* the array could have maximum 10^6 numbers
*/

void sortTemplate(int *arr, const unsigned int uArrSize)
{

}

int main(void)
{
    unitTest(&sortTemplate, "sortTemplate");
}