#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace n64decomp {

enum class RomByteOrder {
    BigEndian,
    ByteSwapped,
    LittleEndian,
};

class RomImage {
public:
    RomImage(
        std::vector<std::uint8_t> data,
        RomByteOrder original_byte_order
    );

    [[nodiscard]] const std::vector<std::uint8_t>& data() const noexcept;

    [[nodiscard]] std::span<const std::uint8_t> bytes() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;

    [[nodiscard]] RomByteOrder original_byte_order() const noexcept;

    [[nodiscard]] std::uint8_t byte(std::size_t offset) const noexcept;

private:
    std::vector<std::uint8_t> data_;
    RomByteOrder original_byte_order_;
};

} // namespace n64decomp
