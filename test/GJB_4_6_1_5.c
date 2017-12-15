int static_p(void){
    unsigned int x = 1u;
    unsigned int y = 2u;
    /*...*/
    y = -x;
    unsigned int z = 0;
    // z = z+1;
    y = x / z;
    return y;
}

int main(){
    static_p();
}