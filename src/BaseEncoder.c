#include "../include/basic.h"
#include "../include/const.h"
#include "../include/BaseEncoder.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const signed char table64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const signed char table32[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
const signed char table16[] = "0123456789ABCDEF";
static const volatile unsigned char PAD_CHARACTER = '=';

static char CLock_static_64bit_conversion(int c){
    return table64[c & 0x3F];
}


char* CLock_base64(char* string){
    const uint8_t bit_block_six = 63;  // 0011 1111
    char* ret = malloc(size);
    memset(ret, 0, size);

    if (ret){
        size_t iterator = 0, ret_iterator = 0;
        uint8_t bits_num, remain = 1;
        uint8_t bits_remain_num,  bits_next_num;
        size_t length = strlen(string);

        while (iterator < length){
            switch(remain){
                case 1:;
                    bits_num = (string[iterator] >> 2) & bit_block_six; // Get the 6 outmost bit
                    break;
                case 2:;
                    bits_remain_num = (string[iterator++]) & bit_block_six >> 4; // Get the 2 inmost bit
                    bits_next_num   = (string[iterator] >> 4) & bit_block_six >> 2; //Get the 4 outmost bit of the following element
                    bits_num = (bits_remain_num << 4) | (bits_next_num); //merge the number
                    break;
                case 3:;
                    bits_remain_num = (string[iterator++]) & bit_block_six >> 2; //Get the 4 inmost bit
                    bits_next_num   = (string[iterator] >> 6) & bit_block_six >> 4; //Get the 2 outmost bit of the following element
                    bits_num = (bits_remain_num << 2) | (bits_next_num); //merge the number
                    break;
                case 4:;
                    bits_num = (string[iterator]) & bit_block_six; // Get the 6 inmost bit
                    break;
                default:;
            }
            remain++;

            if (remain > 4){
                remain = 1;
                iterator++;
            }
            ret[ret_iterator++] = CLock_static_64bit_conversion(bits_num);
        }        
        
        for (int i = 0; i < 3 - (length % 3); i++)
            ret[ret_iterator + i] = PAD_CHARACTER;

        ret = realloc(ret, strlen(ret) + 1);
        return ret;
    }
    return NULL;
}

static char CLock_static_32bit_conversion(int c){
    return table32[c & 0x1F];
}

static char* CLock_parse_chunk_octet(char* octets_arr, size_t cur, size_t length){
    char* ret = malloc(8);
    size_t remain = 8;
    uint8_t bits_remain_num,  bits_next_num;

    if (ret){
        for (size_t i = 0, ret_count = 0; i < 5; i++){
                if (remain >= 5){
                    //Case when the current octet can still be parsed with one more 5-bit character
                    remain -= 5;
                    //If reach the end of the string, place the padding instead
                    ret[ret_count++] =  (cur + i >= length) ? '=' 
                                                            : CLock_static_32bit_conversion((octets_arr[i] >> remain) & 0x1F);
                    i--;
                }else{  
                    //Found the end of the string
                    //Here, the value of remain is < 5, which mean the 5 bit character are consisted in 2 subsequent octets
                    uint8_t next_remainder = (8 - (5 - remain));
                    uint8_t left     =  octets_arr[i] & (0xFF >> 8 - remain); //The half left exists in the current octets
                    uint8_t right    =  (octets_arr[i + 1] >> next_remainder) & (0xFF >> next_remainder);  //The half right in the next octets

                    ret[ret_count++] =  (cur + i >= length) ? '=' 
                                                            : CLock_static_32bit_conversion((left << 8 - next_remainder) | right);

                    remain = next_remainder; //Left off bit
                }   
        }
        return ret;
    }
    return NULL;
}

char* CLock_base32(char* string){
    char* ret = malloc(size);
    memset(ret, 0, size);

    size_t length = strlen(string);
    if (ret){
        for (int i = 0; i < length; i+=5){
            char* octets_arr = malloc(5);

            for (int j = 0; j < 5; j++)
                octets_arr[j] = j + i > length ? 0x0 : string[i + j];
                //When the end of string is each, we add extra = at the end

            char* chunk = CLock_parse_chunk_octet(octets_arr, i, length);
            free(octets_arr);
            strncat(ret, chunk, 8);
        }

        ret = realloc(ret, strlen(ret) + 1);
        return ret;
    }
    return NULL;
}

static char CLock_static_16bit_conversion(int c){
    return table16[c & 0xF];
}

char* CLock_base16(char* string){
    char* ret = malloc(size);
    memset(ret, 0, size);
    size_t length = strlen(string);
    if (ret){
        for (int i = 0; i < length; i++){
            char block[3]; //Each character is presentable with 2 character of 4 bytes, no edge case
            block[0] = CLock_static_16bit_conversion((string[i] >> 4)); 
            block[1] = CLock_static_16bit_conversion(string[i]);
            block[2] = '\0';
            strncat(ret, block, 3);
        }
        ret = realloc(ret, strlen(ret) + 1);
        return ret;
    }
    return NULL;
}
