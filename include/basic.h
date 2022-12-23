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

extern volatile uint64_t mode, size;


/**
 * @brief This function config the option of the current encoder
 * 
 * @param size The buffer size for storing the string
 * @param mode The mode value assigned with OR operator
 */
void  CLock_mode_config(buffer_size _size, uint64_t modeS);

/**
 * @brief This function will encode the string by reversing it
 * 
 * @param string The given string
 */
char* CLock_reverse(size_t perform, const char* string);


/**
 * @brief This function will encode the string by perform rot13 encoding
 * 
 * @param string 
 * @return char* 
 */
char* CLock_rot(size_t perform, const char* string, size_t rotateTime);

/**
 * @brief This function will encode the string by perform binary encoding
 * 
 * @param string The given string
 * @param bits_take The number of binary to cast out (note that if the bits_take is lower than the actual threshold needed for display, this number might be corrupted)
 * @return uint64_t* An array of unsigned 64 bit int, each element represent the encoding
 */
char* CLock_bin(const char* string, size_t bits_take);


/**
 * @brief This function will encode the string using the morse method
 * 
 * @param string The given string
 * @return char* 
 */
char* Clock_morse(size_t perform, char *string);
#endif /* __FILE_NAME_H__ */