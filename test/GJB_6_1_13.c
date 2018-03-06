void static_p(void){
    enum E_type {
        Enum1, Enum2, Enum3
    };
    unsigned int ui = Enum3;
    ui = Enum1;
    /*...*/

    unsigned int a = 1;
    if(a == Enum1){
        // ...
    }

    if(Enum1 == Enum2){
        // ...
    }
}