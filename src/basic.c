#include "../include/basic.h"
#include "../include/const.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

uint64_t mode;
void  CLock_mode_config(uint64_t modeS){
    mode = 0; //Initialize the mode
    if ((modeS & IGNORE_WHITESPACE) == IGNORE_WHITESPACE)
        mode |= IGNORE_WHITESPACE;
    if ((modeS & UPPERCASE) == UPPERCASE)
        mode |= UPPERCASE;
    if ((modeS & LOWERCASE) == LOWERCASE)
        mode |= LOWERCASE;
}

char* CLock_reverse(const char* string){
    char *ret = strdup(string);
    if(ret){
        for (size_t i = 0, end = strlen(ret) - 1; i < (size_t)(strlen(ret)/2) + 1, i < end; i++, end--){
            if (ret[i] == ' ' || ret[i] == '\n' || ret[i] == '\r'){
                if ((mode & IGNORE_WHITESPACE) != IGNORE_WHITESPACE){
                    //In case not ignore
                    memmove(ret + i, ret + i + 1, strlen(ret) - i + 1);
                }
            }

            if (ret[end] == ' ' || ret[end] == '\n' || ret[end] == '\r'){
                if ((mode & IGNORE_WHITESPACE) != IGNORE_WHITESPACE){
                    //In case not ignore
                    memmove(ret + end, ret + end + 1, strlen(ret) - end + 1);
                }
            }

            if ((mode & UPPERCASE) == UPPERCASE){
                ret[i] = toupper(ret[i]);
                ret[end] = toupper(ret[end]);
            }
            else if ((mode & LOWERCASE) == LOWERCASE){
                ret[i] = tolower(ret[i]);
                ret[end] = tolower(ret[end]);
            }

            SWAP(ret[i], ret[end]);
        }

        return ret;
    }
    return NULL;
}

char* CLock_rot13(const char* string){
    char *ret = strdup(string);

    if(ret){
        for (size_t i = 0; i < strlen(string); i++){
            if (ret[i] == ' ' || ret[i] == '\n' || ret[i] == '\r')
                if ((mode & IGNORE_WHITESPACE) == IGNORE_WHITESPACE)
                    continue;
                    
            if (toupper(ret[i]) - 'A' <= 13)
                ret[i] += 13;
            else
                ret[i] -= 13;
        }

        return ret;
    }
    return NULL;
}