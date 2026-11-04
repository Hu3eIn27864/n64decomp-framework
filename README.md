# n64decomp-framework

A generic C++20 static-analysis and decompilation framework for MIPS-based Nintendo 64 software.

## Status

**Early foundation stage.** The repository currently provides project scaffolding and documentation. It does not yet load ROMs, decode MIPS instructions or decompile programs.

The long-term objective is to recover higher-level program structure through a sequence of explicit analysis passes and intermediate representations. Generated C++ is a research goal, not a current capability.

## Intended pipeline

```text
ROM loading and address mapping
  -> MIPS decoding and instruction semantics
  -> function discovery
  -> basic blocks and control-flow graph
  -> intermediate representation
  -> data-flow analysis and SSA
  -> type and memory analysis
  -> structure and expression recovery
  -> control-flow structuring
  -> C++ generation and verification
```

Unknown instructions, uncertain code/data boundaries and low-confidence inferences must remain visible in analysis output.

## Build

Requirements:
- CMake 3.20+
- C++20 compiler
- CTest (provided through CMake)

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Documentation

- [Architecture](docs/ARCHITECTURE.md)
- [Roadmap and time estimates](docs/ROADMAP.md)
- [Milestones](docs/MILESTONES.md)
- [Current state](docs/CURRENT_STATE.md)
- [Decompilation pipeline](docs/DECOMPILATION_PIPELINE.md)
- [Architecture decisions](docs/DECISIONS.md)

## Planning assumptions

The roadmap estimates roughly 10–15 focused development hours per week for one experienced developer. The full analysis pipeline is a multi-year research effort; early milestones should be re-estimated after each working vertical slice.

## ROM handling

ROM images are intentionally excluded from version control. Use only ROMs you are legally entitled to analyze. Keep local inputs outside the repository and use synthetic fixtures or legally redistributable homebrew tests for CI.
