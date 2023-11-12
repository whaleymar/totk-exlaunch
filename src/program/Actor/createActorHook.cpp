#include "createActorHook.hpp"

bool CreateActorHook::Callback(engine::actor::ActorInstanceMgr* actorInstanceMgr, char** actorName, sead::Vector3f* position, 
    void* rotationStruct, s32 someInt, game::actor::ActorInfoLink* actorInfoLink, game::actor::ActorObserver* actorObserver,
    void* someFnPtr, bool someBool, s32 unused, s32* someEnumPtr, game::actor::ActorInfoLink** destActorInfoLink) {

    char* newActor = "Enemy_Zonau_Golem_Junior";
    if (strstr(*actorName, "Enemy_")) {
        strcpy(*actorName, newActor);
    }

    return Orig(actorInstanceMgr, actorName, position, rotationStruct, someInt, actorInfoLink, actorObserver, someFnPtr, someBool, unused, someEnumPtr, destActorInfoLink);
}