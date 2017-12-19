#include <stdbool.h>

void static_p(void){
    unsigned int x = 1u;
    bool flag = false;
    /*...*/
    if((flag | (x != 0)) == false){
        /*...*/
    }
}