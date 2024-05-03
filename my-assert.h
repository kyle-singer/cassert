#pragma once

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "expand.h"

#define EMPTY()
#define DELAY(x) x EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DELAY(EMPTY)()

#define EXPAND C2CILK_EXPAND_100

typedef uintmax_t assert_print_t;
#define PRI_ASSERT PRIXMAX

#define ASSERT_PRINTF printf

#define CONDITION_cilk_cond(a) \
    (a)

#define CONDITION_FMT_cilk_cond(...) \
    "%s = %s"

#define CONDITION_VALS_cilk_cond(a) \
    #a, ((a) ? "true" : "false")

#define CONDITION_cilk_and(a, b) \
    ((OBSTRUCT(CONDITION_HELPER)()(a)) && (OBSTRUCT(CONDITION_HELPER)()(b)))

#define CONDITION_FMT_cilk_and(a, b) \
    OBSTRUCT(CONDITION_FMT_HELPER)()(a) ", " OBSTRUCT(CONDITION_FMT_HELPER)()(b)

#define CONDITION_VALS_cilk_and(a, b) \
    OBSTRUCT(CONDITION_VALS_HELPER)()(a), OBSTRUCT(CONDITION_VALS_HELPER)()(b)

#define CONDITION_cilk_eq(a, b) \
    (a) == (b)

#define CONDITION_FMT_cilk_eq(...) \
    "%s = 0x%" PRI_ASSERT ", %s = 0x%" PRI_ASSERT

/*
define C2CILK_MACRO_PARAMS_TO_FUNC_PARAMS(...)                                \
    C2CILK_EXPAND_PARAMS(                                                     \
            __VA_OPT__(                                                       \
                C2CILK_EXPAND_PARAMS(                                         \
                    C2CILK_MACRO_PARAMS_TO_FUNC_PARAMS_HELPER() (__VA_ARGS__) \
                )                                                             \
            )                                                                 \
    )

#define C2CILK_MACRO_PARAMS_TO_FUNC_PARAMS_HELPER() \
    C2CILK_MACRO_PARAMS_TO_FUNC_PARAMS_HELPER_HELPER

#define C2CILK_MACRO_PARAMS_TO_FUNC_PARAMS_HELPER_HELPER(_1, _2, ...) \
    _1 _2                                                             \
    __VA_OPT__(                                                       \
        , C2CILK_OBSTRUCT(C2CILK_MACRO_PARAMS_TO_FUNC_PARAMS_HELPER)  \
            ()(__VA_ARGS__)                                           \
    )
*/

#define CONDITION_VALS_cilk_eq(a, b) \
    #a, (assert_print_t)(a), #b, (assert_print_t)(b)

#define CONDITION(cond) \
    OBSTRUCT(CONDITION_HELPER)() (cond)

#define CONDITION_HELPER() \
    CONDITION_HELPER_HELPER

#define CONDITION_HELPER_HELPER(cond) CONDITION_ ## cond

#define CONDITION_FMT(cond) OBSTRUCT(CONDITION_FMT_HELPER)()(cond)
#define CONDITION_FMT_HELPER() CONDITION_FMT_HELPER_HELPER
#define CONDITION_FMT_HELPER_HELPER(cond) CONDITION_FMT_ ## cond

#define CONDITION_VALS(cond) OBSTRUCT(CONDITION_VALS_HELPER)()(cond)
#define CONDITION_VALS_HELPER() CONDITION_VALS_HELPER_HELPER
#define CONDITION_VALS_HELPER_HELPER(cond) CONDITION_VALS_ ## cond

#define PRINT_CONDITION(cond) \
    ASSERT_PRINTF("\t" EXPAND(CONDITION_FMT(cond)) "\n", EXPAND(CONDITION_VALS(cond)))

#define __cilk_delayed_stringify(var) #var

#define cilk_delayed_stringify(var) __cilk_delayed_stringify(var)

#define my_assert(cond)                                                        \
    do {                                                                       \
        if (__builtin_expect(EXPAND(CONDITION(cond)) == 0, 0)) {                     \
            printf("%s::%s::%d --> assertion \"%s\" failed\n",                  \
                    __FILE__, __PRETTY_FUNCTION__, __LINE__,                   \
                    "" cilk_delayed_stringify(cond));                  \
            PRINT_CONDITION(cond);                                             \
            /*exit(0xa5);*/                                                    \
        }                                                                      \
    } while (0)
