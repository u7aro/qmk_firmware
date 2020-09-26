#include <stdio.h>
#include "crkbd.h"

uint32_t type_count = 0;
char countlog_str[24] = {};

 void count_up(void){
    type_count++;
    snprintf(countlog_str, sizeof(countlog_str),"Typed | %"PRId32"",type_count);
}

 const char *read_countlog(void) {
  return countlog_str;
} 

