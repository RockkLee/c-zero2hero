#include <stdio.h>

#include "demo_lib.h"

int main(void)
{
    int left = 7;
    int right = 5;

    printf("%d + %d = %d\n", left, right, add(left, right));
    return 0;
}
