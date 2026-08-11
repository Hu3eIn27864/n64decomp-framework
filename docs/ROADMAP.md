# Roadmap

## Phase 1 — Foundation

Commits 001–030

- Project structure
- CMake
- testing
- diagnostics
- configuration
- common utilities
- documentation infrastructure

## Phase 2 — ROM subsystem

Commits 031–060

- ROM loading
- endian detection
- Z64/V64/N64 normalization
- ROM header
- CRC metadata
- address spaces
- ROM/RAM mappings
- segment representation

## Phase 3 — MIPS decoding

Commits 061–100

- MIPS III instruction model
- R4300-oriented instruction semantics
- integer instructions
- branches
- jumps
- loads/stores
- HI/LO
- COP0
- COP1
- FPU
- special instructions

## Phase 4 — Function discovery

Commits 101–150

- entry-point analysis
- call discovery
- branch targets
- function boundaries
- jump tables
- indirect calls
- function metadata

## Phase 5 — CFG and IR

Commits 151–250

- basic blocks
- control-flow graph
- instruction IR
- semantic operations
- delay-slot modeling
- call graph

## Phase 6 — Data-flow and SSA

Commits 251–350

- use/def analysis
- register liveness
- reaching definitions
- SSA
- value propagation
- constant propagation
- copy propagation

## Phase 7 — Types and memory

Commits 351–500

- integer types
- pointer types
- floating-point types
- arrays
- memory regions
- aliases
- pointer arithmetic
- stack variables
- global variables

## Phase 8 — Structure recovery

Commits 501–650

- struct candidates
- field inference
- array recovery
- nested structures
- object-like patterns
- memory access grouping

## Phase 9 — Expression recovery

Commits 651–750

- expression trees
- arithmetic simplification
- casts
- comparisons
- pointer expressions
- function arguments
- return values

## Phase 10 — Control-flow structuring

Commits 751–900

- if/else
- loops
- switch
- break
- continue
- early returns
- irreducible-flow handling

## Phase 11 — Semantic naming

Commits 901–1000

- function names
- variable names
- field names
- type names
- constants
- API recognition
- confidence scoring

## Phase 12 — C++ backend

Commits 1001–1100

- C++ AST
- declarations
- structs/classes
- functions
- expressions
- control flow
- source formatting

## Phase 13 — Verification

Commits 1101+

- generated-source validation
- semantic equivalence checks
- regression corpus
- instruction coverage
- differential testing
- large-scale ROM analysis

The exact commit ranges are provisional and may change as the implementation
reveals the actual complexity of each subsystem.
