# 🌊 Wave-C

**Alpha Test 1.0**

A rule-driven compiler that maps intentions to machine code through derived rules.

---

## What is Wave?

Wave is not a traditional compiler. Instead of parsing → AST → IR → codegen, Wave uses a **three-parameter field** to derive all compilation rules at compile-time:

```
Source Code → Unified Field (i, e, r) → Derived Rules → Machine Code
```

The field parameters control HOW code is generated:
- `i` (information density) - compression vs expansion
- `e` (entropy gradient) - stability vs variability  
- `r` (relation strength) - caching vs recomputation

**Everything else is derived.** No hardcoded behavior.

---

## Quick Example

```wave
# Hello World
out "Hello, Wave!\n"
syscall.exit(0)
```

Compile and run:
```bash
./bin/wavec hello.wave -o hello
./hello
```

---

## More Examples

### Variables and Math

```wave
x = 10
y = 20
sum = x + y
product = x * y

out "Math works!\n"
syscall.exit(0)
```

### Conditions

```wave
temperature = 25

when temperature > 30 {
    out "Hot\n"
}

when temperature <= 30 {
    out "Nice\n"
}

syscall.exit(0)
```

### Loops

```wave
i = 0
loop {
    i = i + 1
    byte(48 + i)    # Print digit
    byte(32)        # Space
    when i >= 9 { break }
}
out "\n"
syscall.exit(0)
```

Output: `1 2 3 4 5 6 7 8 9`

### Functions

```wave
fn add a b {
    result = a + b
    -> result
}

fn factorial n {
    when n <= 1 { -> 1 }
    prev = n - 1
    sub = factorial(prev)
    -> n * sub
}

sum = add(10, 20)      # 30
fact = factorial(5)    # 120

out "Functions work!\n"
syscall.exit(0)
```

### Unified Field Configuration

```wave
unified {
    i: 0.8    # High information density
    e: 0.2    # Low entropy (stable)
    r: 0.9    # Strong relations (aggressive caching)
}

# Code generation is now biased toward compression
out "Optimized!\n"
syscall.exit(0)
```

---

## How It Works

### 1. Unified Field

Three parameters define a "field" that determines all compilation behavior:

| Parameter | Symbol | Effect |
|-----------|--------|--------|
| Information Density | `i` | High = compress, Low = expand |
| Entropy Gradient | `e` | High = variable, Low = stable |
| Relation Strength | `r` | High = cache, Low = recompute |

### 2. Derived Rules

From these three parameters, six rule categories are derived:

- **Gravitational** - Memory attraction (where data goes)
- **Tension** - Resource pressure (when to release)
- **Entropy** - Code variability (optimization paths)
- **Connection** - Data relationships (caching decisions)
- **Memory** - Persistence patterns (what to remember)
- **Orbital** - Execution cycles (loop behavior)

### 3. Fate Scheduler

Fate observes execution and adjusts the field:

```wave
fate on     # Dynamic mode - Fate adjusts field
fate off    # Collapse mode - freeze current configuration
```

When marginal optimization gain falls below threshold, Fate "collapses" to static code.

### 4. Tile Memory

Four memory pools selected by field parameters:

| Pool | Name | Selected When |
|------|------|---------------|
| 0 | BlackHole | High `i` (compression) |
| 1 | MeshBrain | High `r` (patterns) |
| 2 | MultiNova | Default |
| 3 | BaseForce | High `e` (speed) |

---

## Build

```bash
# From source
gcc -o bin/wavec src/wave5.c -O2 -lm

# Test
./bin/wavec examples/hello.wave -o /tmp/hello
/tmp/hello
```

---

## Syntax Reference

### Keywords

| Keyword | Description |
|---------|-------------|
| `out` | Output string |
| `byte` | Output single byte |
| `fn` | Define function |
| `->` | Return value |
| `when` | Conditional |
| `loop` | Infinite loop |
| `break` | Exit loop |
| `fate` | Control scheduler |
| `unified` | Set field parameters |
| `syscall.exit` | Exit program |

### Operators

| Op | Description |
|----|-------------|
| `+` `-` `*` `/` | Arithmetic |
| `==` `!=` | Equality |
| `>` `<` `>=` `<=` | Comparison |

---

## License

MIT License

Copyright (c) 2026 Jouly Mars (ZHUOLI MA)  
Rogue Intelligence LNC.

---

## Status

**Alpha Test 1.0** - Core compiler working. All basic features implemented.

- [x] Variables and arithmetic
- [x] Conditions (when)
- [x] Loops (loop/break)
- [x] Functions with return
- [x] Unified Field configuration
- [x] Fate scheduler
- [x] Tile memory pools
- [x] x86-64 ELF output

---

*Wave-C: Let the rules flow* 🌊
