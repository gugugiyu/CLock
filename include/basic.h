#include <stdio.h>
#include <stdint.h>
#include "../include/const.h"

#ifndef __BASIC_H__
#define __BASIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

extern uint64_t mode;


/**
 * @brief This function config the option of the current encoder
 * 
 * @param mode The mode value assigned with OR operator
 */
void  CLock_mode_config(uint64_t modeS);

/**
 * @brief This function will encode the string by reversing it
 * 
 * @param string The given string
 */
char* CLock_reverse(const char* string);


/**
 * @brief This function will encode the string by perform rot13 encoding
 * 
 * @param string 
 * @return char* 
 */
char* CLock_rot13(const char* string);

#endif /* __FILE_NAME_H__ */