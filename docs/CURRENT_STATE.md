# Current State

## Project

n64decomp-framework

## Current commit

001

## Current milestone

M001 — Foundation

## Status

Foundation initialized.

No ROM processing exists yet.

No MIPS decoding exists yet.

No decompilation functionality exists yet.

## Implemented

- CMake project
- C++20 configuration
- core include path
- executable entry point
- version header
- smoke test
- initial architecture documentation
- roadmap
- milestone policy
- architecture decision log

## Not implemented

- ROM loader
- endian detection
- N64 header parser
- address spaces
- segment mapping
- MIPS decoder
- instruction IR
- CFG
- function discovery
- data-flow analysis
- SSA
- type inference
- pointer analysis
- structure recovery
- C++ generation

## Next commit

002 — Establish project diagnostics and error handling.

## Next major subsystem

ROM subsystem.

## Architectural warning

Do not introduce direct assembly-to-C++ translation.

All future decompilation stages should operate through explicit
intermediate representations.
