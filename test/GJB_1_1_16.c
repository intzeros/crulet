unsigned int static_p(void);
struct static_p{
    unsigned int static_p;
    unsigned int u_1;
};

unsigned int static_p(void){
    unsigned int var_1;
    /*...*/
static_p:
    var_1 = 1u; 
    /*...*/
    return (var_1);
}