#define IF_X(x) if(x) {

void static_p(void){
    int test = 1;
    IF_X(test){
        test = !test;
    }
}