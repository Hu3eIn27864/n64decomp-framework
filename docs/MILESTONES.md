# Milestones

The project uses milestone gates to separate routine implementation from
architecture-critical work.

Legend:

- GREEN: suitable for routine implementation
- YELLOW: implementation should follow an explicit specification
- RED: architecture-critical; requires strong-model review

## M001 — Foundation

Commits 001–030

Status: RED at architectural changes.

## M002 — ROM subsystem

Commits 031–060

Status: RED for address-space architecture.

## M003 — MIPS decoder

Commits 061–100

Status: RED for instruction semantics.

## M004 — Function discovery

Commits 101–150

Status: RED.

## M005 — CFG and IR

Commits 151–250

Status: RED.

## M006 — Data-flow and SSA

Commits 251–350

Status: RED.

## M007 — Type and memory system

Commits 351–500

Status: RED.

## M008 — Structure recovery

Commits 501–650

Status: RED.

## M009 — Expression recovery

Commits 651–750

Status: RED.

## M010 — Control-flow structuring

Commits 751–900

Status: RED.

## M011 — Semantic naming

Commits 901–1000

Status: RED.

## M012 — C++ backend

Commits 1001–1100

Status: RED.

## Model workflow

Smaller models may implement clearly specified tasks inside a milestone.

They must not silently redesign architecture-critical components.

If an implementation discovers an architectural deficiency, it should report
the problem instead of changing the architecture without review.

The strongest available model should review RED milestone boundaries and
architecture changes.
