# n64decomp Architecture

## Purpose

n64decomp is a generic reverse-engineering and decompilation framework
for MIPS-based Nintendo 64 software.

The project is designed to transform machine code into progressively
higher-level representations.

The intended pipeline is:

ROM
 -> ROM inspection
 -> segment mapping
 -> instruction decoding
 -> instruction representation
 -> function discovery
 -> control-flow graph
 -> data-flow analysis
 -> intermediate representation
 -> SSA / value analysis
 -> type inference
 -> memory and pointer analysis
 -> structure recovery
 -> expression recovery
 -> control-flow structuring
 -> semantic symbol recovery
 -> C++ representation
 -> generated high-level source

## Core architectural principle

The framework must not directly translate assembly into C++.

Instead, machine instructions must pass through intermediate representations
and analysis stages.

This allows later stages to reason about semantics rather than raw assembly
syntax.

## Important architectural boundaries

The following components are considered architecture-critical:

- CPU instruction semantics
- machine state representation
- intermediate representation
- control-flow graph
- data-flow representation
- SSA representation
- memory model
- type system
- pointer analysis
- structure recovery
- expression representation
- control-flow structuring
- symbol system
- C++ output representation

Changes to these components require explicit architectural review.

## Correctness principle

The framework must never silently discard an instruction or an unknown
semantic construct.

Unknown instructions must remain explicitly represented.

The preferred behavior is:

unknown instruction
 -> explicit IR node
 -> diagnostic
 -> preserved output

rather than:

unknown instruction
 -> ignored

## Source compatibility

The framework is not intended to reproduce proprietary source code.

Its purpose is to reconstruct program behavior from a legally obtained
binary through static analysis and generated representations.

## Language

The implementation language is C++20.

Python may later be used for auxiliary tooling, generators, or research
scripts, but the core decompilation engine is intended to be C++.
