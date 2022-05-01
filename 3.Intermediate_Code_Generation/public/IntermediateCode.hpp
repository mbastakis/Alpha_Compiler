#ifndef INTERMEDIATECODE_HPP
#define INTERMEDIATECODE_HPP

typedef enum {
    op_assign,
    op_add,
    op_sub,
    op_mul,
    op_div,
    op_mod,
    op_uminus,
    op_and,
    op_or,
    op_not,
    op_if_eq,
    op_if_noteq,
    op_if_lesseq,
    op_if_greatereq,
    op_if_less,
    op_if_greater,
    op_jump,
    op_call,
    op_param,
    op_ret,
    op_getretval,
    op_funcstart,
    op_funcend,
    op_tablecreate,
    op_tablegetelem,
    op_tablesetelem
} opcode;

typedef enum {

} expr;

#endif 