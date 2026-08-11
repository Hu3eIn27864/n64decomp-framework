#pragma once

#include "n64decomp/diagnostics.hpp"

#include <cassert>
#include <optional>
#include <utility>

namespace n64decomp {

template <typename T>
class Result {
public:
    static Result success(T value) {
        Result result;
        result.value_ = std::move(value);
        return result;
    }

    static Result failure(Diagnostic diagnostic) {
        Result result;
        result.diagnostics_.add(
            diagnostic.severity,
            diagnostic.code,
            std::move(diagnostic.message),
            std::move(diagnostic.location)
        );
        return result;
    }

    static Result failure(DiagnosticSink diagnostics) {
        Result result;
        result.diagnostics_ = std::move(diagnostics);
        return result;
    }

    [[nodiscard]] bool has_value() const noexcept {
        return value_.has_value();
    }

    [[nodiscard]] explicit operator bool() const noexcept {
        return has_value();
    }

    [[nodiscard]] bool has_errors() const noexcept {
        return diagnostics_.has_errors();
    }

    [[nodiscard]] T& value() & {
        assert(value_.has_value());
        return *value_;
    }

    [[nodiscard]] const T& value() const& {
        assert(value_.has_value());
        return *value_;
    }

    [[nodiscard]] T&& value() && {
        assert(value_.has_value());
        return std::move(*value_);
    }

    [[nodiscard]] DiagnosticSink& diagnostics() noexcept {
        return diagnostics_;
    }

    [[nodiscard]] const DiagnosticSink&
    diagnostics() const noexcept {
        return diagnostics_;
    }

private:
    std::optional<T> value_;
    DiagnosticSink diagnostics_;
};

} // namespace n64decomp
