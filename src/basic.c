#include "../include/basic.h"
#include "../include/const.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

volatile uint64_t mode, size;
void  CLock_mode_config(buffer_size _size, uint64_t modeS){
        size = mode = 0; //Initialize the mode
        if ((modeS & IGNORE_WHITESPACE) == IGNORE_WHITESPACE)
            mode |= IGNORE_WHITESPACE;
        if ((modeS & UPPERCASE) == UPPERCASE)
            mode |= UPPERCASE;
        if ((modeS & LOWERCASE) == LOWERCASE)
            mode |= LOWERCASE;

        size = _size;
}

static char* CLock_reverse_encode(const char* string){
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

char* CLock_reverse(size_t perform, const char* string){
    char* (*perform_ptr)(const char* string) = CLock_reverse_encode;
    return perform_ptr(string);
}

char* CLock_rot_decode(const char* string, size_t rotateTime){
    char *ret = strdup(string);
    if(ret){
        for (size_t i = 0; i < strlen(string); i++){
            if (ret[i] == ' ' || ret[i] == '\n' || ret[i] == '\r')
                if ((mode & IGNORE_WHITESPACE) == IGNORE_WHITESPACE)
                    continue;
                
                uint8_t temp = isupper(ret[i]) ? (ret[i] - 'A' - rotateTime) 
                                               : (ret[i] - 'a' - rotateTime);

                if (temp < 0)
                    temp = 27 - temp;
                
                temp %= 26 + isupper(ret[i]) ? 'A' : 'a';

                if ((mode & UPPERCASE) == UPPERCASE) 
                    ret[i] = toupper(ret[i]);
                else if ((mode & LOWERCASE) == LOWERCASE)
                    ret[i] = tolower(ret[i]);
        }

        return ret;
    }
    return NULL;
}

char* CLock_rot_encode(const char* string, size_t rotateTime){
    char *ret = strdup(string);
    if(ret){
        for (size_t i = 0; i < strlen(string); i++){
            if (ret[i] == ' ' || ret[i] == '\n' || ret[i] == '\r')
                if ((mode & IGNORE_WHITESPACE) == IGNORE_WHITESPACE)
                    continue;
                
                ret[i] = isupper(ret[i]) ? (ret[i] - 'A' + rotateTime) % 26 + 'A' 
                                         : (ret[i] - 'a' + rotateTime) % 26 + 'a';

                if ((mode & UPPERCASE) == UPPERCASE) 
                    ret[i] = toupper(ret[i]);
                else if ((mode & LOWERCASE) == LOWERCASE)
                    ret[i] = tolower(ret[i]);
        }

        return ret;
    }
    return NULL;
}

char* CLock_rot(size_t perform, const char* string, size_t rotateTime){
    char* (*perform_ptr)(const char* string, size_t rotateTime) = perform == ENCODE ? CLock_rot_encode
                                                                                    : CLock_rot_decode;
    return perform_ptr(string, rotateTime);
}

char* CLock_bin(const char* string, size_t bits_take){
    char *ret = malloc((strlen(string)) * bits_take + 1); //Plus one to add in the \0 terminator
    memset(ret, 0, (strlen(string)) * bits_take + 1);

    size_t reverseIndex = bits_take - 1;// starting at the end of a "custom byte" with bits_take bit(s)

    if (ret){
        for (size_t i = 0; i < strlen(string); i++){
            if (ret[i] == ' ' || ret[i] == '\n' || ret[i] == '\r')
                if ((mode & IGNORE_WHITESPACE) == IGNORE_WHITESPACE)
                    continue;

                uint8_t num = string[i];
                
                int64_t curIndex = reverseIndex;

                while (curIndex >= 0 && curIndex >= (reverseIndex - bits_take + 1)){
                    if (num > 0)
                        ret[curIndex] = num % 2 ? '1' : '0';
                    else
                        ret[curIndex] = '0';

                    num /= 2;
                    curIndex--;
                }
               
                reverseIndex += bits_take;
        }
        ret[reverseIndex - bits_take + 1] = '\0';
        return ret;
    }
    return NULL;
}

//This function credits by jacqueries
//See more : https://gist.github.com/jacquerie/8493041a5c5848ddccc8

static const char* morseTable[95] = {
        NULL, "-.-.--", ".-..-.", NULL, NULL, NULL, NULL, ".----.",
        "-.--.", "-.--.-", NULL, NULL, "--..--", "-....-", ".-.-.-", "-..-.",
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
        "---..", "----.", "---...", NULL, NULL, "-...-", NULL, "..--..",
        ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
        ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
        "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, "..--.-",
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

static const char* charTable[128] = {
        NULL, NULL, "E", "T", "I", "N", "A", "M",
        "S", "D", "R", "G", "U", "K", "W", "O",
        "H", "B", "L", "Z", "F", "C", "P", NULL,
        "V", "X", NULL, "Q", NULL, "Y", "J", NULL,
        "5", "6", NULL, "7", NULL, NULL, NULL, "8",
        NULL, "/", NULL, NULL, NULL, "(", NULL, "9",
        "4", "=", NULL, NULL, NULL, NULL, NULL, NULL,
        "3", NULL, NULL, NULL, "2", NULL, "1", "0",
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, ":",
        NULL, NULL, NULL, NULL, "?", NULL, NULL, NULL,
        NULL, NULL, "\"", NULL, NULL, NULL, "@", NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, "'", NULL,
        NULL, "-", NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, ".", NULL, "_", ")", NULL, NULL,
        NULL, NULL, NULL, ",", NULL, "!", NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

static char* Clock_morse_encode(const char *string){
    char *ret = malloc(size);
    memset(ret, 0, size);
    if (ret){
        size_t length = strlen(string);
        for (size_t i = 0; i < length; i++){
            const char *append = morseTable[toupper(string[i]) - 32];
            if (append){
                strncat(ret, append, strlen(append));
                strncat(ret, " ", 2);
            }
        }
        return ret;
    }
    return NULL;
}

int morse_to_index (const char* str){
        //This function use a byte itself to replicate the morse string with flags value shown below
        unsigned sum = 0, bit;

        for (bit = 1; bit; bit <<= 1) {
                switch (*str++) {
                case 0:
                        return sum | bit; // Reach '\0'
                default:
                        return 0;         //Error
                case '-':
                        sum |= bit;       //Flag '-' as 1
                case '.':
                        break;            //Flag '.' as 0
                }
        }

        return 0; //Error
}

static char* CLock_morse_decode(const char *string){
    char *ret = malloc(size);
    memset(ret, 0, size);

    char *cluster = malloc(6);

    if (ret){
        size_t i = 0, length = strlen(string);

        while (i < length){
            memset(cluster, '\0', 6);
            size_t cluster_count = 0;

            while (string[i] != ' '){
                //Loop until found letter separation or word separation
                cluster[cluster_count++] = string[i];
                i++;
            }

            const char *append = charTable[morse_to_index(cluster)];
            if (append){
                strncat(ret, append, strlen(append));
            }

            //free((char*)append);
            //Loop through more space if it a word separation

            while (string[i] == ' ')
                i++;
        }

        printf("%p\n", cluster);
        free(cluster);
        return ret;
    }
    return NULL;
}

char* Clock_morse(size_t perform, char *string){
    char* (*perform_ptr)(const char* string) = perform == ENCODE ? Clock_morse_encode
                                                                 : CLock_morse_decode;
    return perform_ptr(string);
}