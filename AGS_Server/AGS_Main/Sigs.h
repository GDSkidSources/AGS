#pragma once
#include "framework.h"

//4.16

//Base
#define UE4_16_GObjects "48 8D 0D ? ? ? ? 89 13 E8 ? ? ? ? 89 43 04 48 8B 5C 24 ?" //3
#define UE4_16_FNTS "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9 75 43"
#define UE4_16_GFPC "83 B9 ? ? ? ? ? 7E ? 48 8B 89 ? ? ? ? E9"
#define UE4_16_Free "48 85 C9 74 2E 53 48 83 EC 20 48 8B D9 48 8B 0D ? ? ? ?"
#define UE4_16_GWorld "48 8B 05 ? ? ? ? 4C 8B C3 0F 1F 40 00" //3
#define UE4_16_SpawnActor "40 53 56 57 48 83 EC 70 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 28 1D ? ? ? ?"
//Beacon
#define UE4_16_NAC "48 83 EC 48 48 8B 41 10 48 83 78 ? ?"
#define UE4_16_AOB_NCM "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 33 FF"
#define UE4_16_InitHost "48 8B C4 48 81 EC ? ? ? ? 48 89 58 18 4C 8D 05 ? ? ? ?"
//Other MP Stuff

#define UE4_16_WelcomePlayer "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20"
#define UE4_16_SPA "44 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ?"
#define UE4_16_WorldNCM "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6"
#define UE4_16_CreateChannel "40 56 57 41 54 41 55 41 57 48 83 EC 60 48 8B 01 41 8B F9 45 0F B6 E0"
#define UE4_16_SetChannelActor "4C 8B DC 55 53 57 41 54 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 45 33 E4"
#define UE4_16_ReplicateActor "40 55 53 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8D 59 68 4C 8B F1"

//4.20
//Base
#define UE4_20_GObjects "48 8B 05 ? ? ? ? 48 8D 1C C8 81 4B ? ? ? ? ? 49 63 76 30" //3
#define UE4_20_FNTS "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9"
#define UE4_20_GFPC "83 B9 ? ? ? ? ? 7E ? 48 8B 89 ? ? ? ? E9"
#define UE4_20_Free "48 85 C9 74 1D 4C 8B 05 ? ? ? ? 4D 85 C0"
#define UE4_20_GWorld "48 8B 1D ? ? ? ? 48 85 DB 74 3B 41" //3
#define UE4_20_SpawnActor "40 53 56 57 48 83 EC 70 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 28 1D ? ? ? ? 0F 57 D2 48 8B B4 24 ? ? ? ? 0F 28 CB"
//Beacon
#define UE4_20_NAC "48 83 EC 48 48 8B 41 10 48 83 78 ? ?"
#define UE4_20_AOB_NCM "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 33 FF 48 89 4C 24 ? 89 7C 24 60 49 8B F1"
#define UE4_20_InitHost "48 8B C4 48 81 EC ? ? ? ? 48 89 58 18 4C 8D 05 ? ? ? ? 48 8B D9 48 89 78 F8 48 8D 48 88 45 33 C9"
//Other MP Stuff

#define UE4_20_FindChannel "48 89 5C 24 ? 48 89 7C 24 ? 8B 81 ? ? ? ? 33 FF 4C 8B D1 48 63 1A 4C 63 5A 04"
#define UE4_20_PostLogin "48 89 74 24 ? 41 56 48 83 EC 30 48 8B 01"
#define UE4_20_ReplicateFunction "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 5D 7F 48 8B F9 48 8B 89 ? ? ? ? 4D 8B E1 48 8B 75 77 4D 8B E8"
#define UE4_20_WelcomePlayer "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20"
#define UE4_20_SPA "44 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 33 F6 48 8D 05 ? ? ? ? 89 75 67 4D 8B E9"
#define UE4_20_WorldNCM "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6 49 8B D9"
#define UE4_20_CreateChannel "40 56 57 41 54 41 55 41 57 48 83 EC 60 48 8B 01 41 8B F9 45 0F B6 E0 4C 63 FA 48 8B F1 FF 90 ? ? ? ? 45 33 ED 83 FF FF 0F 85 ? ? ? ? 4C 63 8E ? ? ? ? 41 83 FF 01"
#define UE4_20_SetChannelActor "48 8B C4 55 53 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 10 48 8B D9 48 89 78 18 48 8D 35 ? ? ? ?"
#define UE4_20_ReplicateActor "48 8B C4 48 89 48 08 55 53 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 A8 0F 29 78 98 48 89 70 E8 4C 89 60 D8 4C 8D 61 68"

#define V2_5_SetChannelActor "48 8B C4 55 53 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 E8 48 8B D9"
#define V2_5_ReplicateActor "48 8B C4 48 89 48 08 55 53 48 8D A8 ? ? ? ?"

//Client Stuff
#define UE4_20_SendClientAdjustment "40 53 48 83 EC 20 48 8B 99 ? ? ? ? 48 39 99 ? ? ? ? 74 0A"