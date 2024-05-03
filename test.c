#include "my-assert.h"
#include <stdbool.h>

int main(int argc, char *argv[]) {
    int z = 0;
    //my_assert(z);
    bool is_boss = false;
    my_assert(cilk_eq(z, 1));
    my_assert(cilk_cond(is_boss));
    my_assert(cilk_and(cilk_cond(42), cilk_cond(z)));
    my_assert(cilk_and(cilk_and(cilk_cond(true), cilk_cond(false)), cilk_cond(true)));

    return 0;
}
