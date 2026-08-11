#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>

#include "n64decomp/core/result.hpp"
#include "n64decomp/io/binary_reader.hpp"

namespace n64decomp::n64 {

enum class RomByteOrder {
    BigEndian,
    ByteSwapped,
    LittleEndian,
    Unknown,
};

struct RomHeader {
    RomByteOrder byte_order = RomByteOrder::Unknown;

    std::uint32_t entry_point = 0;
    std::uint32_t crc1 = 0;
    std::uint32_t crc2 = 0;

    std::string title;
    std::string game_code;
};

class Rom {
public:
    [[nodiscard]]
    static Result<Rom> load(
        const std::filesystem::path& path
    );

    [[nodiscard]]
    static Result<Rom> from_bytes(
        std::vector<std::uint8_t> data
    );

    [[nodiscard]]
    const RomHeader& header() const noexcept;

    [[nodiscard]]
    const io::BinaryReader& reader() const noexcept;

    [[nodiscard]]
    std::size_t size() const noexcept;

private:
    Rom(
        io::BinaryReader reader,
        RomHeader header
    );

    io::BinaryReader reader_;
    RomHeader header_;
};

[[nodiscard]]
std::string_view to_string(RomByteOrder order) noexcept;

} // namespace n64decomp::n64