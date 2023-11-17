// modified from https://github.com/RicBent/codedx/blob/master/source/fs2sd.cpp

#include "nn/result.h"
#include "nn/fs.h"
#include "nn/util.h"
#include "string.h"
#include "lib.hpp"

HOOK_DEFINE_TRAMPOLINE(nn_fs_OpenFile_hook) {
    // opens files in sd:/totk/contents/... (don't include "romfs" in path)
    // if they exist, otherwise calls normally
    static nn::Result Callback(nn::fs::FileHandle* out, const char* path, s32 mode) {
        nn::Result rc;
        static char redirectPath[nn::fs::PathLengthMax + 1];

        enum SdMountStatus { SdNotMounted = 0, SdMounted = 1, SdMountFailed = 2 };
        static SdMountStatus sdMountStatus = SdNotMounted;

        char totkPath[] = "sd:/totk";
        char savePath[] = "sd:/totk/savedata.dat";
        if (sdMountStatus == SdNotMounted) {
            nn::Result rc = nn::fs::MountSdCard("sd");

            if (rc.isSuccess()) {
                sdMountStatus = SdMounted;
                nn::fs::CreateDirectory(totkPath);
                nn::fs::CreateFile(savePath, 0);
            } else
                sdMountStatus = SdMountFailed;
        }

        if (sdMountStatus != SdMounted)
            return nn::fs::OpenFile(out, path, mode);

        if (strncmp(path, "content:/", 9) == 0) {
            nn::util::SNPrintf(redirectPath, nn::fs::PathLengthMax, "%s/content/%s", totkPath, path + 9);

            rc = nn::fs::OpenFile(out, redirectPath, mode);
            if (rc.isSuccess())
                return rc;
        }

        else if (strncmp(path, "save:/rp_savedata.dat", 21) == 0) {
            rc = nn::fs::OpenFile(out, savePath, mode);
            if (rc.isSuccess())
                return rc;
        }

        return Orig(out, path, mode);
    }
};