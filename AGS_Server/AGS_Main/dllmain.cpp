#include "Main.h"
#include "Sigs.h"
#include "minhook/MinHook.h"
#pragma comment(lib,"minhook/minhook.lib")
void Init() {
    Discord::StartRPC();
    AllocConsole();
    FILE* pFile;
    freopen_s(&pFile, ("CONOUT$"), "w", stdout);
#ifdef UE4_20
    GetFirstPlayerController = decltype(GetFirstPlayerController)(FindPattern(UE4_20_GFPC));
    uintptr_t GObjsAddr = FindPattern(UE4_20_GObjects);
    auto ObjectsOffset = *(int32_t*)(GObjsAddr + 3);
    GObjsAddr = GObjsAddr + 7 + ObjectsOffset;
    GObjs = reinterpret_cast<UObjectArray*>(GObjsAddr);
    GWorld = *reinterpret_cast<UObject**>(FindPattern(UE4_20_GWorld, true, 3));
    FNameToString = decltype(FNameToString)(FindPattern(UE4_20_FNTS));
    FnFree = decltype(FnFree)(FindPattern(UE4_20_Free));
    SpawnActor = decltype(SpawnActor)(FindPattern(UE4_20_SpawnActor));
    UObject* FEngine = FindObject("FortEngine_");
    void** Engine = *reinterpret_cast<void***>(FEngine);
    auto PEAddr = (uintptr_t)Engine[64];
#elif UE4_16
    GetFirstPlayerController = decltype(GetFirstPlayerController)(FindPattern(UE4_16_GFPC));
    uintptr_t GObjsAddr = FindPattern(UE4_16_GObjects);
    auto ObjectsOffset = *(int32_t*)(GObjsAddr + 3);
    GObjsAddr = GObjsAddr + 7 + ObjectsOffset;
    GObjs = new UObjectArray((reinterpret_cast<OAP*>(GObjsAddr)->Objects));
    GWorld = *reinterpret_cast<UObject**>(FindPattern(UE4_16_GWorld, true, 3));
    FNameToString = decltype(FNameToString)(FindPattern(UE4_16_FNTS));
    FnFree = decltype(FnFree)(FindPattern(UE4_16_Free));
    SpawnActor = decltype(SpawnActor)(FindPattern(UE4_16_SpawnActor));
    auto PEAddr = FindPattern("40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 48 63 41 0C");
#elif UE4_23
    GetFirstPlayerController = decltype(GetFirstPlayerController)(FindPattern(UE4_23_GFPC));
    uintptr_t GObjsAddr = FindPattern(UE4_23_GObjects, true, 10);
    GObjs = reinterpret_cast<GObjects*>(GObjsAddr);
    GWorld = *reinterpret_cast<UObject**>(FindPattern(UE4_23_GWorld, true, 3));
    FNameToString = decltype(FNameToString)(FindPattern(UE4_23_FNTS));
    FnFree = decltype(FnFree)(FindPattern(UE4_23_Free));
    SpawnActor = decltype(SpawnActor)(FindPattern(UE4_23_SpawnActor));
    uintptr_t PEAddr = FindPattern(UE4_23_ProcessEvent);
    FStringToName = decltype(FStringToName)(FindPattern(UE4_23_FSTN));
#endif
    ProcessEventOG = decltype(ProcessEventOG)(PEAddr);
    MH_Initialize();
    MH_CreateHook((LPVOID)PEAddr, ProcessEventHook, (void**)&ProcessEventOG);
    MH_EnableHook((LPVOID)PEAddr);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

