# n64decomp-framework

A generic C++20 reverse-engineering and decompilation framework for
MIPS-based Nintendo 64 software.

## Status

Early development.

Current version: 0.1.0

Current milestone: M001 — Foundation

This project does not currently decompile ROMs.

## Goal

The long-term goal is to build a static-analysis pipeline capable of
transforming MIPS machine code into progressively higher-level representations
and ultimately readable C++ source.

The intended architecture is:

ROM
 -> decoding
 -> instruction semantics
 -> function discovery
 -> CFG
 -> IR
 -> data flow
 -> SSA
 -> type inference
 -> memory analysis
 -> structure recovery
 -> expression recovery
 -> control-flow structuring
 -> semantic naming
 -> C++ generation

## Design philosophy

This is not intended to be a simple:

    assembly -> C

translator.

Reliable high-level recovery requires intermediate representations and
multiple analysis passes.

Unknown instructions and uncertain analysis results must remain visible rather
than being silently discarded.

## Building

Requirements:

- CMake 3.20 or newer
- C++20 compiler

Example:

    cmake -S . -B build
    cmake --build build

Run:

    ./build/n64decomp

Run tests:

    ctest --test-dir build --output-on-failure

## Repository structure

    include/     Public C++ interfaces
    src/         Core implementation
    tests/       Automated tests
    docs/        Architecture and project documentation

## ROM files

ROM images are intentionally excluded from the repository.

Use only ROMs you are legally entitled to analyze.

Local ROM files belong outside version control.

## Development

See:

- docs/ARCHITECTURE.md
- docs/ROADMAP.md
- docs/MILESTONES.md
- docs/DECISIONS.md
- docs/CURRENT_STATE.md
- docs/DECOMPILATION_PIPELINE.md

## License

See LICENSE.
