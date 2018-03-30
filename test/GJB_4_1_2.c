// void static_p(void){
//     unsigned int array[10] = {0};
//     unsigned int *p1_ptr, **p2_ptr;
//     unsigned int **p3_ptr;
//     unsigned int w;
//     p1_ptr = array;
//     p2_ptr = &p1_ptr;
//     p3_ptr = &p2_ptr;
//     w = ***p3_ptr;
// }

typedef struct Node{
    int *p1, **p2, ***p3; 
}Node;

typedef int * INTPTR;

struct S { 
    int *s1; /* compliant */ 
    int **s2; /* compliant */ 
    int ***s3; /* not compliant */ 
};

struct S* ps1;  /* compliant */
struct S** ps2;  /* compliant */
struct S*** ps3;  /* not compliant */

int ** (*pfunc1)();  /* compliant */
int ** (**pfunc2)();  /* compliant */
int ** (***pfunc3)();  /* not compliant */
int *** (**pfunc4)();  /* not compliant */
int ** (**pfunc5)(int **, int ***, int *** (**pfunc4)());   /* not compliant */

int a;

void function (int * par1,
               int ** par2,
               int *** par3,  /* not compliant */
               INTPTR * par4,
               INTPTR * const * const par5,  /* not compliant */
               int p[],
               int * par6[],
               int ** par7[])  /* not compliant */
{
    int * ptr1;
    int ** ptr2;
    int *** ptr3;    /* not compliant */
    INTPTR * ptr4;
    INTPTR * const * const ptr5;    /* not compliant */
    int * ptr6[10];
    int ** ptr7[10];      /* compliant */
}

