void static_p(double d){
    float f1 = 2.0f;
    double db1 = 3.0;
    /*...*/
    f1 = db1;

    int x = f1;
}

int main(){
    static_p(12);
    return 0;
}