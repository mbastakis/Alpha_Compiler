#ifndef AVM_HPP
#define AVM_HPP

#include <map>
#include <functional>
#include <vector>

#define AVM_STACKSIZE 4096  // memory_cell
#define AVM_STACKENV_SIZE 4 // avm

#include "helper.hpp"
#include "Instruction.hpp"
#include "Memory_Cell.hpp"

std::function<void(void)> libfunc_print;
std::function<void(void)> libfunc_input;
std::function<void(void)> libfunc_objectmemberkeys;
std::function<void(void)> libfunc_objecttotalmembers;
std::function<void(void)> libfunc_objectcopy;
std::function<void(void)> libfunc_totalarguments;
std::function<void(void)> libfunc_argument;
std::function<void(void)> libfunc_typeof;
std::function<void(void)> libfunc_strtonum;
std::function<void(void)> libfunc_sqrt;
std::function<void(void)> libfunc_cos;
std::function<void(void)> libfunc_sin;

Instruction* code;
std::vector<avm_memcell> stack(AVM_STACKSIZE);
unsigned int top, topsp;
unsigned char executionFinished = 0;
unsigned int pc = 0;
unsigned int codeSize = 0;
unsigned int currLine = 0;
avm_memcell ax, bx, cx, retval;

typedef struct {
    unsigned int address;
    unsigned int localSize;
    std::string id;
} userFunc;

/*extern void avm_warning(char* format,...)
  extern void avm_error(char* format,...)*/

class AVM {
public:
    AVM() {
        libfuncs_map.insert({ "print", libfunc_print });
        libfuncs_map.insert({ "input", libfunc_input });
        libfuncs_map.insert({ "objectmemberkeys", libfunc_objectmemberkeys });
        libfuncs_map.insert({ "objecttotalmembers", libfunc_objecttotalmembers });
        libfuncs_map.insert({ "objectcopy", libfunc_objectcopy });
        libfuncs_map.insert({ "totalarguments", libfunc_totalarguments });
        libfuncs_map.insert({ "argument", libfunc_argument });
        libfuncs_map.insert({ "typeof", libfunc_typeof });
        libfuncs_map.insert({ "strtonum", libfunc_strtonum });
        libfuncs_map.insert({ "sqrt", libfunc_sqrt });
        libfuncs_map.insert({ "cos", libfunc_cos });
        libfuncs_map.insert({ "sin", libfunc_sin });

        totalGlobals = 0;
    }

    void callLibFunc(std::string libfuncName);

    void loadDataFromBinary(FILE* file) {
        // Check magic number
        unsigned int magicNumber;
        fread(&magicNumber, sizeof(magicNumber), 1, file);
        if (magicNumber != 340200501) {
            red();
            std::cout << "Invalid binary file for alpha virtual machine." << std::endl;
            reset();
            exit(-1);
        }
        // std::cout << "Magic: " << magicNumber << std::endl;

        // Load const strings
        unsigned int size;
        fread(&size, sizeof(size), 1, file);
        // std::cout << "size strings: " << size << std::endl;
        for (int i = 0; i < size; i++) {
            const_strings.push_back(loadBinaryString(file));
            // std::cout << "str: " << const_strings[const_strings.size() - 1] << std::endl;
        }

        // Load const num
        fread(&size, sizeof(size), 1, file);
        // std::cout << "size num: " << size << std::endl;
        for (int i = 0; i < size; i++) {
            double num;
            fread(&num, sizeof(double), 1, file);
            // std::cout << "num: " << num << std::endl;
            const_numbers.push_back(num);
        }

        // Load user funcs
        fread(&size, sizeof(size), 1, file);
        // std::cout << "size userf: " << size << std::endl;
        unsigned int address, localSize;
        for (int i = 0; i < size; i++) {
            fread(&address, sizeof(address), 1, file);
            fread(&localSize, sizeof(localSize), 1, file);
            // std::cout << "addr, localsize: " << address << "," << localSize << std::endl;
            userFunc userfunc;
            userfunc.address = address;
            userfunc.localSize = localSize;
            userfunc.id = loadBinaryString(file);
            userfunctions.push_back(userfunc);
        }

        // Load library funcs
        fread(&size, sizeof(size), 1, file);
        // std::cout << "size lib: " << size << std::endl;
        for (int i = 0; i < size; i++) {
            libfuncs_used.push_back(loadBinaryString(file));
            // std::cout << "lib func: " << libfuncs_used[libfuncs_used.size() - 1] << std::endl;
        }

        // Load instructions
        fread(&size, sizeof(size), 1, file);
        // std::cout << "size instructions: " << size << std::endl;
        for (int i = 0; i < size; i++) {
            Instruction* inst = new Instruction();
            fread(&inst->opcode, sizeof(char), 1, file);
            // std::cout << "op: " << inst->opcode << std::endl;

            fread(&inst->result.type, sizeof(char), 1, file);
            fread(&inst->result.val, sizeof(unsigned int), 1, file);
            // std::cout << "result type, val: " << inst->result.to_string() << "," << inst->result.val << std::endl;

            fread(&inst->arg1.type, sizeof(char), 1, file);
            fread(&inst->arg1.val, sizeof(unsigned int), 1, file);
            // std::cout << "arg1 type, val: " << inst->arg1.to_string() << "," << inst->arg1.val << std::endl;

            fread(&inst->arg2.type, sizeof(char), 1, file);
            fread(&inst->arg2.val, sizeof(unsigned int), 1, file);
            // std::cout << "arg2 type, val: " << inst->arg2.to_string() << "," << inst->arg2.val << std::endl;

            fread(&inst->srcLine, sizeof(int), 1, file);
            // std::cout << "src line: " << inst->srcLine << std::endl;
            instructions.push_back(inst);

            if (inst->result.type == GLOBAL_T && inst->result.val + 1 > totalGlobals)
                totalGlobals = inst->result.val + 1;
            if (inst->arg1.type == GLOBAL_T && inst->arg1.val + 1 > totalGlobals)
                totalGlobals = inst->arg1.val + 1;
            if (inst->arg2.type == GLOBAL_T && inst->arg2.val + 1 > totalGlobals)
                totalGlobals = inst->arg2.val + 1;

            if (inst->result.type == LABEL_T)
                inst->result.val--;
            if (inst->arg1.type == LABEL_T)
                inst->arg1.val--;
            if (inst->arg2.type == LABEL_T)
                inst->arg2.val--;
        }

        code = instructions[0];
        top = AVM_STACKSIZE - totalGlobals - 1;
        topsp = AVM_STACKSIZE - totalGlobals - 1;
    }

