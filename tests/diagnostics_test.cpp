#include "n64decomp/diagnostics.hpp"

#include <cassert>
#include <string>

using namespace n64decomp;

int main() {
    DiagnosticSink diagnostics;

    assert(diagnostics.empty());
    assert(!diagnostics.has_errors());
    assert(diagnostics.size() == 0);

    diagnostics.info(
        DiagnosticCode::Unknown,
        "framework initialized"
    );

    assert(!diagnostics.has_errors());
    assert(diagnostics.size() == 1);

    diagnostics.warning(
        DiagnosticCode::UnsupportedFormat,
        "format is not recognized"
    );

    assert(!diagnostics.has_errors());
    assert(diagnostics.size() == 2);

    diagnostics.error(
        DiagnosticCode::InvalidRom,
        "ROM header is invalid",
        SourceLocation{
            "test.z64",
            1,
            4,
        }
    );

    assert(diagnostics.has_errors());
    assert(diagnostics.size() == 3);

    const auto& entries = diagnostics.diagnostics();

    assert(entries[0].severity == DiagnosticSeverity::Info);
    assert(entries[1].severity == DiagnosticSeverity::Warning);
    assert(entries[2].severity == DiagnosticSeverity::Error);

    assert(entries[2].code == DiagnosticCode::InvalidRom);
    assert(entries[2].location.file == "test.z64");
    assert(entries[2].location.line == 1);
    assert(entries[2].location.column == 4);

    assert(to_string(DiagnosticSeverity::Info) == "info");
    assert(to_string(DiagnosticSeverity::Warning) == "warning");
    assert(to_string(DiagnosticSeverity::Error) == "error");

    assert(to_string(DiagnosticCode::InvalidRom) == "invalid-rom");

    diagnostics.clear();

    assert(diagnostics.empty());
    assert(!diagnostics.has_errors());

    return 0;
}
