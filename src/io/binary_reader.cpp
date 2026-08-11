#include "n64decomp/io/binary_reader.hpp"

#include <cstring>

namespace n64decomp::io {

BinaryReader::BinaryReader(std::vector<std::uint8_t> data)
    : data_(std::move(data)) {
}

std::size_t BinaryReader::size() const noexcept {
    return data_.size();
}

bool BinaryReader::empty() const noexcept {
    return data_.empty();
}

std::span<const std::uint8_t> BinaryReader::data() const noexcept {
    return data_;
}

Result<std::uint8_t> BinaryReader::read_u8(std::size_t offset) const {
    if (offset >= data_.size()) {
        return make_error<std::uint8_t>(
            "BinaryReader: read_u8 out of bounds"
        );
    }

    return data_[offset];
}

Result<std::uint16_t> BinaryReader::read_u16(
    std::size_t offset,
    Endianness endian
) const {
    if (offset + 2 > data_.size()) {
        return make_error<std::uint16_t>(
            "BinaryReader: read_u16 out of bounds"
        );
    }

    const auto b0 = data_[offset];
    const auto b1 = data_[offset + 1];

    if (endian == Endianness::Big) {
        return static_cast<std::uint16_t>(
            (static_cast<std::uint16_t>(b0) << 8) |
            static_cast<std::uint16_t>(b1)
        );
    }

    return static_cast<std::uint16_t>(
        (static_cast<std::uint16_t>(b1) << 8) |
        static_cast<std::uint16_t>(b0)
    );
}

Result<std::uint32_t> BinaryReader::read_u32(
    std::size_t offset,
    Endianness endian
) const {
    if (offset + 4 > data_.size()) {
        return make_error<std::uint32_t>(
            "BinaryReader: read_u32 out of bounds"
        );
    }

    const auto b0 = data_[offset];
    const auto b1 = data_[offset + 1];
    const auto b2 = data_[offset + 2];
    const auto b3 = data_[offset + 3];

    if (endian == Endianness::Big) {
        return
            (static_cast<std::uint32_t>(b0) << 24) |
            (static_cast<std::uint32_t>(b1) << 16) |
            (static_cast<std::uint32_t>(b2) << 8) |
            static_cast<std::uint32_t>(b3);
    }

    return
        (static_cast<std::uint32_t>(b3) << 24) |
        (static_cast<std::uint32_t>(b2) << 16) |
        (static_cast<std::uint32_t>(b1) << 8) |
        static_cast<std::uint32_t>(b0);
}

Result<std::uint64_t> BinaryReader::read_u64(
    std::size_t offset,
    Endianness endian
) const {
    if (offset + 8 > data_.size()) {
        return make_error<std::uint64_t>(
            "BinaryReader: read_u64 out of bounds"
        );
    }

    std::uint64_t value = 0;

    if (endian == Endianness::Big) {
        for (std::size_t i = 0; i < 8; ++i) {
            value <<= 8;
            value |= data_[offset + i];
        }
    } else {
        for (std::size_t i = 0; i < 8; ++i) {
            value |=
                static_cast<std::uint64_t>(data_[offset + i])
                << (i * 8);
        }
    }

    return value;
}

Result<std::span<const std::uint8_t>> BinaryReader::read_bytes(
    std::size_t offset,
    std::size_t count
) const {
    if (offset > data_.size() ||
        count > data_.size() - offset) {

        return make_error<std::span<const std::uint8_t>>(
            "BinaryReader: read_bytes out of bounds"
        );
    }

    return std::span<const std::uint8_t>(
        data_.data() + offset,
        count
    );
}

Result<std::string_view> BinaryReader::read_string(
    std::size_t offset,
    std::size_t count
) const {
    if (offset > data_.size() ||
        count > data_.size() - offset) {

        return make_error<std::string_view>(
            "BinaryReader: read_string out of bounds"
        );
    }

    return std::string_view(
        reinterpret_cast<const char*>(data_.data() + offset),
        count
    );
}

} // namespace n64decomp::io