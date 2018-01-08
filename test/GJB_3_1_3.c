void static_p(void){
    unsigned int name_x = 1u;

    /*...*/
    if(name_x == 0u){/*...*/}
    else;

    /*...*/
    if(name_x == 1u){/*...*/}
    else{
#if FALSE
        name_x = name_x + 5u;
#endif    
    }

    /*...*/
    if(name_x == 2u){/*...*/}
    else{;}

    if(name_x == 3u){/*...*/}
    else name_x++;
}