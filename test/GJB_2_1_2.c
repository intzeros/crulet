int static_p(int p_1){
    int j = 0;
    int k = 0;
    /*...*/
    for(k = 0; k < 10; k = k+1) j--;
    for(k = 0; k < 10; k = k+1) ;
    for(k = 0; k < 10; k = k+1){
        j--;
    }

    while(j < 10) j++;

    do
      j++;
    while(j < 10);

    return j;
}