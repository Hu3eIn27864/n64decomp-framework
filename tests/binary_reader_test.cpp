#include <cassert>
#include <cstdint>
#include <vector>

#include "n64decomp/io/binary_reader.hpp"

using namespace n64decomp::io;

int main() {
    BinaryReader reader({
        0x80, 0x37, 0x12, 0x40,
        0x12, 0x34, 0x56, 0x78
    });

    assert(reader.size() == 8);

    auto u32 = reader.read_u32(
        0,
        Endianness::Big
    );

    assert(u32);
    assert(u32.value() == 0x80371240);

    auto u16 = reader.read_u16(
        4,
        Endianness::Big
    );

    assert(u16);
    assert(u16.value() == 0x1234);

    auto invalid = reader.read_u64(
        4,
        Endianness::Big
    );

    assert(!invalid);

    return 0;
}