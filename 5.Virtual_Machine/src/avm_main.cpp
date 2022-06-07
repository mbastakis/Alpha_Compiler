#include <iostream>
#include <vector>

#include "../public/helper.hpp"
#include "../public/AVM.hpp"




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

    AVM avm{};
    avm.loadDataFromBinary(file);

    avm.printTargetCode("");

    return 0;
}