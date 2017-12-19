#include <stdbool.h>

void static_p(void){
    unsigned int y = 2u;
    bool flag = false;
    flag = flag & (y == 2u);
}