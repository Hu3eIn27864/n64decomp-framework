#include "n64decomp/n64/rom.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

namespace n64decomp::n64 {

namespace {

constexpr std::uint32_t N64_Z64_MAGIC = 0x80371240;
constexpr std::uint32_t N64_V64_MAGIC = 0x37804012;
constexpr std::uint32_t N64_N64_MAGIC = 0x40123780;

std::vector<std::uint8_t> normalize_byte_order(
    std::vector<std::uint8_t> data,
    RomByteOrder order
) {
    if (order == RomByteOrder::BigEndian) {
        return data;
    }

    if (order == RomByteOrder::ByteSwapped) {
        for (std::size_t i = 0; i + 1 < data.size(); i += 2) {
            std::swap(data[i], data[i + 1]);
        }

        return data;
    }

    if (order == RomByteOrder::LittleEndian) {
        for (std::size_t i = 0; i + 3 < data.size(); i += 4) {
            std::swap(data[i], data[i + 3]);
            std::swap(data[i + 1], data[i + 2]);
        }

        return data;
    }

    return data;
}

Result<RomByteOrder> detect_byte_order(
    const io::BinaryReader& reader
) {
    auto magic_result = reader.read_u32(
        0,
        io::Endianness::Big
    );

    if (!magic_result) {
        return make_error<RomByteOrder>(
            "ROM is too small to contain an N64 magic value"
        );
    }

    switch (magic_result.value()) {
    case N64_Z64_MAGIC:
        return RomByteOrder::BigEndian;

    case N64_V64_MAGIC:
        return RomByteOrder::ByteSwapped;

    case N64_N64_MAGIC:
        return RomByteOrder::LittleEndian;

    default:
        return make_error<RomByteOrder>(
            "Unrecognized N64 ROM byte-order magic"
        );
    }
}

Result<RomHeader> parse_header(
    const io::BinaryReader& reader,
    RomByteOrder original_order
) {
    if (reader.size() < 0x40) {
        return make_error<RomHeader>(
            "ROM is smaller than the 0x40-byte N64 header"
        );
    }

    auto entry_result = reader.read_u32(
        0x08,
        io::Endianness::Big
    );

    auto crc1_result = reader.read_u32(
        0x10,
        io::Endianness::Big
    );

    auto crc2_result = reader.read_u32(
        0x14,
        io::Endianness::Big
    );

    auto title_result = reader.read_string(
        0x20,
        20
    );

    auto code_result = reader.read_string(
        0x3B,
        4
    );

    if (!entry_result ||
        !crc1_result ||
        !crc2_result ||
        !title_result ||
        !code_result) {

        return make_error<RomHeader>(
            "Failed to parse N64 ROM header"
        );
    }

    RomHeader header;

    header.byte_order = original_order;
    header.entry_point = entry_result.value();
    header.crc1 = crc1_result.value();
    header.crc2 = crc2_result.value();

    header.title = std::string(title_result.value());

    while (!header.title.empty() &&
           (header.title.back() == '\0' ||
            header.title.back() == ' ')) {
        header.title.pop_back();
    }

    header.game_code = std::string(code_result.value());

    return header;
}

} // namespace

Result<Rom> Rom::load(
    const std::filesystem::path& path
) {
    std::ifstream file(
        path,
        std::ios::binary
    );

    if (!file) {
        return make_error<Rom>(
            "Unable to open ROM file: " +
            path.string()
        );
    }

    file.seekg(
        0,
        std::ios::end
    );

    const auto size = file.tellg();

    if (size < 0) {
        return make_error<Rom>(
            "Unable to determine ROM file size"
        );
    }

    file.seekg(
        0,
        std::ios::beg
    );

    std::vector<std::uint8_t> data(
        static_cast<std::size_t>(size)
    );

    if (!data.empty()) {
        file.read(
            reinterpret_cast<char*>(data.data()),
            static_cast<std::streamsize>(data.size())
        );
    }

    if (!file && !file.eof()) {
        return make_error<Rom>(
            "Failed while reading ROM file: " +
            path.string()
        );
    }

    return from_bytes(std::move(data));
}

Result<Rom> Rom::from_bytes(
    std::vector<std::uint8_t> data
) {
    io::BinaryReader initial_reader(
        data
    );

    auto order_result = detect_byte_order(
        initial_reader
    );

    if (!order_result) {
        return make_error<Rom>(
            order_result.error().message()
        );
    }

    const auto order = order_result.value();

    data = normalize_byte_order(
        std::move(data),
        order
    );

    io::BinaryReader normalized_reader(
        std::move(data)
    );

    auto header_result = parse_header(
        normalized_reader,
        order
    );

    if (!header_result) {
        return make_error<Rom>(
            header_result.error().message()
        );
    }

    return Rom(
        std::move(normalized_reader),
        header_result.value()
    );
}

Rom::Rom(
    io::BinaryReader reader,
    RomHeader header
)
    : reader_(std::move(reader)),
      header_(std::move(header)) {
}

const RomHeader& Rom::header() const noexcept {
    return header_;
}

const io::BinaryReader& Rom::reader() const noexcept {
    return reader_;
}

std::size_t Rom::size() const noexcept {
    return reader_.size();
}

std::string_view to_string(
    RomByteOrder order
) noexcept {
    switch (order) {
    case RomByteOrder::BigEndian:
        return "BigEndian";

    case RomByteOrder::ByteSwapped:
        return "ByteSwapped";

    case RomByteOrder::LittleEndian:
        return "LittleEndian";

    default:
        return "Unknown";
    }
}

} // namespace n64decomp::n64