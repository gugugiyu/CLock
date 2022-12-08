#ifndef __CONST_H__
#define __CONST_H__

#ifdef __cplusplus
extern "C" {
#endif


#define TRUE 1
#define FALSE 0

#define BUFFER_SMALL     ((1 << 10) + 1)
#define BUFFER_MEDIUM    ((1 << 12) + 1)
#define BUFFER_LARGE     ((1 << 14) + 1)
#define BUFFE_VERY_LARGE ((1 << 16) + 1)

#define IGNORE_WHITESPACE 1 //0000 0001
#define UPPERCASE    2 //0000 0010
#define LOWERCASE    4 //0000 0100

#define SWAP(a,b)    char temp = a;\
                     a = b;\
                     b = temp;


#ifdef __cplusplus
}
#endif

#endif /* __FILE_NAME_H__ */