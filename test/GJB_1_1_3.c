struct s_p{
    unsigned int xs;
    struct {
        unsigned char ac, ab;
    };
};

struct s_p2{
    unsigned int xs;
    struct x123{
        unsigned char ac, ab;
    }y456;
};

struct s_p3{
    unsigned int xs;
    struct {
        unsigned char ac, ab;
    }y456;
};

struct s_p4{
    unsigned int xs;
    struct x789{
        unsigned char ac, ab;
    };
};

void static_p(int xs){
    struct s_p sb;
    // sb.xs = 1;
    /*...*/

    int x;
    sb.xs = x;
}
