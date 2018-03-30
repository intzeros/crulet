#include <stdbool.h>
#include "GJB_7_1_3.h"

static bool static_p(unsigned int);

static bool static_p(unsigned int p_1){
  bool ret = false;
  unsigned int i = p_1 + 1u;
  
  if(i == 0){
    ret = false;
  }
  return ret;
}

void main(void){
  // static_p(1);
  // static_p2(2);
}