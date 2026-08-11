# Decompilation Pipeline

The long-term pipeline is:

1. Input
2. ROM normalization
3. ROM metadata extraction
4. Address-space construction
5. Segment classification
6. MIPS instruction decoding
7. Instruction semantics
8. Function discovery
9. Basic-block discovery
10. Control-flow graph
11. Call graph
12. Data-flow analysis
13. SSA/value analysis
14. Memory analysis
15. Type inference
16. Pointer analysis
17. Structure recovery
18. Expression recovery
19. Control-flow structuring
20. Symbol recovery
21. C++ AST generation
22. Source emission
23. Verification

Each stage should expose explicit data structures.

Stages should not depend on parsing human-readable assembly text when a
structured representation can be used instead.

Human-readable assembly output is a presentation/debugging format, not the
canonical internal representation.

## Long-term goal

The final output should resemble naturally written high-level C++ as closely
as static analysis allows.

Examples of desired recovery include:

- meaningful function names
- meaningful variable names
- typed parameters
- typed return values
- structs
- arrays
- pointers
- loops
- switch statements
- if/else structures
- meaningful constants
- recovered global objects
- semantically meaningful expressions

The framework must attach confidence information to heuristic discoveries
where certainty is impossible.