    void printTargetCode(std::string filename) {
        FILE* file;
        if (filename == "") file = stdout;
        else file = fopen(std::string(filename + ".tc").c_str(), "wb");

        if (!file) {
            printf("File cannot open.\n");
            return;
        }
        fprintf(file, "Instruction#\t\tOpcode\t\tResult\t\tArg1\t\tArg2\n");
        fprintf(file, "===================================================================================\n");

        for (int i = 0; i < instructions.size(); i++) {

            Instruction curr = *instructions[i];

            fprintf(file, "%d:\t\t\t%s\t\t%s\t%s\t%s\n",
                i + 1,
                VMopToString(curr.opcode),
                curr.result.to_string() == "" ? "\t\t" : curr.result.to_string().c_str(),
                curr.arg1.to_string() == "" ? "\t\t" : curr.arg1.to_string().c_str(),
                curr.arg2.to_string() == "" ? "\t\t" : curr.arg2.to_string().c_str()
            );
        }
        fprintf(file, "===================================================================================\n");

        if (!const_numbers.empty()) {
            fprintf(file, "\nConst Numbers:\n");
            fprintf(file, "===================================================================================\n");
            for (int i = 0; i < const_numbers.size(); ++i)
                fprintf(file, "%d:\t%s\n", i, remove_extra_zero(modify_number(const_numbers[i])).c_str());
            fprintf(file, "===================================================================================\n");
        }

        if (!const_strings.empty()) {
            fprintf(file, "\nConst Strings:\n");
            fprintf(file, "===================================================================================\n");
            for (int i = 0; i < const_strings.size(); ++i)
                fprintf(file, "%d:\t%s\n", i, const_strings[i].c_str());
            fprintf(file, "===================================================================================\n");
        }

        if (!userfunctions.empty()) {
            fprintf(file, "\nUser Functions:\n");
            fprintf(file, "===================================================================================\n");
            for (int i = 0; i < userfunctions.size(); ++i)
                fprintf(file, "%d:\t%s\n", i, userfunctions[i].id.c_str());
            fprintf(file, "===================================================================================\n");
        }

        if (!libfuncs_used.empty()) {
            fprintf(file, "\nLibrary Functions:\n");
            fprintf(file, "===================================================================================\n");
            for (int i = 0; i < libfuncs_used.size(); ++i)
                fprintf(file, "%d:\t%s\n", i, libfuncs_used[i].c_str());
            fprintf(file, "===================================================================================\n");
        }
    }

    Instruction* get(Instruction* inst, unsigned int pc) {
        auto it = std::find(instructions.begin(), instructions.end(), inst);
        it = it + pc;
        return *it;
    }

    double getConstNumber(unsigned int index) {
        // std::cout << index << " " << const_numbers.size() << std::endl;
        assert(index <= const_numbers.size());
        return const_numbers[index];
    }

    std::string getConstString(unsigned int index) {
        assert(index <= const_strings.size());
        return const_strings[index];
    }

    userFunc getUserFunction(unsigned int index) {
        assert(index <= userfunctions.size());
        return userfunctions[index];
    }

    std::string getLibFunction(unsigned int index) {
        assert(index <= libfuncs_used.size());
        return libfuncs_used[index];
    }

    std::vector<Instruction*> getInstructions() {
        return instructions;
    }

    avm_memcell* avm_translate_operand(VMarg* arg, avm_memcell* reg) {
        switch (arg->type)
        {
        case GLOBAL_T:
            return &stack[AVM_STACKSIZE - 1 - arg->val];
        case LOCAL_T:
            return &stack[topsp - arg->val];
        case FORMAL_T:
            return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
        case RETVAL_T:
            return &retval;
        case NUMBER_T: {
            reg->type = NUMBER_M;
            reg->data = getConstNumber(arg->val);
            return reg;
        }
        case STRING_T: {
            reg->type = STRING_M;
            reg->data = getConstString(arg->val);
            return reg;
        }
        case BOOL_T: {
            reg->type = BOOL_M;
            reg->data = arg->val;
            return reg;
        }
        case NIL_T: {
            reg->type = NIL_M;
            return reg;
        }
        case USERFUNC_T: {
            reg->type = USERFUNC_M;
            reg->data = arg->val;
            return reg;
        }
        case LIBFUNC_T: {
            reg->type = LIBFUNC_M;
            reg->data = getLibFunction(arg->val);
            return reg;
        }
        default:
            assert(0);
        }
    }

    // Lib func map
    std::map<std::string, std::function<void(void)>> libfuncs_map{};
    unsigned int totalGlobals;
private:
    // Code
    std::vector<Instruction*> instructions{};
    // Const Tables
    std::vector<double> const_numbers{};
    std::vector<std::string> const_strings{};
    std::vector<userFunc> userfunctions{};
    std::vector<std::string> libfuncs_used{};
};

AVM avm{};

#endif