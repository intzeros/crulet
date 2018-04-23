#define IF_X(x) if(x) {
#define IF_X2(x) if(x) { x++; }

void static_p(void){
    int test = 1;
    IF_X(test)
        test = !test;
    }
}