struct s_p{
    unsigned int xs;
    struct {
        unsigned char ac, ab;
    };
};

void static_p(void){
    struct s_p sb;
    sb.xs = 1;
    /*...*/

    int x;
    sb.xs = x;
}