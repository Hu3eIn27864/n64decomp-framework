#include "n64decomp/rom_reader.hpp"

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace n64decomp;

namespace {

std::vector<std::uint8_t> make_z64_data() {
    return {
        0x80, 0x37, 0x12, 0x40,
        0x01, 0x02, 0x03, 0x04,
        0x10, 0x20, 0x30, 0x40,
    };
}

std::vector<std::uint8_t> make_v64_data() {
    return {
        0x37, 0x80, 0x40, 0x12,
        0x02, 0x01, 0x04, 0x03,
        0x20, 0x10, 0x40, 0x30,
    };
}

std::vector<std::uint8_t> make_n64_data() {
    return {
        0x40, 0x12, 0x37, 0x80,
        0x04, 0x03, 0x02, 0x01,
        0x40, 0x30, 0x20, 0x10,
    };
}

void assert_normalized(
    const Result<RomImage>& result
) {
    assert(result);

    const auto& rom = result.value();

    assert(rom.size() == 12);

    const auto bytes = rom.bytes();

    const std::vector<std::uint8_t> expected = {
        0x80, 0x37, 0x12, 0x40,
        0x01, 0x02, 0x03, 0x04,
        0x10, 0x20, 0x30, 0x40,
    };

    assert(
        std::vector<std::uint8_t>(
            bytes.begin(),
            bytes.end()
        ) == expected
    );
}

} // namespace

int main() {
    // ---------------------------------------------------------
    // Big endian / .z64
    // ---------------------------------------------------------

    auto z64 = RomReader::from_bytes(
        make_z64_data()
    );

    assert(z64);
    assert(
        z64.value().original_byte_order() ==
        RomByteOrder::BigEndian
    );

    assert_normalized(z64);

    // ---------------------------------------------------------
    // Byte swapped / .v64
    // ---------------------------------------------------------

    auto v64 = RomReader::from_bytes(
        make_v64_data()
    );

    assert(v64);
    assert(
        v64.value().original_byte_order() ==
        RomByteOrder::ByteSwapped
    );

    assert_normalized(v64);

    // ---------------------------------------------------------
    // Little endian / .n64
    // ---------------------------------------------------------

    auto n64 = RomReader::from_bytes(
        make_n64_data()
    );

    assert(n64);
    assert(
        n64.value().original_byte_order() ==
        RomByteOrder::LittleEndian
    );

    assert_normalized(n64);

    // ---------------------------------------------------------
    // Too small
    // ---------------------------------------------------------

    auto too_small =
        RomReader::from_bytes({
            0x80,
            0x37,
            0x12,
        });

    assert(!too_small);
    assert(too_small.has_errors());
    assert(
        too_small.diagnostics().size() == 1
    );

    assert(
        too_small.diagnostics()
            .diagnostics()[0]
            .code ==
        DiagnosticCode::InvalidRom
    );

    // ---------------------------------------------------------
    // Unknown magic
    // ---------------------------------------------------------

    auto unknown =
        RomReader::from_bytes({
            0xDE,
            0xAD,
            0xBE,
            0xEF,
        });

    assert(!unknown);
    assert(unknown.has_errors());

    assert(
        unknown.diagnostics()
            .diagnostics()[0]
            .code ==
        DiagnosticCode::UnsupportedFormat
    );

    // ---------------------------------------------------------
    // Empty data
    // ---------------------------------------------------------

    auto empty =
        RomReader::from_bytes({});

    assert(!empty);
    assert(empty.has_errors());

    assert(
        empty.diagnostics()
            .diagnostics()[0]
            .code ==
        DiagnosticCode::InvalidRom
    );

    return 0;
}
