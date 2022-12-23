#include <stdio.h>
#include <string.h>
#include "../include/basic.h"
#include "../include/BaseEncoder.h"
#include <stdlib.h>
#include <math.h>

int main(){
    char *test = "- .... .. ... .. ... .- ... - .-. .. -. --.";
    CLock_mode_config(BUFFER_VERY_LARGE, IGNORE_WHITESPACE);
    char *ret =  CLock_reverse(ENCODE, test);
    char *ret2 = CLock_rot(DECODE, test, 13);
    char *ret3 = CLock_bin(test, 8);
    char *ret4 = CLock_base64(test);
    char *ret5 = CLock_base32(test);
    char *ret6 = Clock_morse(DECODE, test);
    char *ret7 = CLock_base16(test);
    char *ret8 = CLock_base64(CLock_base32(CLock_base16(test)));

    printf("Test #1: %s\n", ret);
    free(ret);
    printf("Test #2: %s\n", ret2);
    free(ret2);
    printf("Test #3: %s\n", ret3);
    free(ret3);
    printf("Test #4: %s\n", ret4);
    free(ret4);
    printf("Test #5: %s\n", ret5);
    free(ret5);
    printf("Test #6: %s\n", ret6);
    free(ret6);
    printf("Test #7: %s\n", ret7);
    free(ret7);
    printf("Nested encode: %s\n", ret8);
    free(ret8);
    return 0;
}