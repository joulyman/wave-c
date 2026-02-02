# 🌊 Wave LBD Language Handbook

**Wave** — Law-Based Dynamic Language (LBD)

Version: 5.0  
Paradigm: Law-Based Dynamic (LBD)  
Self-Hosting: Yes

---

## Table of Contents

1. [Introduction](#introduction)
2. [Dual Paradigm Innovation](#dual-paradigm-innovation)
3. [Unified Field](#unified-field)
4. [Tile Memory Manager](#tile-memory-manager)
5. [Fate Engine](#fate-engine)
6. [Collapse Staticization](#collapse-staticization)
7. [Syntax Reference](#syntax-reference)
8. [Pipeline System](#pipeline-system)
9. [Graphics](#graphics)
10. [Style System](#style-system)
11. [Universal Bridge](#universal-bridge)
12. [Examples](#examples)

---

## Introduction

### What is Wave LBD?

Wave is a **Law-Based Dynamic Language** — a revolutionary programming paradigm that combines two fundamental innovations:

| Innovation | Name | Core |
|------------|------|------|
| **#1** | Law-Based | Physical-mathematical rules map to computer behavior |
| **#2** | Dynamic | Code automatically optimizes itself at runtime |

```
Traditional:  Code → Compiler → Assembly → Binary (fixed)
Wave LBD:     Intent → Rules → Fate → Binary (evolving)
```

### Naming

| Letter | Full | Meaning |
|--------|------|---------|
| **L** | Law-Based | Physical laws drive computation |
| **B** | Binary-Direct | No intermediate layers |
| **D** | Dynamic | Runtime self-optimization |

---

## Dual Paradigm Innovation

### Innovation #1: Law-Based (法则基)

Instead of abstracting or exposing the machine, Wave **maps** physical laws into composable rules.

```
Traditional Programming:
    Human → Instructions → Machine executes
    (Tell machine HOW to do)

Wave Law-Based:
    Human → Intent → Physical law composition → Behavior emergence
    (Describe WHAT you want, laws compose automatically)
```

```wave
# You express intent
out "hello"

# Wave maps to rules
tension (accumulate output) + connection (connect stdout)

# Rules compose to syscall
write(1, "hello", 5)
```

### Innovation #2: Dynamic (动态)

**No other language does this: code optimizes itself at runtime.**

```
Traditional Compilation:
    Source → Compile optimization → Fixed binary → Execute
    (Compile once, fixed forever)

Wave Dynamic:
    Source → Binary → Execute → Fate monitors → Auto-optimize → Collapse
    (Continuous evolution, automatic optimization)
```

```wave
fate on              # Enable dynamic mode

loop {
    compute()        # Fate monitors
}
# Fate detects: compute_heavy
# Fate adjusts: entropy_gradient += 0.1
# Marginal returns drop → Collapse triggers
# Code staticizes to optimal path
```

### Comparison Table

| Aspect | Traditional | Wave LBD |
|--------|-------------|----------|
| Computation basis | Turing instructions | Physical-mathematical laws |
| Optimization timing | Compile-time | **Runtime** |
| Optimization decision | Compiler rules | **Fate automatic** |
| Code evolution | Impossible | **Collapse staticization** |
| Hardware adaptation | Manual config | **Auto-detect** |
| Task adaptation | Impossible | **Auto-analyze** |

---

## Unified Field (统一场) — Rule Mapping Layer

### Concept

Unified Field is the **rule mapping layer** — maps computer behavior to physical-mathematical rules:

```wave
# Three core parameters
unified {
    information_density: 1.0    # Information density
    entropy_gradient: 0.0       # Entropy gradient
    relation_strength: 1.0      # Relation strength
}
```

### Derived Rules

Rules derived from three parameters, describing various computer behaviors:

| Rule | Mapped Computer Behavior |
|------|--------------------------|
| gravitational | Cache locality, memory aggregation |
| tension | Memory pressure, CPU load |
| entropy | Memory fragmentation, data randomness |
| connection | Pointer relationships, data structures |
| memory | Cache persistence, state durability |
| orbital | Task scheduling, animation loops |

```wave
# Gravitational rule — describes data aggregation
fn derive.gravitational {
    -> { strength: unified.information_density }
}

# Tension rule — describes resource pressure
fn derive.tension {
    -> { base: unified.relation_strength }
}

# Entropy rule — describes disorder
fn derive.entropy {
    -> { growth: unified.entropy_gradient }
}

# Connection rule — describes relationships
fn derive.connection {
    -> { strength: unified.relation_strength }
}
```

---

## Tile Memory Manager (TileQuattro) — Memory Layer

### Concept

Tile is the **memory management layer** — actual memory allocation:

```wave
# Quad memory pools
pool BlackHole { purpose: "compression" }   # Compressed storage
pool MeshBrain { purpose: "pattern" }       # Pattern processing
pool MultiNova { purpose: "parallel" }      # Parallel data
pool BaseForce { purpose: "fragment" }      # Fast fragments
```

### Allocation

Tile selects optimal pool based on Unified Field parameters:

```wave
fn tile.alloc size {
    when unified.information_density > 0.8 { -> BlackHole }
    when unified.relation_strength > 0.8 { -> MeshBrain }
    when unified.entropy_gradient > 0.5 { -> BaseForce }
    -> MultiNova
}
```

### Architecture Relationship

```
Unified Field (统一场)     ← Rule mapping layer
       ↓ parameters
Fate Scheduler            ← Resource scheduling
       ↓ calls
Tile Memory Manager       ← Actual allocation
```

---

## Fate Engine — Dynamic/Static Dual Mode

### On-Demand Scheduling

Fate allocates resources only when needed and monitors execution:

```wave
fn heavy_computation {
    # Fate monitors usage
    # Adjusts unified field parameters
    # Collapse intervenes if diminishing returns
}
heavy_computation()
```

### Dual Mode

```wave
# Dynamic mode (default) — Fate auto-optimizes
fate on
# Code optimizes based on task and hardware
# Triggers Collapse staticization when stable

# Static mode — direct execution
fate off
# Code executes directly, no optimization
```

| Syntax | Mode | Description |
|--------|------|-------------|
| `fate on` | Dynamic | Enable auto-optimization |
| `fate off` | Static | Direct execution, no optimization |

### Three-Layer Adaptation

```
┌─────────────────────────────────────────────────────────────┐
│  1. Task Adaptation — Fate observes code behavior           │
│     compute_heavy → adjust entropy_gradient                 │
│     memory_heavy → adjust information_density               │
│     pattern_rich → adjust relation_strength                 │
└─────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  2. Hardware Adaptation — Fate detects hardware             │
│     GPU VRAM → adjust rendering strategy                    │
│     CPU cores → adjust parallelism                          │
│     Memory size → adjust caching strategy                   │
└─────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  3. Marginal Returns — Collapse staticization               │
│     Monitor gains → Gains diminish → Trigger Collapse       │
│     Dynamic code → Staticize to optimal path                │
└─────────────────────────────────────────────────────────────┘
```

### Resource Limiting

```wave
# Limit to 80% resource usage
limit 80

# Fate respects this during execution
```

---

## Collapse Staticization — Dynamic → Static

### Marginal Returns

Collapse monitors the "marginal return" of each operation:

```
Gain(n) = Result(n) - Result(n-1)
When Gain(n) < threshold → Trigger Collapse
```

### How It Works

```wave
fate on

loop {
    compute()
}

# Fate monitors:
#   Iteration 1: gain = 100
#   Iteration 2: gain = 80
#   Iteration 3: gain = 50
#   Iteration 4: gain = 10
#   Iteration 5: gain = 2 ← Below threshold!
#
# Collapse triggers:
#   Staticize loop to optimal path
#   Switch to static mode
```

### Automatic Application

```wave
# Collapse automatically optimizes loops
loop {
    # If gains diminish, Collapse may break early
    process()
}
```

---

## Syntax Reference

### Output

```wave
out "Text with newline"
emit "Raw bytes without newline"
```

### Variables

```wave
x = 42
name = 100
result = x + 10
```

### Functions

```wave
# Definition
fn function_name {
    out "Inside function"
}

# Call
function_name()
```

### Conditionals

```wave
when condition {
    out "Condition is true"
}

# Conditions: x > 0, x < 10, x == 5, x != 0
```

### Loops

```wave
loop {
    out "Running..."
    break
}
```

### Pipeline

```wave
# Data flows left to right
input -> process -> output

# Examples
data -> filter -> transform -> store
source -> compress -> encrypt -> send
```

### Fate Control

```wave
# Enable dynamic optimization
fate on

# Switch to static mode
fate off
```

### keep Syntax

`keep` maintains program structure:

```wave
gui tile
window "App" 800 600

# Define structure
style btn { fill: 0x3498db }
apply btn
component.button ok 100 100 120 40 "OK"

# Bind events
on.click ok handle_ok

# Render
draw.render

# Keep structure until close
keep
```

---

## Pipeline System

### Syntax

```wave
a -> b -> c -> d
```

### Semantics

Each `->` represents data transformation:

```wave
# Example: data processing pipeline
raw_data -> validate -> transform -> compress -> output
```

### Pipeline with Fate

Fate manages the pipeline execution:
- Parallel stages when possible
- Memory pooling between stages
- Error propagation

---

## Graphics

### Vector Primitives

```wave
# Line: x1 y1 x2 y2 color
draw.line 0 0 100 100 0xFF0000

# Rectangle: x y width height color
draw.rect 10 10 100 50 0x00FF00

# Circle: x y radius color
draw.circle 200 200 50 0x0000FF
```

### Rendering

```wave
# Render all shapes
draw.render

# Save to file
draw.save "output.ppm"
```

---

## Style System

### CSS-like Syntax

```wave
style name {
    property: value
}
```

### Available Properties

| Property | Description | Example |
|----------|-------------|---------|
| `fill` | Fill color | `0x3498db` |
| `stroke` | Border color | `0x2980b9` |
| `stroke_width` | Border width | `2` |
| `radius` | Corner radius | `8` |
| `opacity` | Transparency (0-100) | `80` |
| `font_size` | Text size | `24` |
| `padding` | Inner spacing | `10` |
| `margin` | Outer spacing | `5` |
| `align` | Text alignment | `left/center/right` |

### Using Styles

```wave
# Define
style button {
    fill: 0x3498db
    stroke: 0x2980b9
    radius: 8
}

# Apply
apply button

# Draw with applied style
box 100 150 120 40
text 160 175 "Click"
```

---

## Universal Bridge

### Memory Protocol

Wave uses a **Universal Bridge** — platform-independent memory protocol:

```
Standard Memory Layout
═══════════════════════════════════════
Address       Content
───────────────────────────────────────
0x1000        Framebuffer pointer
0x1004        Width
0x1008        Height
0x100C        Pitch (bytes per row)
0x1010        Pixel format
0x1014        Ready flag (0/1)
───────────────────────────────────────
```

### Platform Independence

Wave programs don't know what platform they run on. They only:
1. Read standard addresses
2. Write to framebuffer
3. Read input events

External loaders (or Wave itself on bare-metal) fill in the addresses.

---

## Platform Kernel

### Cross-Platform Minimal Kernel

Wave includes a **Platform Kernel** — minimal cross-platform output system:

```
src/platform/
├── kernel.wave    # Entry point, auto-detect
├── linux.wave     # ELF output
├── macos.wave     # Mach-O output
└── windows.wave   # PE output
```

### How It Works

```
Wave Code
    ↓
env.init()      → Detect platform
    ↓
env.output()    → Output appropriate format
    ↓
ELF / PE / Mach-O / WAVE (raw)
```

### Usage

```wave
use platform/kernel
use platform/linux

env.init()
env.output(code)
```

### Fate Integration

Platform detection is **Fate-driven**:
- Known platforms: Load library directly
- Unknown platforms: Fate probes and learns
- No hardcoded "if Linux then ELF" rules

---

## Examples

### Hello World

```wave
out "Hello, World!"
syscall.exit(0)
```

### Dynamic Optimization

```wave
fate on              # Enable dynamic

x = 0
loop {
    x = x + 1
    when x > 100 { break }
}
# Fate monitors and may staticize

fate off             # Switch to static
out "Done"
syscall.exit(0)
```

### Styled Graphics

```wave
style header {
    fill: 0x2c3e50
    font_size: 24
}

style card {
    fill: 0xecf0f1
    stroke: 0xbdc3c7
    radius: 12
}

apply header
text 400 30 "Wave LBD Demo"

apply card
box 50 80 300 200

draw.render
draw.save "demo.ppm"

syscall.exit(0)
```

---

## File Structure

```
wave/
├── bin/
│   ├── wave5              # Main compiler
│   ├── rule_*             # Rule layer binaries
│   └── example_*          # Example binaries
├── src/
│   ├── wave5.wave         # Compiler source
│   ├── rules/             # Unified Field rules (11 files)
│   │   ├── unified.wave   # Core unified field
│   │   ├── core.wave      # Derived rules
│   │   ├── fate.wave      # Fate + Collapse
│   │   ├── tile.wave      # Memory manager
│   │   ├── compiler.wave  # Compilation
│   │   ├── codegen.wave   # Code generation
│   │   ├── intent.wave    # Intent mapping
│   │   ├── graphics.wave  # Graphics
│   │   ├── style.wave     # Styling
│   │   ├── gui.wave       # GUI
│   │   └── event.wave     # Events + keep
│   └── drivers/           # Universal bridge
│       ├── bridge.wave    # Memory protocol
│       ├── fate_adapt.wave# Free adaptation
│       └── bare_init.wave # Bare-metal init
├── examples/              # Example programs
├── output/                # Rendered output
└── docs/
    └── handbook.md        # This file
```

---

*Wave LBD — Law-Based Dynamic Language*  
*Dual Paradigm Innovation: Law-Based + Dynamic*  
*Self-Hosting • Pure Binary • Self-Optimizing*
