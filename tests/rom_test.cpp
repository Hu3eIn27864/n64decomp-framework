#include <cassert>
#include <cstdint>
#include <vector>

#include "n64decomp/n64/rom.hpp"

using namespace n64decomp::n64;

int main() {
    std::vector<std::uint8_t> rom(
        0x1000,
        0
    );

    // N64 big-endian magic.
    rom[0x00] = 0x80;
    rom[0x01] = 0x37;
    rom[0x02] = 0x12;
    rom[0x03] = 0x40;

    // Entry point = 0x80000400.
    rom[0x08] = 0x80;
    rom[0x09] = 0x00;
    rom[0x0A] = 0x04;
    rom[0x0B] = 0x00;

    // CRC1.
    rom[0x10] = 0x12;
    rom[0x11] = 0x34;
    rom[0x12] = 0x56;
    rom[0x13] = 0x78;

    // CRC2.
    rom[0x14] = 0x87;
    rom[0x15] = 0x65;
    rom[0x16] = 0x43;
    rom[0x17] = 0x21;

    const char title[] = "N64 TEST ROM";

    for (std::size_t i = 0; i < sizeof(title) - 1; ++i) {
        rom[0x20 + i] =
            static_cast<std::uint8_t>(title[i]);
    }

    rom[0x3B] = 'T';
    rom[0x3C] = 'E';
    rom[0x3D] = 'S';
    rom[0x3E] = 'T';

    auto result = Rom::from_bytes(
        std::move(rom)
    );

    assert(result);

    const auto& loaded = result.value();
    const auto& header = loaded.header();

    assert(
        header.byte_order ==
        RomByteOrder::BigEndian
    );

    assert(
        header.entry_point ==
        0x80000400
    );

    assert(
        header.crc1 ==
        0x12345678
    );

    assert(
        header.crc2 ==
        0x87654321
    );

    assert(
        header.title ==
        "N64 TEST ROM"
    );

    assert(
        header.game_code ==
        "TEST"
    );

    return 0;
}