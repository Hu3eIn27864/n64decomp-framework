# Roadmap

The project aims to recover progressively higher-level semantics from Nintendo 64 MIPS code through explicit intermediate representations. It is a research-scale static-analysis project, not a simple assembly-to-C++ translator.

Estimates assume one experienced developer at 10–15 focused hours per week. They are planning ranges, not delivery promises.

| Phase | Scope | Estimate | Exit gate |
|---|---|---:|---|
| M001 | Foundation, diagnostics, configuration, tests | 2–4 weeks | Clean build and test baseline |
| M002 | ROM loading, endian normalization, headers and address spaces | 3–5 weeks | Synthetic ROM fixtures parse correctly |
| M003 | MIPS III / R4300 instruction model and semantics | 6–10 weeks | Instruction tests cover documented supported set |
| M004 | Function discovery and control-flow targets | 6–10 weeks | Repeatable function candidates with confidence |
| M005 | Basic blocks, CFG and semantic IR | 8–12 weeks | CFG invariants and IR tests pass |
| M006 | Data flow, liveness, reaching definitions and SSA | 3–6 months | Data-flow results validated on hand-checked functions |
| M007 | Types, pointers, stack/global memory analysis | 3–6 months | Conservative type and memory facts with uncertainty |
| M008 | Structure and array recovery | 2–4 months | Recoveries carry evidence and confidence |
| M009 | Expression recovery and simplification | 2–4 months | Stable expression trees and regression tests |
| M010 | Control-flow structuring | 2–4 months | Structured output preserves CFG semantics on test corpus |
| M011 | Semantic naming and API recognition | 2–4 months | Names are evidence-backed and confidence-scored |
| M012 | C++ generation and verification | 3–6 months | Generated code compiles for selected supported cases |
| M013 | Regression corpus and differential validation | Ongoing | Reproducible reports for each supported target |

## Recommended implementation order

1. Finish M001 before introducing ROM-specific abstractions.
2. Complete M002 and M003 independently; keep instruction semantics table-driven.
3. Build function discovery and CFG before any source generation.
4. Introduce IR validation and golden tests before data-flow work.
5. Treat SSA, pointer analysis and structure recovery as research-heavy phases.
6. Generate C++ only after the analysis pipeline has enough semantic evidence.

## Scope controls

- Start with one documented N64 binary format and a limited R4300 instruction subset.
- Unknown instructions and uncertain code/data boundaries must remain explicit.
- Do not claim general C++ decompilation from successful disassembly or function discovery.
- Keep ROM images out of the repository; use synthetic fixtures and legally distributable homebrew tests.
- Re-estimate each phase after its first working vertical slice.
