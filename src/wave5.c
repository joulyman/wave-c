/*
 * Wave-C Alpha Test 1.0 - Rule-Driven Compiler
 * 
 * Features:
 * - Unified Field - Three-parameter rule mapping (i, e, r)
 * - Derived Rules (gravitational, tension, entropy, connection, memory, orbital)
 * - Tile Memory Manager - Four-pool memory system
 * - Fate Scheduler - Dynamic/static optimization
 * - Full syntax support
 * - Platform adaptation (Linux/macOS/Windows)
 * 
 * Build: gcc -o wave5 wave5.c -O2 -lm
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>

#define VERSION "1.0-alpha"
#define MAX_CODE (4 * 1024 * 1024)
#define MAX_DATA (1024 * 1024)
#define MAX_VARS 4096
#define MAX_FUNCS 2048
#define MAX_LABELS 8192
#define MAX_IDENT 256
#define MAX_POOLS 16
#define MAX_ADAPTERS 32

// ═══════════════════════════════════════════════════════════════
// Unified Field - Three-parameter rule mapping layer
// ═══════════════════════════════════════════════════════════════

typedef struct {
    double i;  // information_density [0,1]
    double e;  // entropy_gradient [0,1]
    double r;  // relation_strength [0,1]
} UnifiedField;

// Derived rules
typedef struct {
    double strength;
    double inverse_square;
    double threshold;
} GravitationalRule;

typedef struct {
    double base;
    double accumulation;
    double release;
} TensionRule;

typedef struct {
    double initial;
    double growth;
    double critical;
} EntropyRule;

typedef struct {
    double strength;
    double plasticity;
    double decay;
} ConnectionRule;

typedef struct {
    double persistence;
    double recall;
    double decay;
} MemoryRule;

typedef struct {
    double eccentricity;
    double period;
    double stability;
} OrbitalRule;

void unified_init(UnifiedField* uf) {
    uf->i = 0.5;
    uf->e = 0.5;
    uf->r = 0.5;
}

void unified_set(UnifiedField* uf, double i, double e, double r) {
    uf->i = fmax(0.0, fmin(1.0, i));
    uf->e = fmax(0.0, fmin(1.0, e));
    uf->r = fmax(0.0, fmin(1.0, r));
}

void unified_adjust(UnifiedField* uf, double di, double de, double dr) {
    unified_set(uf, uf->i + di, uf->e + de, uf->r + dr);
}

// Derived rule calculations
GravitationalRule derive_gravitational(UnifiedField* uf) {
    return (GravitationalRule){
        .strength = uf->i,
        .inverse_square = uf->e * 2.0 + 1.0,
        .threshold = uf->r * 0.1
    };
}

TensionRule derive_tension(UnifiedField* uf) {
    return (TensionRule){
        .base = uf->r,
        .accumulation = uf->e,
        .release = uf->i * 0.8
    };
}

EntropyRule derive_entropy(UnifiedField* uf) {
    return (EntropyRule){
        .initial = uf->e,
        .growth = uf->i * 0.01,
        .critical = 1.0 - uf->r * 0.1
    };
}

ConnectionRule derive_connection(UnifiedField* uf) {
    return (ConnectionRule){
        .strength = uf->r,
        .plasticity = uf->e,
        .decay = 1.0 - uf->i
    };
}

MemoryRule derive_memory(UnifiedField* uf) {
    return (MemoryRule){
        .persistence = uf->i,
        .recall = uf->r,
        .decay = uf->e * 0.001
    };
}

OrbitalRule derive_orbital(UnifiedField* uf) {
    return (OrbitalRule){
        .eccentricity = uf->e,
        .period = uf->r,
        .stability = uf->i
    };
}

// ═══════════════════════════════════════════════════════════════
// Tile Memory Manager - Four-pool memory system
// ═══════════════════════════════════════════════════════════════

typedef struct {
    uint64_t base;
    size_t size;
    size_t used;
    char purpose[32];
} MemoryPool;

typedef struct {
    MemoryPool pools[MAX_POOLS];
    int pool_count;
    UnifiedField* unified;
} TileManager;

void tile_init(TileManager* tile, UnifiedField* uf) {
    tile->pool_count = 0;
    tile->unified = uf;
}

int tile_add_pool(TileManager* tile, uint64_t base, size_t size, const char* purpose) {
    if (tile->pool_count >= MAX_POOLS) return -1;
    int idx = tile->pool_count++;
    tile->pools[idx].base = base;
    tile->pools[idx].size = size;
    tile->pools[idx].used = 0;
    strncpy(tile->pools[idx].purpose, purpose, 31);
    return idx;
}

// Select pool based on Unified parameters
int tile_select_pool(TileManager* tile) {
    if (tile->pool_count == 0) return -1;
    
    UnifiedField* uf = tile->unified;
    // High i -> select compression pool (low index)
    // High e -> select fast pool (high index)
    if (uf->i > uf->e) return 0;
    return tile->pool_count - 1;
}

uint64_t tile_alloc(TileManager* tile, size_t size) {
    if (tile->pool_count == 0) {
        // Auto-create default pool
        tile_add_pool(tile, 0x10000, 0x100000, "default");
    }
    
    int idx = tile_select_pool(tile);
    if (idx < 0) return 0;
    
    MemoryPool* pool = &tile->pools[idx];
    if (pool->used + size > pool->size) {
        // Try other pools
        for (int i = 0; i < tile->pool_count; i++) {
            if (tile->pools[i].used + size <= tile->pools[i].size) {
                pool = &tile->pools[i];
                break;
            }
        }
    }
    
    if (pool->used + size > pool->size) return 0;
    
    uint64_t addr = pool->base + pool->used;
    pool->used += size;
    return addr;
}

size_t tile_total_used(TileManager* tile) {
    size_t sum = 0;
    for (int i = 0; i < tile->pool_count; i++) {
        sum += tile->pools[i].used;
    }
    return sum;
}

double tile_ratio(TileManager* tile) {
    size_t total = 0, used = 0;
    for (int i = 0; i < tile->pool_count; i++) {
        total += tile->pools[i].size;
        used += tile->pools[i].used;
    }
    return total > 0 ? (double)used / total : 0.0;
}

// ═══════════════════════════════════════════════════════════════
// Fate Scheduler - Dynamic optimization scheduler
// ═══════════════════════════════════════════════════════════════

typedef void (*AdapterFunc)(void*);

typedef struct {
    bool on;                    // fate on/off
    int id_counter;
    
    // Observation values
    double usage;
    double gain;
    double prev_gain;
    int pattern_count;
    
    // Unified Field parameters (Fate controlled)
    UnifiedField field;
    
    // Adapters
    AdapterFunc adapters[MAX_ADAPTERS];
    void* adapter_ctx[MAX_ADAPTERS];
    int adapter_count;
    
    // Learned patterns (simplified - array based)
    char learned_keys[256][64];
    double learned_values[256];
    int learned_count;
    
    // Collapse threshold
    double marginal_threshold;
} FateScheduler;

void fate_init(FateScheduler* fate) {
    fate->on = true;
    fate->id_counter = 0;
    fate->usage = 0.0;
    fate->gain = 0.0;
    fate->prev_gain = 0.0;
    fate->pattern_count = 0;
    fate->adapter_count = 0;
    fate->learned_count = 0;
    fate->marginal_threshold = 0.05;
    unified_init(&fate->field);
}

int fate_next_id(FateScheduler* fate) {
    return ++fate->id_counter;
}

void fate_register_adapter(FateScheduler* fate, AdapterFunc func, void* ctx) {
    if (fate->adapter_count < MAX_ADAPTERS) {
        fate->adapters[fate->adapter_count] = func;
        fate->adapter_ctx[fate->adapter_count] = ctx;
        fate->adapter_count++;
    }
}

void fate_learn(FateScheduler* fate, const char* key, double value) {
    // Find existing
    for (int i = 0; i < fate->learned_count; i++) {
        if (strcmp(fate->learned_keys[i], key) == 0) {
            fate->learned_values[i] = value;
            return;
        }
    }
    // Add new
    if (fate->learned_count < 256) {
        strncpy(fate->learned_keys[fate->learned_count], key, 63);
        fate->learned_values[fate->learned_count] = value;
        fate->learned_count++;
    }
}

double fate_recall(FateScheduler* fate, const char* key) {
    for (int i = 0; i < fate->learned_count; i++) {
        if (strcmp(fate->learned_keys[i], key) == 0) {
            return fate->learned_values[i];
        }
    }
    return 0.0;
}

void fate_observe(FateScheduler* fate, TileManager* tile) {
    if (!fate->on) return;
    fate->usage = tile_ratio(tile);
    fate->pattern_count++;
}

void fate_adapt(FateScheduler* fate) {
    if (!fate->on) return;
    
    // Run adapters
    for (int i = 0; i < fate->adapter_count; i++) {
        fate->adapters[i](fate->adapter_ctx[i]);
    }
    
    // Adjust field parameters based on observation
    if (fate->usage > 0.7) {
        fate->field.e = fmin(1.0, fate->field.e + 0.1);
    }
    if (fate->pattern_count > 100) {
        fate->field.r = fmin(1.0, fate->field.r + 0.05);
    }
}

bool fate_should_collapse(FateScheduler* fate) {
    double delta = fate->gain - fate->prev_gain;
    fate->prev_gain = fate->gain;
    return delta < fate->marginal_threshold;
}

void fate_collapse(FateScheduler* fate) {
    fate_learn(fate, "static:i", fate->field.i);
    fate_learn(fate, "static:e", fate->field.e);
    fate_learn(fate, "static:r", fate->field.r);
    fate->on = false;
}

void fate_tick(FateScheduler* fate, TileManager* tile) {
    if (!fate->on) return;
    fate_observe(fate, tile);
    fate_adapt(fate);
    if (fate_should_collapse(fate)) {
        fate_collapse(fate);
    }
}

// ═══════════════════════════════════════════════════════════════
// Platform - Minimal platform layer (Fate adaptive)
// ═══════════════════════════════════════════════════════════════

typedef struct {
    int id;                 // Platform ID (Fate assigned)
    uint64_t syscall_base;  // Syscall base address (probed)
    bool probed;            // Whether probed
} Platform;

void platform_init(Platform* p) {
    p->id = 0;
    p->syscall_base = 0;
    p->probed = false;
}

// Fate probes platform - runtime auto-detection
void platform_probe(Platform* p, FateScheduler* fate) {
    if (p->probed) return;
    
    // Fate assigns unique ID
    p->id = fate_next_id(fate);
    
    // Probe syscall base (compile-time, may differ at runtime)
    #ifdef __linux__
    p->syscall_base = 0;
    #elif __APPLE__
    p->syscall_base = 0x2000000;
    #else
    p->syscall_base = 0;
    #endif
    
    p->probed = true;
    fate_learn(fate, "platform.id", p->id);
    fate_learn(fate, "platform.syscall_base", p->syscall_base);
}

// ═══════════════════════════════════════════════════════════════
// Bridge - Minimal universal bridge (standard memory protocol)
// ═══════════════════════════════════════════════════════════════

// Standard addresses (externally injected)
#define ADDR_DISPLAY_FB     0x1000
#define ADDR_DISPLAY_WIDTH  0x1004
#define ADDR_DISPLAY_HEIGHT 0x1008
#define ADDR_DISPLAY_PITCH  0x100C
#define ADDR_DISPLAY_FORMAT 0x1010
#define ADDR_DISPLAY_READY  0x1014
#define ADDR_INPUT_BUFFER   0x2000
#define ADDR_INPUT_HEAD     0x2004
#define ADDR_INPUT_TAIL     0x2008
#define ADDR_INPUT_READY    0x200C
#define ADDR_TIME_TICKS     0x3000
#define ADDR_TIME_FREQ      0x3004

typedef struct {
    bool display_ready;
    bool input_ready;
    uint32_t width;
    uint32_t height;
} Bridge;

void bridge_init(Bridge* b) {
    b->display_ready = false;
    b->input_ready = false;
    b->width = 0;
    b->height = 0;
}

// ═══════════════════════════════════════════════════════════════
// Compat - Minimal universal compatibility layer (Fate adaptive)
// ═══════════════════════════════════════════════════════════════

typedef struct {
    bool display_available;
    bool input_available;
    bool storage_available;
    bool network_available;
    bool audio_available;
} Compat;

void compat_init(Compat* c) {
    c->display_available = false;
    c->input_available = false;
    c->storage_available = false;
    c->network_available = false;
    c->audio_available = false;
}

// Fate probes available devices
void compat_probe(Compat* c, FateScheduler* fate) {
    // Fate probes actual devices at runtime
    // Compile-time only records probe requests
    fate_learn(fate, "probe.display", 1);
    fate_learn(fate, "probe.input", 1);
    fate_learn(fate, "probe.storage", 1);
    fate_learn(fate, "probe.network", 1);
    fate_learn(fate, "probe.audio", 1);
}

// ═══════════════════════════════════════════════════════════════
// Variable System
// ═══════════════════════════════════════════════════════════════

typedef enum { VAR_INT, VAR_FLOAT, VAR_STRING, VAR_ARRAY, VAR_OBJECT } VarType;

typedef struct {
    char name[MAX_IDENT];
    VarType type;
    int64_t int_val;
    double float_val;
    char str_val[512];
    int stack_offset;
    bool is_param;
    bool is_global;      // Global variable (uses absolute address)
    uint64_t global_addr; // Absolute address for global vars
} Variable;

// ═══════════════════════════════════════════════════════════════
// Function System
// ═══════════════════════════════════════════════════════════════

typedef struct {
    char name[MAX_IDENT];
    size_t code_offset;
    int param_count;
    char params[16][MAX_IDENT];
    size_t body_pos;
    size_t body_end;
} Function;

// ═══════════════════════════════════════════════════════════════
// Code Generator
// ═══════════════════════════════════════════════════════════════

typedef struct {
    uint8_t* code;
    size_t code_pos;
    size_t code_cap;
    
    uint8_t* data;
    size_t data_pos;
    size_t data_cap;
    
    Variable vars[MAX_VARS];
    int var_count;
    int stack_size;
    int global_var_count;  // Number of global variables
    size_t global_data_pos; // Position in data for global vars
    
    Function funcs[MAX_FUNCS];
    int func_count;
    
    struct { size_t pos; char label[64]; } fixups[MAX_LABELS];
    int fixup_count;
    
    struct { char name[64]; size_t pos; } labels[MAX_LABELS];
    int label_count;
    
    int when_id;
    int loop_id;
    int platform;  // 1=Linux, 2=macOS, 3=Windows
    bool raw_mode;
    bool in_function;  // Currently compiling a function body
} CodeGen;

void codegen_init(CodeGen* cg) {
    cg->code = malloc(MAX_CODE);
    cg->code_pos = 0;
    cg->code_cap = MAX_CODE;
    cg->data = malloc(MAX_DATA);
    cg->data_pos = 0;
    cg->data_cap = MAX_DATA;
    cg->var_count = 0;
    cg->stack_size = 0;
    cg->global_var_count = 0;
    cg->global_data_pos = 0;
    cg->func_count = 0;
    cg->fixup_count = 0;
    cg->label_count = 0;
    cg->when_id = 0;
    cg->loop_id = 0;
    cg->platform = 1;  // Linux default
    cg->raw_mode = false;
    cg->in_function = false;
}

void codegen_free(CodeGen* cg) {
    free(cg->code);
    free(cg->data);
}

// ═══════════════════════════════════════════════════════════════
// Byte emission
// ═══════════════════════════════════════════════════════════════

void emit_byte(CodeGen* cg, uint8_t b) {
    if (cg->code_pos < cg->code_cap) cg->code[cg->code_pos++] = b;
}

void emit_bytes(CodeGen* cg, const uint8_t* bytes, size_t len) {
    for (size_t i = 0; i < len; i++) emit_byte(cg, bytes[i]);
}

void emit_u32(CodeGen* cg, uint32_t v) {
    emit_byte(cg, v & 0xff);
    emit_byte(cg, (v >> 8) & 0xff);
    emit_byte(cg, (v >> 16) & 0xff);
    emit_byte(cg, (v >> 24) & 0xff);
}

void emit_i32(CodeGen* cg, int32_t v) { emit_u32(cg, (uint32_t)v); }

void emit_u64(CodeGen* cg, uint64_t v) {
    emit_u32(cg, v & 0xffffffff);
    emit_u32(cg, (v >> 32) & 0xffffffff);
}

// ═══════════════════════════════════════════════════════════════
// Labels and fixups
// ═══════════════════════════════════════════════════════════════

void add_label(CodeGen* cg, const char* name) {
    if (cg->label_count < MAX_LABELS) {
        strncpy(cg->labels[cg->label_count].name, name, 63);
        cg->labels[cg->label_count].pos = cg->code_pos;
        cg->label_count++;
    }
}

void add_fixup(CodeGen* cg, const char* label) {
    if (cg->fixup_count < MAX_LABELS) {
        cg->fixups[cg->fixup_count].pos = cg->code_pos;
        strncpy(cg->fixups[cg->fixup_count].label, label, 63);
        cg->fixup_count++;
    }
    emit_u32(cg, 0);
}

void resolve_fixups(CodeGen* cg) {
    for (int i = 0; i < cg->fixup_count; i++) {
        for (int j = 0; j < cg->label_count; j++) {
            if (strcmp(cg->fixups[i].label, cg->labels[j].name) == 0) {
                size_t fix_pos = cg->fixups[i].pos;
                size_t target = cg->labels[j].pos;
                int32_t offset = (int32_t)(target - fix_pos - 4);
                cg->code[fix_pos] = offset & 0xff;
                cg->code[fix_pos + 1] = (offset >> 8) & 0xff;
                cg->code[fix_pos + 2] = (offset >> 16) & 0xff;
                cg->code[fix_pos + 3] = (offset >> 24) & 0xff;
                break;
            }
        }
    }
}

// ═══════════════════════════════════════════════════════════════
// Variable and function lookup
// ═══════════════════════════════════════════════════════════════

Variable* find_var(CodeGen* cg, const char* name) {
    for (int i = cg->var_count - 1; i >= 0; i--) {
        if (strcmp(cg->vars[i].name, name) == 0) return &cg->vars[i];
    }
    return NULL;
}

Variable* add_var(CodeGen* cg, const char* name, VarType type) {
    if (cg->var_count >= MAX_VARS) return NULL;
    Variable* v = &cg->vars[cg->var_count++];
    strncpy(v->name, name, MAX_IDENT - 1);
    v->type = type;
    v->int_val = 0;
    v->is_param = false;
    
    if (cg->in_function) {
        // Local variable: use stack relative to rbp
        v->is_global = false;
        v->global_addr = 0;
        cg->stack_size += 8;
        v->stack_offset = -cg->stack_size;
    } else {
        // Global variable: use absolute address in data section
        v->is_global = true;
        // Global vars stored at end of data section (after strings)
        // We'll use a fixed base address + offset
        v->global_addr = 0x600000 + cg->global_data_pos; // Fixed base for globals
        cg->global_data_pos += 8;
        cg->global_var_count++;
        v->stack_offset = 0; // Not used for globals
    }
    return v;
}

Function* find_func(CodeGen* cg, const char* name) {
    for (int i = 0; i < cg->func_count; i++) {
        if (strcmp(cg->funcs[i].name, name) == 0) return &cg->funcs[i];
    }
    return NULL;
}

// ═══════════════════════════════════════════════════════════════
// x86-64 instruction generation
// ═══════════════════════════════════════════════════════════════

void gen_push_rbp(CodeGen* cg) { emit_byte(cg, 0x55); }
void gen_pop_rbp(CodeGen* cg) { emit_byte(cg, 0x5d); }
void gen_push_rax(CodeGen* cg) { emit_byte(cg, 0x50); }
void gen_pop_rax(CodeGen* cg) { emit_byte(cg, 0x58); }
void gen_push_rbx(CodeGen* cg) { emit_byte(cg, 0x53); }
void gen_pop_rbx(CodeGen* cg) { emit_byte(cg, 0x5b); }

void gen_mov_rbp_rsp(CodeGen* cg) { emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0xe5}, 3); }
void gen_mov_rsp_rbp(CodeGen* cg) { emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0xec}, 3); }
void gen_ret(CodeGen* cg) { emit_byte(cg, 0xc3); }
void gen_syscall(CodeGen* cg) { emit_bytes(cg, (uint8_t[]){0x0f, 0x05}, 2); }
void gen_pause(CodeGen* cg) { emit_bytes(cg, (uint8_t[]){0xf3, 0x90}, 2); }
void gen_nop(CodeGen* cg) { emit_byte(cg, 0x90); }

void gen_sub_rsp(CodeGen* cg, int32_t n) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x81, 0xec}, 3);
    emit_i32(cg, n);
}

void gen_add_rsp(CodeGen* cg, int32_t n) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x81, 0xc4}, 3);
    emit_i32(cg, n);
}

void gen_mov_rax_imm(CodeGen* cg, int64_t v) {
    emit_bytes(cg, (uint8_t[]){0x48, 0xb8}, 2);
    emit_u64(cg, (uint64_t)v);
}

void gen_mov_rdi_imm(CodeGen* cg, int64_t v) {
    emit_bytes(cg, (uint8_t[]){0x48, 0xbf}, 2);
    emit_u64(cg, (uint64_t)v);
}

void gen_mov_rsi_imm(CodeGen* cg, int64_t v) {
    emit_bytes(cg, (uint8_t[]){0x48, 0xbe}, 2);
    emit_u64(cg, (uint64_t)v);
}

void gen_mov_rdx_imm(CodeGen* cg, int64_t v) {
    emit_bytes(cg, (uint8_t[]){0x48, 0xba}, 2);
    emit_u64(cg, (uint64_t)v);
}

// mov rdi, rax
void gen_mov_rdi_rax(CodeGen* cg) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0xc7}, 3);
}

// mov rsi, rax
void gen_mov_rsi_rax(CodeGen* cg) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0xc6}, 3);
}

// mov rdx, rax
void gen_mov_rdx_rax(CodeGen* cg) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0xc2}, 3);
}

void gen_mov_rax_rbp_off(CodeGen* cg, int32_t off) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x8b, 0x85}, 3);
    emit_i32(cg, off);
}

void gen_mov_rbp_off_rax(CodeGen* cg, int32_t off) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0x85}, 3);
    emit_i32(cg, off);
}

// Load from absolute address: mov rax, [addr]
void gen_mov_rax_abs(CodeGen* cg, uint64_t addr) {
    // movabs rax, addr; mov rax, [rax]
    emit_bytes(cg, (uint8_t[]){0x48, 0xb8}, 2);  // movabs rax, imm64
    emit_u64(cg, addr);
    emit_bytes(cg, (uint8_t[]){0x48, 0x8b, 0x00}, 3);  // mov rax, [rax]
}

// Store to absolute address: mov [addr], rax
void gen_mov_abs_rax(CodeGen* cg, uint64_t addr) {
    // push rax; movabs rbx, addr; pop rax; mov [rbx], rax
    emit_byte(cg, 0x50);  // push rax
    emit_bytes(cg, (uint8_t[]){0x48, 0xbb}, 2);  // movabs rbx, imm64
    emit_u64(cg, addr);
    emit_byte(cg, 0x58);  // pop rax
    emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0x03}, 3);  // mov [rbx], rax
}

// Load variable (global or local)
void gen_load_var(CodeGen* cg, Variable* v) {
    if (v->is_global) {
        gen_mov_rax_abs(cg, v->global_addr);
    } else {
        gen_mov_rax_rbp_off(cg, v->stack_offset);
    }
}

// Store variable (global or local)
void gen_store_var(CodeGen* cg, Variable* v) {
    if (v->is_global) {
        gen_mov_abs_rax(cg, v->global_addr);
    } else {
        gen_mov_rbp_off_rax(cg, v->stack_offset);
    }
}

void gen_mul_rax_rbx(CodeGen* cg) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x0f, 0xaf, 0xc3}, 4);
}

void gen_div_rax_rbx(CodeGen* cg) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x99}, 2);
    emit_bytes(cg, (uint8_t[]){0x48, 0xf7, 0xfb}, 3);
}

void gen_test_rax_rax(CodeGen* cg) {
    emit_bytes(cg, (uint8_t[]){0x48, 0x85, 0xc0}, 3);
}

void gen_je(CodeGen* cg, const char* label) {
    emit_bytes(cg, (uint8_t[]){0x0f, 0x84}, 2);
    add_fixup(cg, label);
}

void gen_jne(CodeGen* cg, const char* label) {
    emit_bytes(cg, (uint8_t[]){0x0f, 0x85}, 2);
    add_fixup(cg, label);
}

void gen_jmp(CodeGen* cg, const char* label) {
    emit_byte(cg, 0xe9);
    add_fixup(cg, label);
}

void gen_call(CodeGen* cg, const char* label) {
    emit_byte(cg, 0xe8);
    add_fixup(cg, label);
}

void gen_exit(CodeGen* cg, int code) {
    gen_mov_rax_imm(cg, 60);  // Linux sys_exit
    gen_mov_rdi_imm(cg, code);
    gen_syscall(cg);
}

// Exit with value in rax
void gen_exit_rax(CodeGen* cg) {
    // mov rdi, rax
    emit_bytes(cg, (uint8_t[]){0x48, 0x89, 0xc7}, 3);
    gen_mov_rax_imm(cg, 60);  // Linux sys_exit
    gen_syscall(cg);
}

void gen_prologue(CodeGen* cg) {
    gen_push_rbp(cg);
    gen_mov_rbp_rsp(cg);
}

void gen_epilogue(CodeGen* cg) {
    gen_mov_rsp_rbp(cg);
    gen_pop_rbp(cg);
    gen_ret(cg);
}

void gen_event_loop(CodeGen* cg) {
    gen_pause(cg);
    emit_bytes(cg, (uint8_t[]){0xeb, 0xfc}, 2);
}

// ═══════════════════════════════════════════════════════════════
// ELF Generator
// ═══════════════════════════════════════════════════════════════

void write_elf(CodeGen* cg, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;
    
    uint64_t base = 0x400000;
    uint64_t entry = base + 120;
    size_t total_size = cg->code_pos + cg->data_pos;
    
    uint8_t ehdr[64] = {0};
    ehdr[0] = 0x7f; ehdr[1] = 'E'; ehdr[2] = 'L'; ehdr[3] = 'F';
    ehdr[4] = 2; ehdr[5] = 1; ehdr[6] = 1;
    ehdr[16] = 2; ehdr[18] = 0x3e; ehdr[20] = 1;
    memcpy(ehdr + 24, &entry, 8);
    uint64_t phoff = 64;
    memcpy(ehdr + 32, &phoff, 8);
    ehdr[52] = 64; ehdr[54] = 56; ehdr[56] = 1;
    
    uint8_t phdr[56] = {0};
    uint32_t p_type = 1, p_flags = 7;
    memcpy(phdr + 0, &p_type, 4);
    memcpy(phdr + 4, &p_flags, 4);
    uint64_t file_size = 120 + total_size;
    // mem_size needs to cover global variable area at 0x600000+
    // Global vars are at 0x600000, so we need at least 0x200000 + globals
    uint64_t global_size = cg->global_data_pos > 0 ? cg->global_data_pos : 0x1000;
    uint64_t mem_size = 0x600000 - base + global_size + 0x10000; // Cover 0x400000 to 0x600000+globals
    memcpy(phdr + 16, &base, 8);
    memcpy(phdr + 24, &base, 8);
    memcpy(phdr + 32, &file_size, 8);
    memcpy(phdr + 40, &mem_size, 8);
    uint64_t align = 0x1000;
    memcpy(phdr + 48, &align, 8);
    
    fwrite(ehdr, 1, 64, f);
    fwrite(phdr, 1, 56, f);
    fwrite(cg->code, 1, cg->code_pos, f);
    fwrite(cg->data, 1, cg->data_pos, f);
    fclose(f);
    chmod(filename, 0755);
}

void write_raw(CodeGen* cg, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;
    fwrite(cg->code, 1, cg->code_pos, f);
    fclose(f);
}

// ═══════════════════════════════════════════════════════════════
// Compiler
// ═══════════════════════════════════════════════════════════════

typedef struct Compiler Compiler;

struct Compiler {
    const char* source;
    size_t pos;
    size_t len;
    bool fate_mode;
    int loop_depth;
    char loop_labels[16][2][64];
    
    UnifiedField unified;
    TileManager tile;
    FateScheduler fate;
    CodeGen codegen;
    
    // Compatibility layer (minimal universal)
    Platform platform;
    Bridge bridge;
    Compat compat;
    
    Function* current_func;
    int base_var_count;
};

void compiler_init(Compiler* c, const char* source) {
    c->source = source;
    c->pos = 0;
    c->len = strlen(source);
    c->fate_mode = true;
    c->loop_depth = 0;
    c->current_func = NULL;
    c->base_var_count = 0;
    
    unified_init(&c->unified);
    tile_init(&c->tile, &c->unified);
    fate_init(&c->fate);
    codegen_init(&c->codegen);
    
    // Initialize compatibility layer (minimal universal)
    platform_init(&c->platform);
    bridge_init(&c->bridge);
    compat_init(&c->compat);
    
    // Fate adaptive probing
    platform_probe(&c->platform, &c->fate);
    compat_probe(&c->compat, &c->fate);
}

void compiler_free(Compiler* c) {
    codegen_free(&c->codegen);
}

// ═══════════════════════════════════════════════════════════════
// Parsing helper functions
// ═══════════════════════════════════════════════════════════════

char peek(Compiler* c) { return (c->pos < c->len) ? c->source[c->pos] : 0; }
char peek_n(Compiler* c, int n) { return (c->pos + n < c->len) ? c->source[c->pos + n] : 0; }
char advance(Compiler* c) { return (c->pos < c->len) ? c->source[c->pos++] : 0; }

void skip_whitespace(Compiler* c) {
    while (c->pos < c->len) {
        char ch = peek(c);
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            advance(c);
        }
        else if (ch == '/' && peek_n(c, 1) == '/') {
            // Skip // comment to end of line
            advance(c); advance(c);  // skip //
            while (c->pos < c->len && peek(c) != '\n') advance(c);
            if (peek(c) == '\n') advance(c);
        }
        else {
            break;
        }
    }
}

void skip_line(Compiler* c) {
    while (c->pos < c->len && peek(c) != '\n') advance(c);
    if (peek(c) == '\n') advance(c);
}

bool match(Compiler* c, const char* str) {
    size_t len = strlen(str);
    if (c->pos + len > c->len) return false;
    return strncmp(c->source + c->pos, str, len) == 0;
}

bool is_ident_start(char ch) { return isalpha(ch) || ch == '_'; }
bool is_ident_char(char ch) { return isalnum(ch) || ch == '_' || ch == '.'; }

char* parse_ident(Compiler* c) {
    char* buf = malloc(MAX_IDENT);
    int bi = 0;
    while (c->pos < c->len && is_ident_char(peek(c)) && bi < MAX_IDENT - 1) {
        buf[bi++] = advance(c);
    }
    buf[bi] = 0;
    return buf;
}

char* parse_string(Compiler* c) {
    char* buf = malloc(4096);
    int bi = 0;
    if (peek(c) == '"') advance(c);
    while (c->pos < c->len && peek(c) != '"' && bi < 4095) {
        char ch = advance(c);
        if (ch == '\\' && c->pos < c->len) {
            char esc = advance(c);
            if (esc == 'n') buf[bi++] = '\n';
            else if (esc == 't') buf[bi++] = '\t';
            else if (esc == 'r') buf[bi++] = '\r';
            else if (esc == '0') buf[bi++] = '\0';
            else if (esc == 'x' && c->pos + 2 <= c->len) {
                char hex[3] = {advance(c), advance(c), 0};
                buf[bi++] = (char)strtol(hex, NULL, 16);
            } else buf[bi++] = esc;
        } else buf[bi++] = ch;
    }
    if (peek(c) == '"') advance(c);
    buf[bi] = 0;
    return buf;
}

int64_t parse_number(Compiler* c) {
    int64_t num = 0;
    bool neg = false;
    
    if (peek(c) == '-') { neg = true; advance(c); }
    
    if (peek(c) == '0' && peek_n(c, 1) == 'x') {
        advance(c); advance(c);
        while (c->pos < c->len && isxdigit(peek(c))) {
            char ch = advance(c);
            if (ch >= '0' && ch <= '9') num = num * 16 + (ch - '0');
            else if (ch >= 'a' && ch <= 'f') num = num * 16 + (ch - 'a' + 10);
            else if (ch >= 'A' && ch <= 'F') num = num * 16 + (ch - 'A' + 10);
        }
    } else {
        while (c->pos < c->len && isdigit(peek(c))) {
            num = num * 10 + (advance(c) - '0');
        }
    }
    
    // Decimal part
    if (peek(c) == '.') {
        advance(c);
        double frac = 0.1;
        while (c->pos < c->len && isdigit(peek(c))) {
            num += (int64_t)((advance(c) - '0') * frac);
            frac *= 0.1;
        }
    }
    
    return neg ? -num : num;
}

// Forward declarations
void compile_block(Compiler* c);
void compile_statement(Compiler* c);
int64_t compile_expr(Compiler* c);

// ═══════════════════════════════════════════════════════════════
// Expression compilation
// ═══════════════════════════════════════════════════════════════

int64_t compile_expr(Compiler* c) {
    skip_whitespace(c);
    
    int64_t left = 0;
    
    if (isdigit(peek(c)) || (peek(c) == '-' && isdigit(peek_n(c, 1)))) {
        left = parse_number(c);
        gen_mov_rax_imm(&c->codegen, left);
    }
    else if (peek(c) == '"') {
        char* str = parse_string(c);
        size_t len = strlen(str);
        
        // Embed string inline in code, use lea to get address
        // jmp over string data
        emit_byte(&c->codegen, 0xeb);  // jmp short
        emit_byte(&c->codegen, len + 1);  // skip len+1 bytes
        
        size_t str_pos = c->codegen.code_pos;
        for (size_t i = 0; i <= len; i++) emit_byte(&c->codegen, str[i]);
        
        // lea rax, [rip - offset_to_string]
        int32_t rel = -(int32_t)(c->codegen.code_pos - str_pos + 7);
        emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x05}, 3);  // lea rax, [rip+disp32]
        emit_i32(&c->codegen, rel);
        
        left = 0;  // Address is computed at runtime
        free(str);
    }
    else if (is_ident_start(peek(c))) {
        char* name = parse_ident(c);
        skip_whitespace(c);
        
        if (peek(c) == '(') {
            advance(c);
            skip_whitespace(c);
            
            // Built-in functions
            if (strcmp(name, "getchar") == 0) {
                if (peek(c) == ')') advance(c);
                gen_sub_rsp(&c->codegen, 16);
                gen_mov_rax_imm(&c->codegen, 0);
                gen_mov_rdi_imm(&c->codegen, 0);
                emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x34, 0x24}, 4);
                gen_mov_rdx_imm(&c->codegen, 1);
                gen_syscall(&c->codegen);
                emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0x04, 0x24}, 5);
                gen_add_rsp(&c->codegen, 16);
                left = 0;
            }
            // peek(addr) - read byte from memory
            else if (strcmp(name, "peek") == 0) {
                compile_expr(c);  // addr in rax
                skip_whitespace(c);
                if (peek(c) == ')') advance(c);
                // movzx rax, byte [rax]
                emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0x00}, 4);
                left = 0;
            }
            // poke(addr, val) - write byte to memory
            else if (strcmp(name, "poke") == 0) {
                compile_expr(c);  // addr
                gen_push_rax(&c->codegen);
                skip_whitespace(c);
                if (peek(c) == ',') advance(c);
                skip_whitespace(c);
                compile_expr(c);  // val in rax
                skip_whitespace(c);
                if (peek(c) == ')') advance(c);
                gen_pop_rbx(&c->codegen);
                // mov [rbx], al
                emit_bytes(&c->codegen, (uint8_t[]){0x88, 0x03}, 2);
                left = 0;
            }
            // syscall.xxx - handle syscall.open, syscall.read, etc.
            // Note: name might be "syscall" or "syscall.xxx" depending on parse_ident
            else if (strncmp(name, "syscall", 7) == 0) {
                const char* syscall_name = name + 7;
                if (*syscall_name == '.') syscall_name++;  // skip '.'
                else if (peek(c) == '.') {
                    advance(c);
                    free(name);
                    name = parse_ident(c);
                    syscall_name = name;
                }
                skip_whitespace(c);
                if (peek(c) == '(') advance(c);
                
                if (strcmp(syscall_name, "open") == 0) {
                    compile_expr(c); gen_push_rax(&c->codegen);  // path
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // flags
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_mov_rdx_rax(&c->codegen);  // mode
                    gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);  // flags
                    gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);  // path
                    gen_mov_rax_imm(&c->codegen, 2);  // sys_open
                    gen_syscall(&c->codegen);
                }
                else if (strcmp(syscall_name, "read") == 0) {
                    compile_expr(c); gen_push_rax(&c->codegen);  // fd
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // buf
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_mov_rdx_rax(&c->codegen);  // count
                    gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);  // buf
                    gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);  // fd
                    gen_mov_rax_imm(&c->codegen, 0);  // sys_read
                    gen_syscall(&c->codegen);
                }
                else if (strcmp(syscall_name, "write") == 0) {
                    compile_expr(c); gen_push_rax(&c->codegen);  // fd
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // buf
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_mov_rdx_rax(&c->codegen);  // count
                    gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);  // buf
                    gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);  // fd
                    gen_mov_rax_imm(&c->codegen, 1);  // sys_write
                    gen_syscall(&c->codegen);
                }
                else if (strcmp(syscall_name, "close") == 0) {
                    compile_expr(c); gen_mov_rdi_rax(&c->codegen);  // fd
                    gen_mov_rax_imm(&c->codegen, 3);  // sys_close
                    gen_syscall(&c->codegen);
                }
                else if (strcmp(syscall_name, "mmap") == 0) {
                    // Push all args to stack first, then pop to correct regs
                    compile_expr(c); gen_push_rax(&c->codegen);  // addr
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // len
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // prot
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // flags
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c); gen_push_rax(&c->codegen);  // fd
                    skip_whitespace(c); if (peek(c) == ',') advance(c);
                    compile_expr(c);  // offset -> r9
                    emit_bytes(&c->codegen, (uint8_t[]){0x49, 0x89, 0xc1}, 3);
                    // pop r8 (fd)
                    emit_bytes(&c->codegen, (uint8_t[]){0x41, 0x58}, 2);
                    // pop r10 (flags)
                    emit_bytes(&c->codegen, (uint8_t[]){0x41, 0x5a}, 2);
                    gen_pop_rax(&c->codegen);  // prot -> rdx
                    gen_mov_rdx_rax(&c->codegen);
                    gen_pop_rax(&c->codegen);  // len -> rsi
                    gen_mov_rsi_rax(&c->codegen);
                    gen_pop_rax(&c->codegen);  // addr -> rdi
                    gen_mov_rdi_rax(&c->codegen);
                    gen_mov_rax_imm(&c->codegen, 9);  // sys_mmap
                    gen_syscall(&c->codegen);
                }
                skip_whitespace(c);
                if (peek(c) == ')') advance(c);
                // Don't free syscall_name - it points into 'name' which is freed later
                left = 0;
            }
            else {
                int argc = 0;
                while (peek(c) != ')' && c->pos < c->len && argc < 16) {
                    compile_expr(c);
                    gen_push_rax(&c->codegen);
                    argc++;
                    skip_whitespace(c);
                    if (peek(c) == ',') advance(c);
                    skip_whitespace(c);
                }
                if (peek(c) == ')') advance(c);
                
                gen_call(&c->codegen, name);
                if (argc > 0) gen_add_rsp(&c->codegen, argc * 8);
                left = 0;
            }
        } else {
            Variable* v = find_var(&c->codegen, name);
            if (v) {
                gen_load_var(&c->codegen, v);
                left = v->int_val;
            } else {
                left = 0;
                gen_mov_rax_imm(&c->codegen, 0);
            }
        }
        free(name);
    }
    else if (peek(c) == '(') {
        advance(c);
        left = compile_expr(c);
        skip_whitespace(c);
        if (peek(c) == ')') advance(c);
    }
    else {
        left = 0;
        gen_mov_rax_imm(&c->codegen, 0);
    }
    
    // Binary operators
    skip_whitespace(c);
    while (c->pos < c->len) {
        char op = peek(c);
        char op2 = peek_n(c, 1);
        
        if (op == '+' && op2 != '=') {
            advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x01, 0xd8}, 3);
        }
        else if (op == '-' && !isdigit(op2) && op2 != '=') {
            advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x89, 0xc1}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x89, 0xd8}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x29, 0xc8}, 3);
        }
        else if (op == '*' && op2 != '=') {
            advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            gen_mul_rax_rbx(&c->codegen);
        }
        else if (op == '/' && op2 != '=') {
            advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x89, 0xc3}, 3);
            gen_pop_rax(&c->codegen);
            gen_div_rax_rbx(&c->codegen);
        }
        else if (op == '>' && op2 == '=') {
            advance(c); advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x39, 0xc3}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x0f, 0x9d, 0xc0}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0xc0}, 4);
        }
        else if (op == '<' && op2 == '=') {
            advance(c); advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x39, 0xc3}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x0f, 0x9e, 0xc0}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0xc0}, 4);
        }
        else if (op == '=' && op2 == '=') {
            advance(c); advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x39, 0xc3}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x0f, 0x94, 0xc0}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0xc0}, 4);
        }
        else if (op == '!' && op2 == '=') {
            advance(c); advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x39, 0xc3}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x0f, 0x95, 0xc0}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0xc0}, 4);
        }
        else if (op == '>' && op2 != '>') {
            advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x39, 0xc3}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x0f, 0x9f, 0xc0}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0xc0}, 4);
        }
        else if (op == '<' && op2 != '<') {
            advance(c);
            gen_push_rax(&c->codegen);
            compile_expr(c);
            gen_pop_rbx(&c->codegen);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x39, 0xc3}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x0f, 0x9c, 0xc0}, 3);
            emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0xc0}, 4);
        }
        else {
            break;
        }
    }
    
    return left;
}

// ═══════════════════════════════════════════════════════════════
// Statement compilation
// ═══════════════════════════════════════════════════════════════

void compile_out(Compiler* c) {
    skip_whitespace(c);
    char* text = parse_string(c);
    size_t len = strlen(text);
    if (len == 0) { free(text); return; }
    
    // Use jmp near (32-bit offset) to skip data, supports long strings
    emit_byte(&c->codegen, 0xe9);  // jmp near rel32
    emit_i32(&c->codegen, len);    // Skip len bytes
    
    size_t data_pos = c->codegen.code_pos;
    for (size_t i = 0; i < len; i++) emit_byte(&c->codegen, text[i]);
    
    gen_mov_rax_imm(&c->codegen, 1);
    gen_mov_rdi_imm(&c->codegen, 1);
    
    int32_t rel = -(int32_t)(c->codegen.code_pos - data_pos + 7);
    emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x35}, 3);
    emit_i32(&c->codegen, rel);
    
    gen_mov_rdx_imm(&c->codegen, len);
    gen_syscall(&c->codegen);
    
    free(text);
}

void compile_emit(Compiler* c) {
    skip_whitespace(c);
    char* bytes = parse_string(c);
    size_t len = strlen(bytes);
    if (len == 0) { free(bytes); return; }
    
    // Emit outputs bytes at runtime, use jmp near for long data
    emit_byte(&c->codegen, 0xe9);  // jmp near rel32
    emit_i32(&c->codegen, len);    // Skip len bytes
    
    size_t data_pos = c->codegen.code_pos;
    for (size_t i = 0; i < len; i++) emit_byte(&c->codegen, (uint8_t)bytes[i]);
    
    gen_mov_rax_imm(&c->codegen, 1);
    gen_mov_rdi_imm(&c->codegen, 1);
    
    int32_t rel = -(int32_t)(c->codegen.code_pos - data_pos + 7);
    emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x35}, 3);
    emit_i32(&c->codegen, rel);
    
    gen_mov_rdx_imm(&c->codegen, len);
    gen_syscall(&c->codegen);
    
    free(bytes);
}

void compile_fn_def(Compiler* c) {
    skip_whitespace(c);
    char* name = parse_ident(c);
    
    if (c->codegen.func_count >= MAX_FUNCS) { free(name); return; }
    
    Function* fn = &c->codegen.funcs[c->codegen.func_count++];
    strncpy(fn->name, name, MAX_IDENT - 1);
    fn->param_count = 0;
    fn->body_pos = 0;
    fn->body_end = 0;
    
    skip_whitespace(c);
    while (c->pos < c->len && peek(c) != '{' && fn->param_count < 16) {
        if (is_ident_start(peek(c))) {
            char* param = parse_ident(c);
            strncpy(fn->params[fn->param_count++], param, MAX_IDENT - 1);
            free(param);
        }
        skip_whitespace(c);
    }
    
    if (peek(c) == '{') {
        advance(c);
        fn->body_pos = c->pos;
        int depth = 1;
        while (c->pos < c->len && depth > 0) {
            char ch = peek(c);
            if (ch == '{') depth++;
            else if (ch == '}') depth--;
            else if (ch == '"') {
                advance(c);
                while (c->pos < c->len && peek(c) != '"') {
                    if (peek(c) == '\\') advance(c);
                    advance(c);
                }
            } else if (ch == '#') {
                while (c->pos < c->len && peek(c) != '\n') advance(c);
            }
            advance(c);
        }
        fn->body_end = c->pos - 1;
    }
    
    free(name);
}

void compile_when(Compiler* c) {
    int id = c->codegen.when_id++;
    char end_label[64];
    sprintf(end_label, "_when_end_%d", id);
    
    skip_whitespace(c);
    compile_expr(c);
    
    gen_test_rax_rax(&c->codegen);
    gen_je(&c->codegen, end_label);
    
    skip_whitespace(c);
    if (peek(c) == '{') compile_block(c);
    
    add_label(&c->codegen, end_label);
}

void compile_loop(Compiler* c) {
    int id = c->codegen.loop_id++;
    
    char start_label[64], end_label[64];
    sprintf(start_label, "_loop_start_%d", id);
    sprintf(end_label, "_loop_end_%d", id);
    
    if (c->loop_depth < 16) {
        strncpy(c->loop_labels[c->loop_depth][0], start_label, 63);
        strncpy(c->loop_labels[c->loop_depth][1], end_label, 63);
        c->loop_depth++;
    }
    
    add_label(&c->codegen, start_label);
    
    skip_whitespace(c);
    if (peek(c) == '{') compile_block(c);
    
    // Fate hook: insert observation in loop
    if (c->fate_mode && c->fate.on) {
        fate_tick(&c->fate, &c->tile);
    }
    
    gen_jmp(&c->codegen, start_label);
    add_label(&c->codegen, end_label);
    
    if (c->loop_depth > 0) c->loop_depth--;
}

void compile_break(Compiler* c) {
    if (c->loop_depth > 0) {
        gen_jmp(&c->codegen, c->loop_labels[c->loop_depth - 1][1]);
    }
}

void compile_return(Compiler* c) {
    skip_whitespace(c);
    if (c->pos < c->len && peek(c) != '\n' && peek(c) != '}') {
        compile_expr(c);
    }
    
    // If inside a loop, -> acts as break (jump to loop end)
    // If outside loops (at function level), -> acts as return
    if (c->loop_depth > 0) {
        // Break out of innermost loop
        gen_jmp(&c->codegen, c->loop_labels[c->loop_depth - 1][1]);
    } else {
        // Return from function
        gen_epilogue(&c->codegen);
    }
}

void compile_assign(Compiler* c, const char* name) {
    skip_whitespace(c);
    
    Variable* v = find_var(&c->codegen, name);
    if (!v) v = add_var(&c->codegen, name, VAR_INT);
    
    if (v) {
        compile_expr(c);
        gen_store_var(&c->codegen, v);
    }
}

void compile_block(Compiler* c) {
    skip_whitespace(c);
    if (peek(c) == '{') advance(c);
    
    while (c->pos < c->len) {
        skip_whitespace(c);
        if (peek(c) == '}') {
            advance(c);
            break;
        }
        compile_statement(c);
    }
}

// Skip block declarations
void skip_block_decl(Compiler* c) {
    while (c->pos < c->len && peek(c) != '{') advance(c);
    if (peek(c) == '{') {
        advance(c);
        int depth = 1;
        while (c->pos < c->len && depth > 0) {
            char ch = peek(c);
            if (ch == '{') depth++;
            else if (ch == '}') depth--;
            else if (ch == '"') {
                advance(c);
                while (c->pos < c->len && peek(c) != '"') {
                    if (peek(c) == '\\') advance(c);
                    advance(c);
                }
            } else if (ch == '#') {
                while (c->pos < c->len && peek(c) != '\n') advance(c);
            }
            advance(c);
        }
    }
}

// Parse unified { i: v, e: v, r: v }
void parse_unified_block(Compiler* c) {
    skip_whitespace(c);
    if (peek(c) != '{') { skip_line(c); return; }
    advance(c);
    
    while (c->pos < c->len && peek(c) != '}') {
        skip_whitespace(c);
        if (peek(c) == '}') break;
        
        char* key = parse_ident(c);
        skip_whitespace(c);
        if (peek(c) == ':') advance(c);
        skip_whitespace(c);
        double val = (double)parse_number(c);
        
        if (strcmp(key, "i") == 0 || strcmp(key, "information_density") == 0) {
            c->unified.i = val;
        } else if (strcmp(key, "e") == 0 || strcmp(key, "entropy_gradient") == 0) {
            c->unified.e = val;
        } else if (strcmp(key, "r") == 0 || strcmp(key, "relation_strength") == 0) {
            c->unified.r = val;
        }
        
        free(key);
        skip_whitespace(c);
        if (peek(c) == ',') advance(c);
    }
    if (peek(c) == '}') advance(c);
}

void compile_statement(Compiler* c) {
    skip_whitespace(c);
    if (c->pos >= c->len) return;
    
    // Comments
    if (peek(c) == '#') { skip_line(c); return; }
    
    // out
    if (match(c, "out ")) { c->pos += 4; compile_out(c); return; }
    
    // emit
    if (match(c, "emit ")) { c->pos += 5; compile_emit(c); return; }
    
    // fn
    if (match(c, "fn ")) { c->pos += 3; compile_fn_def(c); return; }
    
    // when
    if (match(c, "when ")) { c->pos += 5; compile_when(c); return; }
    
    // loop
    if (match(c, "loop")) { c->pos += 4; skip_whitespace(c); compile_loop(c); return; }
    
    // break
    if (match(c, "break")) { c->pos += 5; compile_break(c); return; }
    
    // return / ->
    if (match(c, "return")) { c->pos += 6; compile_return(c); return; }
    if (match(c, "-> ")) { c->pos += 3; compile_return(c); return; }
    
    // keep
    if (match(c, "keep")) { c->pos += 4; gen_event_loop(&c->codegen); return; }
    
    // fate on/off
    if (match(c, "fate on")) { c->pos += 7; c->fate_mode = true; c->fate.on = true; return; }
    if (match(c, "fate off")) { c->pos += 8; c->fate_mode = false; c->fate.on = false; return; }
    
    // limit
    if (match(c, "limit ")) {
        c->pos += 6;
        int n = (int)parse_number(c);
        c->fate.marginal_threshold = 1.0 / n;
        return;
    }
    
    // syscall.exit
    if (match(c, "syscall.exit(")) {
        c->pos += 13;
        skip_whitespace(c);
        // Check if it's a simple number or an expression
        char ch = peek(c);
        if ((ch >= '0' && ch <= '9') || ch == '-') {
            // Simple number - use optimized path
            int code = (int)parse_number(c);
            while (peek(c) != ')' && c->pos < c->len) advance(c);
            if (peek(c) == ')') advance(c);
            gen_exit(&c->codegen, code);
        } else {
            // Expression - compile it to rax
            compile_expr(c);
            skip_whitespace(c);
            if (peek(c) == ')') advance(c);
            gen_exit_rax(&c->codegen);
        }
        return;
    }
    
    // syscall.write(fd, buf, count)
    if (match(c, "syscall.write(")) {
        c->pos += 14;
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_mov_rdx_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);
        gen_mov_rax_imm(&c->codegen, 1);
        gen_syscall(&c->codegen);
        skip_whitespace(c); if (peek(c) == ')') advance(c);
        return;
    }
    
    // syscall.read(fd, buf, count)
    if (match(c, "syscall.read(")) {
        c->pos += 13;
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_mov_rdx_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);
        gen_mov_rax_imm(&c->codegen, 0);
        gen_syscall(&c->codegen);
        skip_whitespace(c); if (peek(c) == ')') advance(c);
        return;
    }
    
    // syscall.open(path, flags, mode)
    if (match(c, "syscall.open(")) {
        c->pos += 13;
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_mov_rdx_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);
        gen_mov_rax_imm(&c->codegen, 2);
        gen_syscall(&c->codegen);
        skip_whitespace(c); if (peek(c) == ')') advance(c);
        return;
    }
    
    // syscall.close(fd)
    if (match(c, "syscall.close(")) {
        c->pos += 14;
        compile_expr(c); gen_mov_rdi_rax(&c->codegen);
        gen_mov_rax_imm(&c->codegen, 3);
        gen_syscall(&c->codegen);
        skip_whitespace(c); if (peek(c) == ')') advance(c);
        return;
    }
    
    // syscall.mmap(addr, len, prot, flags, fd, offset)
    if (match(c, "syscall.mmap(")) {
        c->pos += 13;
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c); gen_push_rax(&c->codegen);
        skip_whitespace(c); if (peek(c) == ',') advance(c);
        compile_expr(c);
        emit_bytes(&c->codegen, (uint8_t[]){0x49, 0x89, 0xc1}, 3);  // mov r9, rax
        emit_bytes(&c->codegen, (uint8_t[]){0x41, 0x58}, 2);  // pop r8
        emit_bytes(&c->codegen, (uint8_t[]){0x41, 0x5a}, 2);  // pop r10
        gen_pop_rax(&c->codegen); gen_mov_rdx_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rsi_rax(&c->codegen);
        gen_pop_rax(&c->codegen); gen_mov_rdi_rax(&c->codegen);
        gen_mov_rax_imm(&c->codegen, 9);
        gen_syscall(&c->codegen);
        skip_whitespace(c); if (peek(c) == ')') advance(c);
        return;
    }
    
    // poke(addr, val) as statement
    if (match(c, "poke(")) {
        c->pos += 5;
        compile_expr(c);  // addr
        gen_push_rax(&c->codegen);
        skip_whitespace(c);
        if (peek(c) == ',') advance(c);
        skip_whitespace(c);
        compile_expr(c);  // val
        gen_pop_rbx(&c->codegen);
        emit_bytes(&c->codegen, (uint8_t[]){0x88, 0x03}, 2);  // mov [rbx], al
        skip_whitespace(c);
        if (peek(c) == ')') advance(c);
        return;
    }
    
    // peek(addr) as statement (result discarded)
    if (match(c, "peek(")) {
        c->pos += 5;
        compile_expr(c);  // addr
        emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0x00}, 4);  // movzx rax, byte [rax]
        skip_whitespace(c);
        if (peek(c) == ')') advance(c);
        return;
    }
    
    // getchar() / putchar() / byte() as statements
    if (match(c, "getchar()")) {
        c->pos += 9;
        gen_sub_rsp(&c->codegen, 16);
        gen_mov_rax_imm(&c->codegen, 0);
        gen_mov_rdi_imm(&c->codegen, 0);
        emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x34, 0x24}, 4);
        gen_mov_rdx_imm(&c->codegen, 1);
        gen_syscall(&c->codegen);
        emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x0f, 0xb6, 0x04, 0x24}, 5);
        gen_add_rsp(&c->codegen, 16);
        return;
    }
    
    if (match(c, "putchar(")) {
        c->pos += 8;
        compile_expr(c);
        skip_whitespace(c);
        if (peek(c) == ')') advance(c);
        gen_sub_rsp(&c->codegen, 16);
        emit_bytes(&c->codegen, (uint8_t[]){0x88, 0x04, 0x24}, 3);
        gen_mov_rax_imm(&c->codegen, 1);
        gen_mov_rdi_imm(&c->codegen, 1);
        emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x34, 0x24}, 4);
        gen_mov_rdx_imm(&c->codegen, 1);
        gen_syscall(&c->codegen);
        gen_add_rsp(&c->codegen, 16);
        return;
    }
    
    if (match(c, "byte(")) {
        c->pos += 5;
        compile_expr(c);
        skip_whitespace(c);
        if (peek(c) == ')') advance(c);
        gen_sub_rsp(&c->codegen, 16);
        emit_bytes(&c->codegen, (uint8_t[]){0x88, 0x04, 0x24}, 3);
        gen_mov_rax_imm(&c->codegen, 1);
        gen_mov_rdi_imm(&c->codegen, 1);
        emit_bytes(&c->codegen, (uint8_t[]){0x48, 0x8d, 0x34, 0x24}, 4);
        gen_mov_rdx_imm(&c->codegen, 1);
        gen_syscall(&c->codegen);
        gen_add_rsp(&c->codegen, 16);
        return;
    }
    
    // unified { } - parse and set Unified Field parameters
    if (match(c, "unified ")) {
        c->pos += 8;
        parse_unified_block(c);
        return;
    }
    if (match(c, "unified{")) {
        c->pos += 7;
        parse_unified_block(c);
        return;
    }
    
    // ═══════════════════════════════════════════════════════════════
    // Minimal universal compatibility commands (Fate adaptive)
    // ═══════════════════════════════════════════════════════════════
    
    // platform.probe - Fate probes platform
    if (match(c, "platform.probe")) {
        c->pos += 14;
        // Fate probes at runtime, just record here
        return;
    }
    
    // bridge.read - Read bridge environment
    if (match(c, "bridge.read")) {
        c->pos += 11;
        // Read from standard addresses at runtime
        return;
    }
    
    // compat.probe - Fate probes available devices
    if (match(c, "compat.probe")) {
        c->pos += 12;
        // Fate probes at runtime
        return;
    }
    
    // Other block declarations (skip)
    if (match(c, "pool ") || match(c, "fate {") ||
        match(c, "task {") || match(c, "gpu {") || match(c, "perf {") ||
        match(c, "reg {") || match(c, "sys {") || match(c, "compiler {") ||
        match(c, "collapse {") || match(c, "lib {") || match(c, "env {") ||
        match(c, "rule ") || match(c, "intent ") || match(c, "platform {") ||
        match(c, "tile {") || match(c, "codegen {") || match(c, "graphics {") ||
        match(c, "gui {") || match(c, "style {") || match(c, "layout {") ||
        match(c, "event {") || match(c, "db {") || match(c, "core {") ||
        match(c, "kernel {") || match(c, "linux {") || match(c, "macos {") ||
        match(c, "windows {") || match(c, "driver {") || match(c, "observe {") ||
        match(c, "field {") || match(c, "use ")) {
        skip_block_decl(c);
        return;
    }
    
    // otherwise
    if (match(c, "otherwise")) {
        c->pos += 9;
        skip_whitespace(c);
        if (peek(c) == '{') compile_block(c);
        return;
    }
    
    // Variable assignment or function call
    if (is_ident_start(peek(c))) {
        char* name = parse_ident(c);
        skip_whitespace(c);
        
        if (peek(c) == '=' && peek_n(c, 1) != '=') {
            advance(c);
            compile_assign(c, name);
        } else if (peek(c) == '(') {
            advance(c);
            skip_whitespace(c);
            int argc = 0;
            while (peek(c) != ')' && c->pos < c->len) {
                compile_expr(c);
                gen_push_rax(&c->codegen);
                argc++;
                skip_whitespace(c);
                if (peek(c) == ',') advance(c);
                skip_whitespace(c);
            }
            if (peek(c) == ')') advance(c);
            gen_call(&c->codegen, name);
            if (argc > 0) gen_add_rsp(&c->codegen, argc * 8);
        } else {
            skip_line(c);
        }
        free(name);
        return;
    }
    
    skip_line(c);
}

void compile_function_body(Compiler* c, Function* fn) {
    int saved_var_count = c->codegen.var_count;
    int saved_stack_size = c->codegen.stack_size;
    bool saved_in_function = c->codegen.in_function;
    c->codegen.in_function = true;  // Mark we're inside a function
    c->current_func = fn;
    
    for (int i = 0; i < fn->param_count; i++) {
        Variable* v = &c->codegen.vars[c->codegen.var_count++];
        strncpy(v->name, fn->params[i], MAX_IDENT - 1);
        v->type = VAR_INT;
        v->int_val = 0;
        v->is_param = true;
        v->is_global = false;  // Parameters are never global
        v->global_addr = 0;
        v->stack_offset = 16 + (fn->param_count - 1 - i) * 8;
    }
    
    size_t saved_pos = c->pos;
    c->pos = fn->body_pos;
    while (c->pos < fn->body_end) {
        compile_statement(c);
    }
    c->pos = saved_pos;
    
    c->codegen.var_count = saved_var_count;
    c->codegen.stack_size = saved_stack_size;
    c->codegen.in_function = saved_in_function;  // Restore in_function flag
    c->current_func = NULL;
}

void compile(Compiler* c) {
    gen_prologue(&c->codegen);
    gen_sub_rsp(&c->codegen, 512);
    
    // Initialize rule systems
    unified_init(&c->unified);
    tile_init(&c->tile, &c->unified);
    fate_init(&c->fate);
    
    // Add default four memory pools
    tile_add_pool(&c->tile, 0x10000, 0x10000, "blackhole");
    tile_add_pool(&c->tile, 0x20000, 0x10000, "meshbrain");
    tile_add_pool(&c->tile, 0x30000, 0x10000, "multinova");
    tile_add_pool(&c->tile, 0x40000, 0x10000, "baseforce");
    
    // First pass: collect function definitions
    size_t saved_pos = c->pos;
    while (c->pos < c->len) {
        skip_whitespace(c);
        if (match(c, "fn ")) {
            c->pos += 3;
            compile_fn_def(c);
        } else {
            skip_line(c);
        }
    }
    c->pos = saved_pos;
    
    int func_count = c->codegen.func_count;
    c->codegen.func_count = 0;
    
    // Second pass: compile main program code
    while (c->pos < c->len) {
        compile_statement(c);
    }
    
    c->codegen.func_count = func_count;
    
    gen_exit(&c->codegen, 0);
    
    // Third pass: generate function bodies
    for (int i = 0; i < c->codegen.func_count; i++) {
        Function* fn = &c->codegen.funcs[i];
        if (fn->body_pos > 0 && fn->body_end > fn->body_pos) {
            fn->code_offset = c->codegen.code_pos;
            add_label(&c->codegen, fn->name);
            
            gen_prologue(&c->codegen);
            gen_sub_rsp(&c->codegen, 256);
            
            compile_function_body(c, fn);
            
            gen_add_rsp(&c->codegen, 256);
            gen_pop_rbp(&c->codegen);
            emit_byte(&c->codegen, 0xc3);
        }
    }
    
    resolve_fixups(&c->codegen);
}

// ═══════════════════════════════════════════════════════════════
// Main
// ═══════════════════════════════════════════════════════════════

int main(int argc, char* argv[]) {
    printf("🌊 Wave-C %s\n", VERSION);
    printf("   Rule-Driven Compiler | Rogue Intelligence LNC.\n\n");
    
    if (argc < 2) {
        printf("Usage: %s <input.wave> [-o output] [--raw]\n\n", argv[0]);
        printf("Syntax:\n");
        printf("  out \"text\"           - 输出文本\n");
        printf("  emit \"\\xHH\"         - 输出字节\n");
        printf("  byte(N)              - 输出单个字节\n");
        printf("  getchar()            - 读取一个字符\n");
        printf("  putchar(N)           - 输出一个字符\n");
        printf("  name = expr          - 变量赋值\n");
        printf("  when cond { }        - 条件语句\n");
        printf("  loop { }             - 循环\n");
        printf("  break                - 跳出循环\n");
        printf("  fn name args { }     - 函数定义\n");
        printf("  name(args)           - 函数调用\n");
        printf("  keep                 - 事件循环\n");
        printf("  fate on/off          - 动态/静态模式\n");
        printf("  limit N              - 资源限制\n");
        printf("  -> value             - 返回值\n");
        printf("  unified { i: e: r: } - 设置统一场参数\n");
        printf("  syscall.exit(N)      - 退出程序\n");
        return 1;
    }
    
    char* input = argv[1];
    char* output = "a.out";
    bool raw_mode = false;
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) output = argv[++i];
        else if (strcmp(argv[i], "--raw") == 0) raw_mode = true;
    }
    
    FILE* f = fopen(input, "r");
    if (!f) { fprintf(stderr, "Cannot open: %s\n", input); return 1; }
    
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* source = malloc(size + 1);
    fread(source, 1, size, f);
    source[size] = 0;
    fclose(f);
    
    Compiler* compiler = malloc(sizeof(Compiler));
    if (!compiler) {
        fprintf(stderr, "Out of memory\n");
        free(source);
        return 1;
    }
    
    compiler_init(compiler, source);
    compile(compiler);
    
    if (raw_mode) {
        write_raw(&compiler->codegen, output);
        printf("Generated raw: %s (%zu bytes)\n", output, compiler->codegen.code_pos);
    } else {
        write_elf(&compiler->codegen, output);
        printf("Generated: %s\n", output);
        printf("   Code: %zu bytes\n", compiler->codegen.code_pos);
    }
    
    printf("   Variables: %d | Functions: %d\n", 
           compiler->codegen.var_count, compiler->codegen.func_count);
    printf("   Unified: i=%.2f e=%.2f r=%.2f\n",
           compiler->unified.i, compiler->unified.e, compiler->unified.r);
    printf("   Tile: %zu bytes (%d pools)\n",
           tile_total_used(&compiler->tile), compiler->tile.pool_count);
    printf("   Fate: %s\n", compiler->fate.on ? "dynamic" : "static");
    printf("   Platform: id=%d syscall_base=0x%lx\n", 
           compiler->platform.id, compiler->platform.syscall_base);
    
    compiler_free(compiler);
    free(compiler);
    free(source);
    
    return 0;
}
