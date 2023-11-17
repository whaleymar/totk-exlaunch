#include "lib.hpp"
#include <diag/debug.hpp>
#include "setting.hpp"

#include "nn/err.h"
#include "nn/fs.h"
#include "logger/logger.hpp"
#include "sd/fs2sd.cpp"

HOOK_DEFINE_TRAMPOLINE(MainInitHook) { static void Callback(); };

void MainInitHook::Callback() {
    Orig();

    R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd").value);
}

extern "C" void exl_main(void* x0, void* x1) {
    exl::hook::Initialize();

    // using Patcher = exl::patch::CodePatcher;
    // using namespace exl::patch::inst;

    #ifdef LOGGER_IP
    // Logger::instance().init(LOGGER_IP, 3080);
    #endif

    nn_fs_OpenFile_hook::InstallAtSymbol("_ZN2nn2fs8OpenFileEPNS0_10FileHandleEPKci");

    MainInitHook::InstallAtSymbol("nnMain");
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}