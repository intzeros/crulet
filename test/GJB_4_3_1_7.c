void static_p(int p_1){
    int i = 0, j = 0;
    switch(p_1){
        case 0:
            j = 0;
        case 1:
            j = i;
            i = 123;
            break;
        default:
            i = j+1;
    }
    /*...*/
}