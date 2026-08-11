# Architecture Decisions

This document records decisions that affect the long-term architecture.

## D001 — C++20 core

Status: Accepted

The core framework uses C++20.

Reason:

- strong type system
- deterministic performance
- suitable for large static-analysis workloads
- RAII and ownership support
- standard library facilities
- good tooling availability

## D002 — Multi-stage representation

Status: Accepted

The framework will use multiple intermediate representations instead of
direct assembly-to-C++ translation.

Reason:

Direct translation cannot reliably recover:

- types
- variables
- structures
- control flow
- pointer semantics
- expressions
- function signatures

## D003 — Preserve unknown semantics

Status: Accepted

Unknown or unsupported machine instructions must remain represented.

They must never silently disappear from the analysis.

## D004 — Generic framework

Status: Accepted

The framework is designed as a generic MIPS/N64 reverse-engineering system.

It must not depend on the implementation details of one particular game.

## D005 — ROMs are external inputs

Status: Accepted

ROM images are not stored in the repository.

Local ROM files are ignored by Git.

The framework operates on user-provided, legally obtained binaries.

## D006 — Architecture gates

Status: Accepted

Architecture-critical changes require explicit review.

Routine implementation can be delegated to smaller models when the required
behavior is already specified and covered by tests.
