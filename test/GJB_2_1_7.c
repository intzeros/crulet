void static_p(void){
    unsigned int x;
    x = 0u;
    _asm
    {
        mov eax, x
    }
}