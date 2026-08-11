#include "n64decomp/result.hpp"

#include <cassert>
#include <string>

using namespace n64decomp;

int main() {
    auto success = Result<int>::success(42);

    assert(success);
    assert(success.has_value());
    assert(!success.has_errors());
    assert(success.value() == 42);

    Diagnostic diagnostic{
        DiagnosticSeverity::Error,
        DiagnosticCode::InvalidInput,
        "test failure",
        SourceLocation{
            "input.bin",
            12,
            8,
        },
    };

    auto failure = Result<int>::failure(
        std::move(diagnostic)
    );

    assert(!failure);
    assert(!failure.has_value());
    assert(failure.has_errors());
    assert(failure.diagnostics().size() == 1);

    const auto& entry =
        failure.diagnostics().diagnostics().front();

    assert(entry.severity == DiagnosticSeverity::Error);
    assert(entry.code == DiagnosticCode::InvalidInput);
    assert(entry.message == "test failure");
    assert(entry.location.file == "input.bin");
    assert(entry.location.line == 12);
    assert(entry.location.column == 8);

    return 0;
}
