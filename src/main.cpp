#include <iostream>

#include <n64decomp/version.hpp>

int main()
{
    std::cout
        << "n64decomp "
        << n64decomp::VERSION
        << '\n';

    std::cout
        << "Generic Nintendo 64 / MIPS "
           "decompilation framework\n";

    return 0;
}
