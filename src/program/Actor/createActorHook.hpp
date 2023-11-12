#pragma once
#include "lib.hpp"
#include "types.h"
#include <sead/math/seadVector.h>

namespace engine {
namespace actor {

class ActorInstanceMgr;

}
}

namespace game {
namespace actor {

class ActorInfoLink;
class ActorObserver;
}
}

HOOK_DEFINE_TRAMPOLINE(CreateActorHook) { static bool Callback(engine::actor::ActorInstanceMgr* actorInstanceMgr, char** actorName, sead::Vector3f* position, 
                                                               void* rotationStruct, s32 someInt, game::actor::ActorInfoLink* actorInfoLink, game::actor::ActorObserver* actorObserver,
                                                               void* someFnPtr, bool someBool, s32 unused, s32* someEnumPtr, game::actor::ActorInfoLink** destActorInfoLink); };