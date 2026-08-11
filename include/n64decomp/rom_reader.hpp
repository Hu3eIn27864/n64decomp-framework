#pragma once

#include "n64decomp/result.hpp"
#include "n64decomp/rom.hpp"

#include <cstdint>
#include <filesystem>
#include <vector>

namespace n64decomp {

class RomReader {
public:
    [[nodiscard]]
    static Result<RomImage> load(
        const std::filesystem::path& path
    );

    [[nodiscard]]
    static Result<RomImage> from_bytes(
        std::vector<std::uint8_t> data
    );

private:
    [[nodiscard]]
    static RomByteOrder detect_byte_order(
        const std::vector<std::uint8_t>& data
    );

    static void normalize_byte_order(
        std::vector<std::uint8_t>& data,
        RomByteOrder byte_order
    );
};

} // namespace n64decomp
