#include "n64decomp/rom_reader.hpp"

#include <fstream>
#include <iterator>
#include <utility>

namespace n64decomp {

namespace {

constexpr std::uint8_t Z64_MAGIC_0 = 0x80;
constexpr std::uint8_t Z64_MAGIC_1 = 0x37;
constexpr std::uint8_t Z64_MAGIC_2 = 0x12;
constexpr std::uint8_t Z64_MAGIC_3 = 0x40;

constexpr std::uint8_t V64_MAGIC_0 = 0x37;
constexpr std::uint8_t V64_MAGIC_1 = 0x80;
constexpr std::uint8_t V64_MAGIC_2 = 0x40;
constexpr std::uint8_t V64_MAGIC_3 = 0x12;

constexpr std::uint8_t N64_MAGIC_0 = 0x40;
constexpr std::uint8_t N64_MAGIC_1 = 0x12;
constexpr std::uint8_t N64_MAGIC_2 = 0x37;
constexpr std::uint8_t N64_MAGIC_3 = 0x80;

} // namespace

Result<RomImage> RomReader::load(
    const std::filesystem::path& path
) {
    std::ifstream file(
        path,
        std::ios::binary
    );

    if (!file) {
        return Result<RomImage>::failure(
            Diagnostic{
                DiagnosticSeverity::Error,
                DiagnosticCode::IoError,
                "unable to open ROM file: " + path.string(),
                SourceLocation{
                    path.string(),
                    0,
                    0,
                },
            }
        );
    }

    file.seekg(
        0,
        std::ios::end
    );

    const std::streampos end = file.tellg();

    if (end < 0) {
        return Result<RomImage>::failure(
            Diagnostic{
                DiagnosticSeverity::Error,
                DiagnosticCode::IoError,
                "unable to determine ROM file size: " +
                    path.string(),
                SourceLocation{
                    path.string(),
                    0,
                    0,
                },
            }
        );
    }

    const std::size_t size =
        static_cast<std::size_t>(end);

    file.seekg(
        0,
        std::ios::beg
    );

    std::vector<std::uint8_t> data(size);

    if (size != 0) {
        file.read(
            reinterpret_cast<char*>(data.data()),
            static_cast<std::streamsize>(size)
        );

        if (!file) {
            return Result<RomImage>::failure(
                Diagnostic{
                    DiagnosticSeverity::Error,
                    DiagnosticCode::IoError,
                    "failed while reading ROM file: " +
                        path.string(),
                    SourceLocation{
                        path.string(),
                        0,
                        0,
                    },
                }
            );
        }
    }

    auto result = from_bytes(
        std::move(data)
    );

    if (!result) {
        return result;
    }

    return result;
}

Result<RomImage> RomReader::from_bytes(
    std::vector<std::uint8_t> data
) {
    if (data.size() < 4) {
        return Result<RomImage>::failure(
            Diagnostic{
                DiagnosticSeverity::Error,
                DiagnosticCode::InvalidRom,
                "ROM data is smaller than the four-byte N64 magic",
                {},
            }
        );
    }

    const RomByteOrder byte_order =
        detect_byte_order(data);

    switch (byte_order) {
    case RomByteOrder::BigEndian:
    case RomByteOrder::ByteSwapped:
    case RomByteOrder::LittleEndian:
        break;

    default:
        return Result<RomImage>::failure(
            Diagnostic{
                DiagnosticSeverity::Error,
                DiagnosticCode::UnsupportedFormat,
                "unsupported N64 ROM byte order",
                {},
            }
        );
    }

    normalize_byte_order(
        data,
        byte_order
    );

    return Result<RomImage>::success(
        RomImage(
            std::move(data),
            byte_order
        )
    );
}

RomByteOrder RomReader::detect_byte_order(
    const std::vector<std::uint8_t>& data
) {
    if (
        data[0] == Z64_MAGIC_0 &&
        data[1] == Z64_MAGIC_1 &&
        data[2] == Z64_MAGIC_2 &&
        data[3] == Z64_MAGIC_3
    ) {
        return RomByteOrder::BigEndian;
    }

    if (
        data[0] == V64_MAGIC_0 &&
        data[1] == V64_MAGIC_1 &&
        data[2] == V64_MAGIC_2 &&
        data[3] == V64_MAGIC_3
    ) {
        return RomByteOrder::ByteSwapped;
    }

    if (
        data[0] == N64_MAGIC_0 &&
        data[1] == N64_MAGIC_1 &&
        data[2] == N64_MAGIC_2 &&
        data[3] == N64_MAGIC_3
    ) {
        return RomByteOrder::LittleEndian;
    }

    return RomByteOrder::LittleEndian;
}

void RomReader::normalize_byte_order(
    std::vector<std::uint8_t>& data,
    RomByteOrder byte_order
) {
    if (byte_order == RomByteOrder::BigEndian) {
        return;
    }

    if (byte_order == RomByteOrder::ByteSwapped) {
        for (std::size_t i = 0; i + 1 < data.size(); i += 2) {
            std::swap(
                data[i],
                data[i + 1]
            );
        }

        return;
    }

    if (byte_order == RomByteOrder::LittleEndian) {
        for (std::size_t i = 0; i + 3 < data.size(); i += 4) {
            std::swap(
                data[i],
                data[i + 3]
            );

            std::swap(
                data[i + 1],
                data[i + 2]
            );
        }
    }
}

} // namespace n64decomp
