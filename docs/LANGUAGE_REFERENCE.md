# Wave Language Reference

Version 5.0.2

## Table of Contents

1. [Introduction](#introduction)
2. [Lexical Structure](#lexical-structure)
3. [Types](#types)
4. [Variables](#variables)
5. [Operators](#operators)
6. [Control Flow](#control-flow)
7. [Functions](#functions)
8. [Unified Field](#unified-field)
9. [Fate Scheduler](#fate-scheduler)
10. [Tile Memory](#tile-memory)
11. [I/O Operations](#io-operations)
12. [Platform Adaptation](#platform-adaptation)
13. [Standard Library](#standard-library)

---

## Introduction

Wave is a rule-driven programming language that compiles to native machine code. Unlike traditional languages, Wave uses the **Unified Field** theory to map high-level code to machine instructions through derived rules.

### Design Philosophy

- **No hardcoded behavior** - Everything is derived from rules
- **Adaptive optimization** - Fate observes and optimizes at runtime
- **Minimal universal drivers** - Platform adaptation through probing
- **Self-hosting** - The Wave compiler is written in Wave

---

## Lexical Structure

### Comments

```wave
# This is a single-line comment
```

### Identifiers

Identifiers start with a letter or underscore, followed by letters, digits, or underscores.

```wave
x
_private
myVariable
count123
```

### Literals

**Integers:**
```wave
42
-17
0xFF      # Hexadecimal
```

**Strings:**
```wave
"Hello, World!"
"Line 1\nLine 2"
"\x7f\x45\x4c\x46"    # Raw bytes
```

### Keywords

```
out emit byte fn when loop break keep
fate limit unified syscall return ->
```

---

## Types

Wave uses dynamic typing with automatic type inference.

| Type | Description | Example |
|------|-------------|---------|
| Integer | 64-bit signed | `42` |
| Float | 64-bit IEEE 754 | `3.14` |
| String | UTF-8 encoded | `"hello"` |
| Array | Dynamic array | `[1, 2, 3]` |
| Object | Key-value map | `{x: 10, y: 20}` |

---

## Variables

### Declaration and Assignment

```wave
x = 10              # Integer
name = "Wave"       # String
pi = 3.14159        # Float
```

### Scope

Variables are scoped to their containing block.

```wave
x = 10
when x > 5 {
    y = 20          # y is local to this block
}
# y is not accessible here
```

---

## Operators

### Arithmetic

| Operator | Description | Example |
|----------|-------------|---------|
| `+` | Addition | `a + b` |
| `-` | Subtraction | `a - b` |
| `*` | Multiplication | `a * b` |
| `/` | Division | `a / b` |

### Comparison

| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal | `a == b` |
| `!=` | Not equal | `a != b` |
| `>` | Greater than | `a > b` |
| `<` | Less than | `a < b` |
| `>=` | Greater or equal | `a >= b` |
| `<=` | Less or equal | `a <= b` |

### Precedence

From highest to lowest:
1. `*` `/`
2. `+` `-`
3. `>` `<` `>=` `<=`
4. `==` `!=`

---

## Control Flow

### Conditional (when)

```wave
when condition {
    # executed if condition is true (non-zero)
}
```

**Nested conditions:**
```wave
when x > 0 {
    when x < 10 {
        out "x is between 0 and 10\n"
    }
}
```

### Loop

```wave
loop {
    # infinite loop
    when done { break }
}
```

**Counter pattern:**
```wave
i = 0
loop {
    i = i + 1
    # do work
    when i >= 100 { break }
}
```

### Break

Exits the innermost loop.

```wave
loop {
    when condition { break }
}
```

---

## Functions

### Definition

```wave
fn name param1 param2 {
    # function body
}
```

### Return Value

Use `->` to return a value:

```wave
fn add a b {
    result = a + b
    -> result
}
```

**Early return:**
```wave
fn abs n {
    when n < 0 { -> 0 - n }
    -> n
}
```

### Calling Functions

```wave
result = add(10, 20)
greet()
```

### Recursion

```wave
fn factorial n {
    when n <= 1 { -> 1 }
    prev = n - 1
    sub = factorial(prev)
    -> n * sub
}
```

---

## Unified Field

The Unified Field is Wave's core rule-mapping system. It uses three parameters to control code generation:

### Parameters

| Parameter | Symbol | Range | Description |
|-----------|--------|-------|-------------|
| Information Density | `i` | 0.0-1.0 | Data compression preference |
| Entropy Gradient | `e` | 0.0-1.0 | Code stability/variability |
| Relation Strength | `r` | 0.0-1.0 | Caching aggressiveness |

### Setting Parameters

```wave
unified {
    i: 0.8
    e: 0.3
    r: 0.9
}
```

### Derived Rules

The Unified Field derives six rule categories:

1. **Gravitational** - Memory attraction (based on `i`)
2. **Tension** - Resource pressure (based on `r`)
3. **Entropy** - Code variability (based on `e`)
4. **Connection** - Data relationships (based on `r`)
5. **Memory** - Persistence patterns (based on `i`)
6. **Orbital** - Execution cycles (based on `e`)

---

## Fate Scheduler

Fate is Wave's adaptive optimization system that observes runtime behavior and optimizes accordingly.

### Modes

**Dynamic Mode:**
```wave
fate on
# Fate actively observes and optimizes
```

**Static Mode (Collapse):**
```wave
fate off
# Fate freezes current optimizations
```

### Threshold

Set the marginal gain threshold for collapse:

```wave
limit 100    # Collapse when gain < 1/100
```

### Collapse

When Fate detects diminishing returns, it "collapses" dynamic code to static:

1. Fate observes execution patterns
2. Calculates marginal gain
3. If gain < threshold, collapses to static
4. Learned patterns are preserved

---

## Tile Memory

Tile is Wave's four-pool memory management system.

### Pools

| Pool | Name | Purpose | Selection Criteria |
|------|------|---------|-------------------|
| 0 | BlackHole | Compressed data | High `i` |
| 1 | MeshBrain | Pattern data | High `r` |
| 2 | MultiNova | General purpose | Default |
| 3 | BaseForce | Fast cache | High `e` |

### Selection Algorithm

Pool selection is based on Unified Field parameters:

```
if i > e: select BlackHole (compression)
else: select BaseForce (speed)
```

---

## I/O Operations

### Output

**String output:**
```wave
out "Hello, World!\n"
```

**Raw bytes:**
```wave
emit "\x7f\x45\x4c\x46"    # ELF magic
```

**Single byte:**
```wave
byte(65)        # ASCII 'A'
putchar(10)     # Newline
```

### Input

```wave
ch = getchar()    # Read single character
```

### Exit

```wave
syscall.exit(0)    # Exit with code 0
```

---

## Platform Adaptation

Wave uses Fate to automatically detect and adapt to the platform.

### Probing

```wave
platform.probe    # Fate detects platform
compat.probe      # Fate discovers devices
bridge.read       # Read bridge environment
```

### Bridge Protocol

Standard memory addresses for device communication:

| Address | Name | Description |
|---------|------|-------------|
| 0x1000 | DISPLAY_FB | Framebuffer pointer |
| 0x1004 | DISPLAY_WIDTH | Display width |
| 0x1008 | DISPLAY_HEIGHT | Display height |
| 0x100C | DISPLAY_PITCH | Bytes per row |
| 0x1010 | DISPLAY_FORMAT | Pixel format |
| 0x1014 | DISPLAY_READY | Ready flag |
| 0x2000 | INPUT_BUFFER | Input queue |
| 0x2004 | INPUT_HEAD | Queue head |
| 0x2008 | INPUT_TAIL | Queue tail |
| 0x200C | INPUT_READY | Ready flag |
| 0x3000 | TIME_TICKS | Time counter |
| 0x3004 | TIME_FREQ | Timer frequency |

---

## Standard Library

### Core Rules

Located in `src/rules/`:

| File | Description |
|------|-------------|
| `unified.wave` | Unified Field implementation |
| `fate.wave` | Fate Scheduler |
| `tile.wave` | Tile Memory Manager |
| `codegen.wave` | Code generator |
| `compiler.wave` | Compiler logic |

### Graphics

```wave
use rules/graphics

shape.add_rect(x, y, w, h, color)
shape.add_circle(cx, cy, r, color)
shape.add_line(x1, y1, x2, y2, color)
render()
```

### GUI

```wave
use rules/gui

w = window.create("Title", 800, 600)
btn = component.button("btn1", 100, 50, 200, 40, "Click")
gui.render_all()
```

### Database

```wave
use rules/db

users = db("users")
users.put("key", value)
data = users.get("key")
users.del("key")
```

---

## Compiler Options

```bash
wave5 <input.wave> [-o output] [--raw]
```

| Option | Description |
|--------|-------------|
| `-o <file>` | Output file path |
| `--raw` | Generate raw binary (no ELF header) |

---

## Error Handling

Wave uses a fail-fast approach. Runtime errors cause immediate termination.

Future versions may support:
```wave
try {
    # risky operation
} catch {
    # error handling
}
```

---

## Best Practices

1. **Use Unified Field wisely** - Set parameters based on your use case
2. **Let Fate optimize** - Avoid premature optimization
3. **Use minimal drivers** - Let Fate probe and adapt
4. **Structure with functions** - Keep code modular
5. **Comment your rules** - Document Unified Field choices

---

## Version History

| Version | Date | Changes |
|---------|------|---------|
| 5.0.2 | 2026-01 | Minimal universal drivers, Fate adaptation |
| 5.0.1 | 2026-01 | C bootstrap compiler |
| 5.0.0 | 2026-01 | Initial release |

---

*Wave Language Reference - Version 5.0.2*
