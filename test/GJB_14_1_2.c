void static_p(void){
    unsigned int x = 0u;
    if(x){
        /*...*/
    }

    for(x = 100; x; x--){
        
    }

    for(; ; );

    x = x ? 1u : 0u;
    x = x ? : 0u;
}
