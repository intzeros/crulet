void static_p(void){
    unsigned int x = 1u;
    unsigned int y = 200000u;
    x <<= 32;   //
    x = y << 31;
    x = y << 32;    //
    
    x = 33u;
    x = y << x;

    const unsigned int z = 33u;
    x = y << z; //

    char a = 'c';
    a >>= 8;   //

    short b = 2;
    b >>= 16;   //

    long c = 3;
    c >>= 64;   //

    long long d = 3;
    d >>= (z + 40u);    //
    d >>= (z + 10u);

    int arr[10] = {0};
    arr[3] = arr[0] << 32;  //
}