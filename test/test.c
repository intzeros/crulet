void static_p(void){
    long arr[10] = {100};
    const unsigned int y = 64u;
    arr[0] <<= y;
    arr[1] = y >> 32;
}
