void static_p(void){
    int a = 6;
    a >>= 2;

    unsigned int b = 6;
    b >>= 2;
    b = b >> a;

    int arr[3] = {-1, 2, 10};
    arr[0] <<= a;
    arr[0] = arr[1] << b;
}