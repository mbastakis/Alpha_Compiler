#ifndef MEMORY_CELL
#define MEMORY_CELL

typedef enum {
    NUMBER_T, //=0
    STRING_T,
    BOOL_M,
    TABLE_M,
    USERFUNC_M,
    LIBFUNC_M,
    NIL_M,
    UNDEFINED_T
} avm_memcell_t;


#endif
