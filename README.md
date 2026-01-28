# 🌊 Wave-C

**Alpha Test 1.0** | A rule-driven compiler

> *Binary releases coming soon.*

---

## What is Wave?

Wave compiles code through **derived rules**, not hardcoded behavior.

```
Source → Unified Field (i, e, r) → Derived Rules → Machine Code
```

Three parameters control everything:
- `i` - information density (compress ↔ expand)
- `e` - entropy gradient (stable ↔ variable)
- `r` - relation strength (cache ↔ recompute)

---

## Quick Start

```bash
# Build
gcc -o wavec src/wave5.c -O2 -lm

# Run
./wavec hello.wave -o hello
./hello
```

---

## Examples

**Hello World:**
```wave
out "Hello, Wave!\n"
syscall.exit(0)
```

**Variables & Math:**
```wave
x = 10
y = 20
sum = x + y
syscall.exit(0)
```

**Functions:**
```wave
fn add a b {
    -> a + b
}

result = add(10, 20)
syscall.exit(0)
```

**Loops:**
```wave
i = 0
loop {
    i = i + 1
    when i >= 10 { break }
}
syscall.exit(0)
```

**Unified Field:**
```wave
unified {
    i: 0.8
    e: 0.2
    r: 0.9
}
```

---

## How It Works

| Component | Purpose |
|-----------|---------|
| **Unified Field** | Three parameters (i, e, r) that derive all rules |
| **Derived Rules** | Gravitational, Tension, Entropy, Connection, Memory, Orbital |
| **Fate Scheduler** | Observes execution, collapses when gain < threshold |
| **Tile Memory** | Four pools: BlackHole, MeshBrain, MultiNova, BaseForce |

---

## License

MIT License

Copyright © 2026 Jouly Mars (ZHUOLI MA)  
Rogue Intelligence LNC.

---

[📖 Documentation](docs/LANGUAGE_REFERENCE.md) · [🌐 Website](https://joulyman.github.io/wave-c)
