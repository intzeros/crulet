void static_p(void){
    float f = 0.0f;
    for(f = 0.0f; f < 10.0f; f = f + 1.0f){
        /*...*/
    }

    for(; 10.0f >= f; f = f - 1.0f){
        /*...*/
    }

    for(double d = 0.0; d != 5.0 && d <= f || 20 > d; d = d + 1.0f){
        /*...*/
    }

    for(int i = 0; i < (f = 5); i++){

    }
}