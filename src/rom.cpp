#include "n64decomp/rom.hpp"

#include <utility>

namespace n64decomp {

RomImage::RomImage(
    std::vector<std::uint8_t> data,
    RomByteOrder original_byte_order
)
    : data_(std::move(data)),
      original_byte_order_(original_byte_order) {
}

const std::vector<std::uint8_t>&
RomImage::data() const noexcept {
    return data_;
}

std::span<const std::uint8_t>
RomImage::bytes() const noexcept {
    return std::span<const std::uint8_t>(
        data_.data(),
        data_.size()
    );
}

std::size_t RomImage::size() const noexcept {
    return data_.size();
}

RomByteOrder RomImage::original_byte_order() const noexcept {
    return original_byte_order_;
}

std::uint8_t RomImage::byte(
    std::size_t offset
) const noexcept {
    if (offset >= data_.size()) {
        return 0;
    }

    return data_[offset];
}

} // namespace n64decomp
