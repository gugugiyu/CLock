#ifndef __BASE_ENCODER_H__
#define __BASE_ENCODER_H__

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif


static char CLock_static_64bit_conversion(int c);
/**
 * @brief This function will encode the string using the base64 method
 * 
 * @param string The given string
 * @param opt_arr The optional binary array that contains '0' and '1'
 * @return char* 
 */
char* CLock_base64(char* string);


static char CLock_static_32bit_conversion(int c);
/**
 * @brief This function will encode the string using the base32 method
 * 
 * @param string The given string
 * @return char* 
 */
char* CLock_base32(char* string);

static char CLock_static_16bit_conversion(int c);
/**
 * @brief This function will encode the string using the base32 method
 * 
 * @param string The given string
 * @return char* 
 */
char* CLock_base16(char* string);
#endif