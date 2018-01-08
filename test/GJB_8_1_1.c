void static_p(){
    int l = 1, O = 0;
    /*...*/
    l = O;
    O = l;
}

struct Node{
    int l, O;
};

struct Node O;
struct Node Ol;

void fun_p(int l, int O){
    l++;
    O++;
}