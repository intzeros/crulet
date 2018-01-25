#include <stdio.h>

#define PRINT(n) printf( "token"#n" = %d", token##n )

int main(void){
    int token5 = 9;
    PRINT(5);
    return 0;
}