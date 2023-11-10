#pragma once

#include "lib.hpp"

namespace UnityEngine {
    struct Vector3 {
        struct Fields {
            float x;
            float y;
            float z;
        } fields;
    };
}

typedef void(*Il2CppMethodPointer)();

struct Il2CppClass;

struct Il2CppType {
    void* data;
    unsigned int bits;
};

struct MethodInfo {
    Il2CppMethodPointer methodPointer;
    void* invoker_method;
    const char* name;
    Il2CppClass* klass;
    const Il2CppType* return_type;
    const void* parameters;
    union {
        const void* rgctx_data;
        const void* methodDefinition;
    };
    union {
        const void* method;
        const void* genericMethod;
    };
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;

    MethodInfo* copyWith(Il2CppMethodPointer method) {
        auto m = new MethodInfo;
        memcpy(m, this, sizeof(MethodInfo));
        m->methodPointer = method;
        return m;
    }
};

HOOK_DEFINE_TRAMPOLINE(setVelocityInjected) { 
    static void Callback(void* __this, UnityEngine::Vector3* vec, MethodInfo* method) {
        float multiplier = 10.0;

        vec->fields.x = vec->fields.x*multiplier;
        vec->fields.y = vec->fields.y*multiplier;
        vec->fields.z = vec->fields.z*multiplier;

        Orig(__this, vec, method);
    }
};

HOOK_DEFINE_REPLACE(UnityRandomRange) {
    static u32 Callback(u32 min, u32 max, MethodInfo* method) {
        return 8;
    }
};