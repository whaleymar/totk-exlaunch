#include "lib.hpp"
#include <diag/debug.hpp>

#include "nn/err.h"
#include "nn/fs.h"

HOOK_DEFINE_TRAMPOLINE(MainInitHook) { static void Callback(); };

void MainInitHook::Callback() {
    Orig();

    R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd").value);
}

extern "C" void exl_main(void* x0, void* x1) {
    exl::hook::Initialize();

    using Patcher = exl::patch::CodePatcher;
    using namespace exl::patch::inst;

    MainInitHook::InstallAtSymbol("nnMain");
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}