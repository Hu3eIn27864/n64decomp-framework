#include "n64decomp/diagnostics.hpp"

#include <utility>

namespace n64decomp {

void DiagnosticSink::add(
    DiagnosticSeverity severity,
    DiagnosticCode code,
    std::string message,
    SourceLocation location
) {
    diagnostics_.push_back(Diagnostic{
        severity,
        code,
        std::move(message),
        std::move(location),
    });
}

void DiagnosticSink::info(
    DiagnosticCode code,
    std::string message,
    SourceLocation location
) {
    add(
        DiagnosticSeverity::Info,
        code,
        std::move(message),
        std::move(location)
    );
}

void DiagnosticSink::warning(
    DiagnosticCode code,
    std::string message,
    SourceLocation location
) {
    add(
        DiagnosticSeverity::Warning,
        code,
        std::move(message),
        std::move(location)
    );
}

void DiagnosticSink::error(
    DiagnosticCode code,
    std::string message,
    SourceLocation location
) {
    add(
        DiagnosticSeverity::Error,
        code,
        std::move(message),
        std::move(location)
    );
}

bool DiagnosticSink::has_errors() const noexcept {
    for (const Diagnostic& diagnostic : diagnostics_) {
        if (diagnostic.severity == DiagnosticSeverity::Error) {
            return true;
        }
    }

    return false;
}

bool DiagnosticSink::empty() const noexcept {
    return diagnostics_.empty();
}

std::size_t DiagnosticSink::size() const noexcept {
    return diagnostics_.size();
}

const std::vector<Diagnostic>&
DiagnosticSink::diagnostics() const noexcept {
    return diagnostics_;
}

void DiagnosticSink::clear() noexcept {
    diagnostics_.clear();
}

std::string_view
to_string(DiagnosticSeverity severity) noexcept {
    switch (severity) {
    case DiagnosticSeverity::Info:
        return "info";

    case DiagnosticSeverity::Warning:
        return "warning";

    case DiagnosticSeverity::Error:
        return "error";
    }

    return "unknown";
}

std::string_view
to_string(DiagnosticCode code) noexcept {
    switch (code) {
    case DiagnosticCode::Unknown:
        return "unknown";

    case DiagnosticCode::InvalidArgument:
        return "invalid-argument";

    case DiagnosticCode::InvalidInput:
        return "invalid-input";

    case DiagnosticCode::IoError:
        return "io-error";

    case DiagnosticCode::InvalidRom:
        return "invalid-rom";

    case DiagnosticCode::UnsupportedFormat:
        return "unsupported-format";

    case DiagnosticCode::InvalidInstruction:
        return "invalid-instruction";

    case DiagnosticCode::InternalError:
        return "internal-error";
    }

    return "unknown";
}

} // namespace n64decomp
