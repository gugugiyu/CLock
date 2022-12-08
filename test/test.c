#include <stdio.h>
#include <string.h>
#include "../include/basic.h"
#include <stdlib.h>
#include <math.h>

int main(){
    char *test = "THIS WILL WORK PERFECTLY RIGhT";
    CLock_mode_config(IGNORE_WHITESPACE | UPPERCASE);
    char *ret = CLock_reverse(test);
    char *ret2 = CLock_rot13(test);

    printf("Test #1: %s\n", ret);
    printf("Test #2: %s\n", ret2);
    return 0;
}