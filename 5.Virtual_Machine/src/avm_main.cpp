#include <iostream>
#include <vector>

#include "../public/Instruction.hpp"
#include "../public/AVM.hpp"
#include "../public/global_def.hpp"

//Definitions
//#define AVM_ENDING_PC codeSize;
//#define AVM_MAX_INSTRUCTIONS (unsigned int) NOP_OP;

// Function like macro definition
typedef void (*execute_func_t)(Instruction*);

extern void execute_assign(Instruction*);
extern void execute_add(Instruction*);
extern void execute_sub(Instruction*);
extern void execute_mul(Instruction*);
extern void execute_div(Instruction*);
extern void execute_mod(Instruction*);
extern void execute_and(Instruction*);
extern void execute_or(Instruction*);
extern void execute_not(Instruction*);
extern void execute_jeq(Instruction*);
extern void execute_jne(Instruction*);
extern void execute_jle(Instruction*);
extern void execute_jge(Instruction*);
extern void execute_jlt(Instruction*);
extern void execute_jgt(Instruction*);
extern void execute_call(Instruction*);
extern void execute_pusharg(Instruction*);
extern void execute_funcenter(Instruction*);
extern void execute_funcexit(Instruction*);
extern void execute_newtable(Instruction*);
extern void execute_tablegetelem(Instruction*);
extern void execute_tablesetelem(Instruction*);
extern void execute_nop(Instruction*);

void execute_jump(Instruction* instr) {
    assert(instr->result.type == LABEL_T);
    pc = instr->result.val;
    return;
}

execute_func_t executeFuncs[] = {
        execute_assign, execute_add, execute_sub,
        execute_mul, execute_div, execute_mod,
        execute_jeq, execute_jne, execute_jle,
        execute_jge, execute_jlt,execute_jgt,
        execute_and, execute_not, execute_or,
        execute_jump, execute_call, execute_pusharg,
        execute_funcenter, execute_funcexit, execute_newtable,
        execute_tablegetelem, execute_tablesetelem, execute_nop
};

bool execute_cycle() {
    if (executionFinished)
        return false;
    if (pc == codeSize) {
        executionFinished = 1;
        return false;
    }
    else {
        assert(pc < codeSize);
        Instruction* instr = avm.get(code, pc);
        assert(instr->opcode >= 0 && instr->opcode <= NOP_OP);
        if (instr->srcLine)
            currLine = instr->srcLine;
        unsigned int oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if (pc == oldPC) ++pc;
    }
    return true;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        red();
        std::cout << "Expected binary file as argument." << std::endl;
        reset();
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        red();
        std::cout << "Could not open file." << std::endl;
        reset();
        return -1;
    }
    avm.loadDataFromBinary(file);
    // avm.printTargetCode("");

    avm.libfuncs_map["print"] = print;
    avm.libfuncs_map["totalarguments"] = totalarguments;
    avm.libfuncs_map["typeof"] = typeof;
    avm.libfuncs_map["argument"] = argument;
    avm.libfuncs_map["cos"] = a_cos;
    avm.libfuncs_map["sin"] = a_sin;
    avm.libfuncs_map["sqrt"] = a_sqrt;
    avm.libfuncs_map["strtonum"] = strtonum;



    std::vector<Instruction*> instructions = avm.getInstructions();
    codeSize = instructions.size();
    while (true) {
        if (execute_cycle() == false) break;
        else continue;
    }

    return 0;
}