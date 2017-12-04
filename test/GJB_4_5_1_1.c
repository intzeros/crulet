#include <setjmp.h>

static void static_p(jmp_buf mark, unsigned int val){
    longjump(mark, val);
}