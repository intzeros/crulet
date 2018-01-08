void static_p(void){
    float f1, f2;
    f1 = 1.01f;
    f2 = 2.01f;
    /*...*/
    if(f1 == f2){
        /*...*/
    }
    if(f1 == 0.0f){
        f1 = f1 + 0.01f;
    }
}
