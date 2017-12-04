void static_p(void){
    int jump_flag = 0;
    /*...*/
start:
    jump_flag++;
    if(jump_flag < 10){
        goto start;
    }
}