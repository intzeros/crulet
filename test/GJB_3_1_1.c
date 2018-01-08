void static_p(void){
    unsigned int value_x = 1u;

    /*...*/
    if(value_x == 0u);

    /*...*/
    if(value_x == 1u){
#if FALSE
        value_x = value_x + 5u;
#endif
    }

    /*...*/
    if(value_x == 2u) {; }

    /*...*/
    if(value_x == 3u) { }

    if(value_x == 4u) { 
        ;
        value_x++;
    }

    if(value_x == 5u) value_x--;
}