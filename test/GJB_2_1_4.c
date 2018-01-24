#include <stdbool.h>

void static_p(void){
    bool flag = true;
    unsigned int y = 0u, x = 0u, z = 1u;
    /*...*/
    if(x < 0 || z + y != 0 && !flag){
        flag = false;
    }

    for(int i = 0; i < 10 && x < 0 || z + y != 0 && !flag; i++){
        y++;
    }

    while(x < 0 || z + y != 0 || !flag){
        flag = false;
    }

    do{
        flag = false;
    }while(x < 0 && z + y != 0 && !flag);
}