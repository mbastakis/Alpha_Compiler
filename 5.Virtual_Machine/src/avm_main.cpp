#include <iostream>
#include <vector>

#include "../public/helper.hpp"
#include "../public/AVM.hpp"
#include "../public/arithmetic_exec.hpp"
#include "../public/jumps_exec.hpp"
#include "../public/funcs_exec.hpp"
#include "../public/tables_exec.hpp"
#include "../public/libfuncs_Impl.hpp"

//Definitions
//#define AVM_ENDING_PC codeSize;
//#define AVM_MAX_INSTRUCTIONS (unsigned int) NOP_OP;

// Function like macro definition
typedef void (*execute_func_t)(Instruction*);

execute_func_t executeFuncs[] = {
        execute_assign, execute_add, execute_sub,
        execute_mul, execute_div, execute_mod,
        execute_and, execute_or,
        execute_not, execute_jeq, execute_jne,
        execute_jle, execute_jge, execute_jlt,
        execute_jgt, execute_call, execute_pusharg,
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
        if (pc == oldPC)
            ++pc;
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

    std::vector<Instruction*> instructions = avm.getInstructions();
    codeSize = instructions.size();
    while (execute_cycle());

    return 0;
}