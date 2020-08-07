#ifndef _UNITY_CONFIG_INCLUDED
#define _UNITY_CONFIG_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include "main_test.h"


//-------------------------DEFINITIONS AND MACORS---------------------------



#define UNITY_OUTPUT_CHAR(a)    target_putc(a)
#define UNITY_OUTPUT_START()    target_init_putc()
#define UNITY_OUTPUT_FLUSH()    target_flush_putc()
#define UNITY_OUTPUT_COMPLETE() target_close_putc()

#define UNITY_EXCLUDE_MATH_H
//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _UNITY_CONFIG_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
void target_putc(char a);
void target_init_putc(void);
void target_flush_putc(void);
void target_close_putc(void);


#endif
