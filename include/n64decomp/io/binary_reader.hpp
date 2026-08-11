#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

#include "n64decomp/core/result.hpp"

namespace n64decomp::io {

enum class Endianness {
    Big,
    Little,
};

class BinaryReader {
public:
    BinaryReader() = default;

    explicit BinaryReader(std::vector<std::uint8_t> data);

    [[nodiscard]]
    std::size_t size() const noexcept;

    [[nodiscard]]
    bool empty() const noexcept;

    [[nodiscard]]
    std::span<const std::uint8_t> data() const noexcept;

    [[nodiscard]]
    Result<std::uint8_t> read_u8(std::size_t offset) const;

    [[nodiscard]]
    Result<std::uint16_t> read_u16(
        std::size_t offset,
        Endianness endian
    ) const;

    [[nodiscard]]
    Result<std::uint32_t> read_u32(
        std::size_t offset,
        Endianness endian
    ) const;

    [[nodiscard]]
    Result<std::uint64_t> read_u64(
        std::size_t offset,
        Endianness endian
    ) const;

    [[nodiscard]]
    Result<std::span<const std::uint8_t>> read_bytes(
        std::size_t offset,
        std::size_t count
    ) const;

    [[nodiscard]]
    Result<std::string_view> read_string(
        std::size_t offset,
        std::size_t count
    ) const;

private:
    std::vector<std::uint8_t> data_;
};

} // namespace n64decomp::io