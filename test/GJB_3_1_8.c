int static_p(int p_1){
    int i = 0, j = 0;
    /*...*/
    switch(p_1){
        case 0:
            j = 0;
            break;
        case 1:
        case 2:
            j = i;
            break;
        default:
            i = j+1;
    }
    return i+j;
}