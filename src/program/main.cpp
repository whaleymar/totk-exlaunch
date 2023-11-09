#include "lib.hpp"
#include <diag/debug.hpp>
#include "setting.hpp"

#include "nn/err.h"
#include "nn/fs.h"

#ifdef LOGGER_IP
#include "log/logger.h"
#include "socket/Socket.h"
static Socket gSocket {};
#endif

HOOK_DEFINE_TRAMPOLINE(MainInitHook) { static void Callback(); };

void MainInitHook::Callback() {
    Orig();

    #ifdef LOGGER_IP
    if (gSocket.init(LOGGER_IP, LOGGER_PORT).isFailure()) {
        Logger::log("Failed to connect to logging server!\n");
    } else {
        Logger::addListener([](const char* message) {
            gSocket.sendMessage(message);
        });
        Logger::log("Connected to logging server!\n");
    }
    Logger::log(EXL_MODULE_NAME " Loaded!\n");
    #endif

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