#include <stdbool.h>

void static_p(void){
    bool flag = false;
    unsigned int x = 0u, y = 0u;
    /*...*/
    if(flag && ((x = y) == 0)){
        /*...*/
    }
}