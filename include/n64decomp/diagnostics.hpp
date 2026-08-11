#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace n64decomp {

enum class DiagnosticSeverity {
    Info,
    Warning,
    Error,
};

enum class DiagnosticCode {
    Unknown,
    InvalidArgument,
    InvalidInput,
    IoError,
    InvalidRom,
    UnsupportedFormat,
    InvalidInstruction,
    InternalError,
};

struct SourceLocation {
    std::string file;
    std::size_t line = 0;
    std::size_t column = 0;
};

struct Diagnostic {
    DiagnosticSeverity severity = DiagnosticSeverity::Error;
    DiagnosticCode code = DiagnosticCode::Unknown;
    std::string message;
    SourceLocation location;
};

class DiagnosticSink {
public:
    void add(
        DiagnosticSeverity severity,
        DiagnosticCode code,
        std::string message,
        SourceLocation location = {}
    );

    void info(
        DiagnosticCode code,
        std::string message,
        SourceLocation location = {}
    );

    void warning(
        DiagnosticCode code,
        std::string message,
        SourceLocation location = {}
    );

    void error(
        DiagnosticCode code,
        std::string message,
        SourceLocation location = {}
    );

    [[nodiscard]] bool has_errors() const noexcept;

    [[nodiscard]] bool empty() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;

    [[nodiscard]] const std::vector<Diagnostic>& diagnostics() const noexcept;

    void clear() noexcept;

private:
    std::vector<Diagnostic> diagnostics_;
};

[[nodiscard]] std::string_view
to_string(DiagnosticSeverity severity) noexcept;

[[nodiscard]] std::string_view
to_string(DiagnosticCode code) noexcept;

} // namespace n64decomp
