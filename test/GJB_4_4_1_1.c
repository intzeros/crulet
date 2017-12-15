unsigned int *static_p(unsigned int *p1_ptr){
    static unsigned int w = 10u;
    /*...*/
    p1_ptr = &w;
    /*...*/
    return &w;
}