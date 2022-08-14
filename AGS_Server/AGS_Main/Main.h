#pragma once
#include "Discord.h"
#include "UE4.h"
#include "Sigs.h"
#include "minhook/MinHook.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <detours.h>
bool InGame = false;
bool StartedMatch = false;
bool IsGSRep = false;
int Connections = 0;
bool Started = false;
bool ServerStarted = false;
UObject* BeaconHost;
UNetDriver* NetDriver;
CheatManager* GCheatManager;
UObject* GPlayerController;
//#define Use_GMB
//#define UE4_20
#define LOG(STR)(std::cout << "\n[AGS]: " << STR << std::endl)

void(__fastcall* ReplicateFunctionInternal)(UObject* ND, UObject* Object, UObject* Function, void* Params, void* OutParams, void* Frame, UObject* SubObj);
void(__fastcall* UWorld_NotifyControlMessage)(UObject* World, UObject* NetConnection, uint8_t a3, void* a4);
inline static UObject* (__fastcall* SpawnPlayActor)(UObject* World, UObject* Connection, ENetRole NetRole, FURL Idk, void* Idk2, FString& Idk3, uint8_t Idk4);
inline static UObject* (__fastcall* CreateChannel)(UObject*, int, bool, int);
inline static void(__fastcall* CallPreRep)(UObject* Actor, UObject* ND);
inline static void(__fastcall* SendClientAdjustment)(UObject* Controller);
inline static __int64(__fastcall* ReplicateActorInternal)(UObject* This);
inline static __int64(__fastcall* SetChannelActor)(UObject* This, UObject* Actor);
inline static __int64(__fastcall* WelcomePlayer)(UObject* This, UObject* NetConnection);
inline static __int64(__fastcall* NotifyAcceptingConnection)(UObject* Target);
inline static __int64(__fastcall* PostLogin)(UObject*, UObject* NewPlayerController);
inline static bool(__fastcall* InitHost)(UObject* Target);
//inline static bool(__fastcall* ReplicateSubObjects)(UObject* Target, UObject* Channel, void* Bunch, FReplicationFlags RepFlags);

//New
inline static __int64 (*ServerReplicateActors)(UObject* NetDriver, float Time);

UObject* GS = nullptr;

void Update() {
#ifdef UE4_20
	GWorld = *reinterpret_cast<UObject**>(FindPattern(UE4_20_GWorld, true, 3));
#elif UE4_16
	GWorld = *reinterpret_cast<UObject**>(FindPattern(UE4_16_GWorld, true, 3));
#elif UE4_23
	GWorld = *reinterpret_cast<UObject**>(FindPattern(UE4_23_GWorld, true, 3));
#endif
	GPlayerController = GetFirstPlayerController(GWorld);
}

namespace Functions {
	namespace Actor {
		UObject* OnRep_Owner;
		UObject* SetOwner;
		UObject* OnRep_AttachmentReplication;
	}
	namespace Pawn {
		UObject* OnRep_Controller;
		UObject* OnRep_PlayerState;

	}
	namespace PlayerControllers {
		UObject* OnRep_Pawn;
		UObject* ClientForceProfileQuery;
		UObject* ServerSetClientHasFinishedLoading;
		UObject* ServerClientPawnLoaded;
		UObject* OnRep_bHasServerFinishedLoading;
		UObject* OnRep_PlayerState;
		UObject* OnRep_QuickBar;
	}
	namespace PlayerState {
		UObject* OnRep_PlayerTeam;
		UObject* OnRep_SquadId;
		UObject* OnRep_CharacterParts;
		UObject* OnRep_PlayerName;
	}
}

namespace Offsets {
	namespace Actor {
		int Owner = 0;
		int Role = 0;
		int RemoteRole = 0;
	}
	namespace Player {
		int PlayerController = 0;
	}
	namespace Pawn {
		int Controller = 0;
		int PlayerState = 0;
		int bIsPlayerPawnReady = 0;
		int bReplicateMovement = 0;
	}
	namespace Controller {
		int Pawn = 0;
		int AcknowledgedPawn = 0;
		int PlayerState = 0;
		int bClientPawnIsLoaded = 0;
		int bHasClientFinishedLoading = 0;
		int bHasServerFinishedLoading = 0;
		int bReadyToStartMatch = 0;
	}
	namespace PlayerState {
		int bHasFinishedLoading = 0;
		int TeamIndex = 0;
		int ReadyCheckState = 0;
		int CharacterParts = 0;
	}
}

void InitPreDefs() {
	LOG("Getting Functions!");
	//Funcs
	Functions::Actor::OnRep_Owner = FindObjectShort("OnRep_Owner");
	Functions::Actor::OnRep_AttachmentReplication = FindObjectShort("OnRep_AttachmentReplication");
	Functions::Actor::SetOwner = FindObject("Function /Script/Engine.Actor.SetOwner");
	Functions::Pawn::OnRep_Controller = FindObjectShort("OnRep_Controller");
	Functions::Pawn::OnRep_PlayerState = FindObject("Function /Script/Engine.Pawn.OnRep_PlayerState");
	Functions::PlayerControllers::ClientForceProfileQuery = FindObjectShort("ClientForceProfileQuery");
	Functions::PlayerControllers::OnRep_bHasServerFinishedLoading = FindObjectShort("OnRep_bHasServerFinishedLoading");
	Functions::PlayerControllers::OnRep_Pawn = FindObjectShort("OnRep_Pawn");
	Functions::PlayerControllers::OnRep_PlayerState = FindObject("Function /Script/Engine.Controller.OnRep_PlayerState");
	Functions::PlayerControllers::OnRep_QuickBar = FindObjectShort("OnRep_QuickBar");
	Functions::PlayerControllers::ServerClientPawnLoaded = FindObjectShort("ServerClientPawnLoaded");
	Functions::PlayerControllers::ServerSetClientHasFinishedLoading = FindObjectShort("ServerSetClientHasFinishedLoading");
	Functions::PlayerState::OnRep_CharacterParts = FindObjectShort("OnRep_CharacterParts");
	Functions::PlayerState::OnRep_PlayerName = FindObjectShort("OnRep_PlayerName");
	Functions::PlayerState::OnRep_PlayerTeam = FindObjectShort("OnRep_PlayerTeam");
	Functions::PlayerState::OnRep_SquadId = FindObjectShort("OnRep_SquadId");
	//Offsets
	LOG("Getting Offsets!");
	Offsets::Actor::Owner = FindOffsetC1("ObjectProperty /Script/Engine.Actor.Owner");
	Offsets::Actor::RemoteRole = FindOffsetC1("ByteProperty /Script/Engine.Actor.RemoteRole");
	Offsets::Actor::Role = FindOffsetC1("ByteProperty /Script/Engine.Actor.Role");
	Offsets::Controller::AcknowledgedPawn = FindOffsetC1("ObjectProperty /Script/Engine.PlayerController.AcknowledgedPawn");
	Offsets::Controller::bClientPawnIsLoaded = FindOffsetC1("BoolProperty /Script/FortniteGame.FortPlayerController.bClientPawnIsLoaded");
	Offsets::Controller::bHasClientFinishedLoading = FindOffsetC1("BoolProperty /Script/FortniteGame.FortPlayerController.bHasClientFinishedLoading");
	Offsets::Controller::bHasServerFinishedLoading = FindOffsetC1("BoolProperty /Script/FortniteGame.FortPlayerController.bHasServerFinishedLoading");
	Offsets::Controller::bReadyToStartMatch = FindOffsetC1("BoolProperty /Script/FortniteGame.FortPlayerController.bReadyToStartMatch");
	Offsets::Controller::Pawn = FindOffsetC1("ObjectProperty /Script/Engine.Controller.Pawn");
	Offsets::Controller::PlayerState = FindOffsetC1("ObjectProperty /Script/Engine.Controller.PlayerState");
	Offsets::Pawn::bIsPlayerPawnReady = FindOffsetC1("BoolProperty /Script/FortniteGame.FortPlayerPawnAthena.bIsPlayerPawnReady");
	Offsets::Pawn::bReplicateMovement = FindOffsetC1("BoolProperty /Script/Engine.Actor.bReplicateMovement");
	Offsets::Pawn::Controller = FindOffsetC1("ObjectProperty /Script/Engine.Pawn.Controller");
	Offsets::Pawn::PlayerState = FindOffsetC1("ObjectProperty /Script/Engine.Pawn.PlayerState");
	Offsets::Player::PlayerController = FindOffsetC1("ObjectProperty /Script/Engine.Player.PlayerController");
	Offsets::PlayerState::bHasFinishedLoading = FindOffsetC1("BoolProperty /Script/FortniteGame.FortPlayerState.bHasStartedPlaying");
	Offsets::PlayerState::CharacterParts = FindOffsetC1("ObjectProperty /Script/FortniteGame.FortPlayerState.CharacterParts");
	Offsets::PlayerState::ReadyCheckState = FindOffsetC1("EnumProperty /Script/FortniteGame.FortPlayerState.ReadyCheckState");
	Offsets::PlayerState::TeamIndex = FindOffsetC1("ByteProperty /Script/FortniteGame.FortPlayerStateAthena.TeamIndex");
}

namespace Server {
	uintptr_t ReplicatesOffset = 0;
	uintptr_t AlwaysRelvOffset = 0;
	uintptr_t NetDormOffset = 0;
	uintptr_t NetSetupOffset = 0;
	uintptr_t AC_ActorOffset = 0;
	uintptr_t AC_ChannelOffset = 0;

	namespace SGlobals {

	}

	int NumPlayers = 0;
	std::vector<std::string> ClosedChannelActorNames;
	uintptr_t OC_Offset = 0;
	UObject* FindChannel(UObject* Actor, UObject* Connection) {
		if (Actor->IsValid()) {
			TArray<UObject*>* OpenChannels = reinterpret_cast<TArray<UObject*>*>(__int64(Connection) + __int64(OC_Offset));
			for (auto i = 0; i < OpenChannels->Num(); i++) {
				UObject* Channel = OpenChannels->Data[i];
				UObject* CActor = *reinterpret_cast<UObject**>(__int64(Channel) + AC_ActorOffset);
				if (CActor->IsValid()) {
					if (CActor->GetName() == Actor->GetName()) {
						return Channel;
					}
				}
			}
		}
		LOG("FindChannel: Failed to Find Channel...");
		return nullptr;
	}

	void ReplicateProps() {
		LOG("Replicating Properties with Replication Frame: " + std::to_string(NetDriver->ReplicationFrame++));
	}

	__int64 PostLogin_Hook(UObject* GM, UObject* PC) {
		__int64 Ret = PostLogin(GM, PC);
		ReplicateProps();
		return Ret;
	}

	void ReplicateFunction(UObject* Object, UObject* Function, void* Params = nullptr) {
		LOG("Replicating Function: " + Function->GetName());
		ReplicateFunctionInternal(NetDriver, Object, Function, Params, nullptr, nullptr, nullptr);
	}

	void ReplicateActor(UObject* Actor, UObject* Connection) {
		if (Actor->IsValid() && Connection->IsValid()) {
			std::string ActorName = Actor->GetName();
			LOG("Replicating: " + ActorName);
			auto Channel = FindChannel(Actor, Connection);
			if (Channel == nullptr)
			{
#ifdef UE4_20
				Channel = CreateChannel(Connection, 2, true, -1);
#elif UE4_16
				Channel = CreateChannel(Connection, 2, true, -1);
#elif UE4_23 
				FName ChannelName;
				FString* CHNameS = new FString(L"Actor");
				FStringToName(CHNameS, ChannelName);
				Channel = CreateChannelNew(Connection, ChannelName, EChannelCreateFlags::OpenedLocally, -1);
#endif
				SetChannelActor(Channel, Actor);
				*reinterpret_cast<UObject**>(__int64(Channel) + AC_ChannelOffset) = Connection;
			}
			ReplicateActorInternal(Channel);
			LOG("Replicated " + ActorName);
		}
		else {
			LOG("ReplicateActor: Actor or Channel was NULL!");
		}
	}

	namespace Game {
		void ServerChoosePart(UObject* TargetPawn, UObject* Part, EFortCustomPartType Type) {
			struct
			{
				TEnumAsByte<EFortCustomPartType> Type;
				UObject* ChosenCharacterPart;
			} Params;
			Params.Type = Type;
			Params.ChosenCharacterPart = Part;
			ProcessEventOG(TargetPawn, FindObject("Function /Script/FortniteGame.FortPlayerPawn.ServerChoosePart"), &Params);
		}

		void KickPlayer(UObject* TargetPC, FString Reason) {
			ProcessEventOG(TargetPC, FindObject("Function /Script/Engine.PlayerController.ClientReturnToMainMenu", true), &Reason);
		}
	}


	uintptr_t ClientConnectionsOffset;
	TArray<UObject*>* Objects;
	void __fastcall ReplicateAllActors(UObject* Connection) {
		Objects = FindAllObjects();
		for (int i = 0; i < Objects->Num(); i++) {
			UObject* Actor = Objects->Data[i];
			//bool Replicates = *reinterpret_cast<bool*>(__int64(Actor) + __int64(ReplicatesOffset));
			ReplicateActor(Actor, Connection);
		}
	}

	int AOB_NAC(UObject* Target) {
		LOG("Accepting Client Connection...");
		return 1;
	}

	void __fastcall AOB_NCM_Hook(UObject* Beacon, UObject* Connection, uint8_t Idk, void* Idk2) {
		LOG("NotifyControlMessage Called!");
		//Update();
		if (std::to_string(Idk) == "15") {
			return;
		}
		if (std::to_string(Idk) == "4") {
			*reinterpret_cast<int*>(__int64(Connection) + __int64(FindOffsetC1("IntProperty /Script/Engine.Player.CurrentNetSpeed"))) = 30000;
			return;
		}
		return UWorld_NotifyControlMessage(GWorld, Connection, Idk, Idk2);
	}

	__int64 __fastcall WelcomePlayer_Hook(UObject*, UObject* Connection) {
		LOG("Welcoming New Player!");
		NumPlayers++;
		return WelcomePlayer(GWorld, Connection);
	}

	UObject* SPA_Hook(UObject*, UObject* Connection, ENetRole NetRole, FURL Idk, void* Idk2, FString& Idk3, uint8_t Idk4) {
		ReplicateProps();
		Update();
		GS = *reinterpret_cast<UObject**>(__int64(GWorld) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.World.GameState")));
		UObject* GM = *reinterpret_cast<UObject**>(__int64(GWorld) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.World.AuthorityGameMode")));
		ReplicateActor(GS, Connection);
		UObject* CurrentLevel = *reinterpret_cast<UObject**>(__int64(GWorld) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.World.CurrentLevel")));
		UObject* WorldSettings = *reinterpret_cast<UObject**>(__int64(CurrentLevel) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.Level.WorldSettings")));
		ReplicateActor(WorldSettings, Connection);
		UObject* FTODM = *reinterpret_cast<UObject**>(__int64(WorldSettings) + __int64(FindOffsetC1("ObjectProperty /Script/FortniteGame.FortWorldSettings.TimeOfDayManager")));
		ReplicateActor(FTODM, Connection);
		LOG("Spawning PlayActor!");
		UObject* NPC = SpawnPlayActor(GWorld, Connection, NetRole, Idk, Idk2, Idk3, Idk4);
		UObject* NPawn = SpawnActor(GWorld, FindObject("BlueprintGeneratedClass /Game/Athena/PlayerPawn_Athena.PlayerPawn_Athena_C"), new FVector(1, 1, 1), {}, {});
		UObject* NPS = *reinterpret_cast<UObject**> (__int64(NPC) + FindOffsetC1("ObjectProperty /Script/Engine.Controller.PlayerState"));
		/*UObject* NPC = SpawnActor(GWorld, FindObject("BlueprintGeneratedClass /Game/Athena/Athena_PlayerController.Athena_PlayerController_C"), {}, {}, {});
		UObject* NPawn = SpawnActor(GWorld, FindObject("BlueprintGeneratedClass /Game/Athena/PlayerPawn_Athena.PlayerPawn_Athena_C"), new FVector(1, 1, 1), {}, {});
		UObject* NPS = *reinterpret_cast<UObject**> (__int64(NPC) + FindOffsetC1("ObjectProperty /Script/Engine.Controller.PlayerState"));*/
		LOG("Setting up Player!");
		*reinterpret_cast<UObject**> (__int64(NPC) + FindOffsetC1("ObjectProperty /Script/Engine.Controller.Pawn")) = NPawn;
		ReplicateActor(NPC, Connection);
		ReplicateActor(NPawn, Connection);
		ReplicateActor(NPS, Connection);
		*reinterpret_cast<UObject**>(__int64(NPC) + Offsets::Actor::Owner) = Connection;
		ProcessEventOG(NPC, Functions::Actor::OnRep_Owner, nullptr);
		*reinterpret_cast<UObject**>(__int64(NPawn) + Offsets::Pawn::PlayerState) = NPS;
		ReplicateFunction(NPawn, Functions::Pawn::OnRep_PlayerState, nullptr);
		*reinterpret_cast<UObject**>(__int64(NPawn) + Offsets::Actor::Owner) = NPC;
		ReplicateFunction(NPawn, Functions::Actor::OnRep_Owner, nullptr);
		//ReplicateFunction(NPC, FindObject("Function /Script/Engine.Controller.Possess"), &NPawn);
		UObject* Mesh = *reinterpret_cast<UObject**>(__int64(NPawn) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.Character.Mesh")));
		UObject* NewMesh = FindObject("SkeletalMesh /Game/Characters/Survivors/Female/Small/F_SML_Starter_01/Meshes/F_SML_Starter_Epic.F_SML_Starter_Epic");
		ReplicateFunction(Mesh, FindObject("Function /Script/Engine.SkinnedMeshComponent.SetSkeletalMesh"), &NewMesh);
		Server::Game::ServerChoosePart(NPawn, FindObject("CustomCharacterPart /Game/Characters/CharacterParts/Female/Medium/Bodies/F_Med_Soldier_01.F_Med_Soldier_01"), EFortCustomPartType::Body);
		Server::Game::ServerChoosePart(NPawn, FindObject("CustomCharacterPart /Game/Characters/CharacterParts/Female/Medium/Heads/F_Med_Head1.F_Med_Head1"), EFortCustomPartType::Head);
		bool Yes = true;
		ReplicateFunction(NPC, Functions::PlayerControllers::ServerSetClientHasFinishedLoading, &Yes);
		ReplicateFunction(NPC, Functions::PlayerControllers::ServerClientPawnLoaded, &Yes);
		*reinterpret_cast<bool*>(__int64(NPC) + Offsets::Controller::bClientPawnIsLoaded) = Yes;
		*reinterpret_cast<bool*>(__int64(NPC) + Offsets::Controller::bHasClientFinishedLoading) = Yes;
		*reinterpret_cast<bool*>(__int64(NPC) + Offsets::Controller::bHasServerFinishedLoading) = Yes;
		*reinterpret_cast<bool*>(__int64(NPC) + Offsets::Controller::bReadyToStartMatch) = Yes;
		ReplicateFunction(NPC, Functions::PlayerControllers::OnRep_bHasServerFinishedLoading, nullptr);
		*reinterpret_cast<bool*>(__int64(NPawn) + Offsets::Pawn::bIsPlayerPawnReady) = Yes;
		*reinterpret_cast<bool*>(__int64(NPawn) + Offsets::Pawn::bReplicateMovement) = Yes;
		*reinterpret_cast<bool*>(__int64(NPS) + Offsets::PlayerState::bHasFinishedLoading) = Yes;
		*reinterpret_cast<bool*>(__int64(NPS) + Offsets::PlayerState::ReadyCheckState) = 1;
		ReplicateFunction(NPS, Functions::PlayerState::OnRep_SquadId, nullptr);
		ReplicateFunction(NPS, Functions::PlayerState::OnRep_PlayerTeam, nullptr);
		ReplicateFunction(NPS, Functions::PlayerState::OnRep_PlayerName, nullptr);
		return NPC;
	}


	void ServerThread() {
		OC_Offset = __int64(FindOffsetC1("ArrayProperty /Script/Engine.NetConnection.OpenChannels"));
		AC_ActorsOffset = __int64(FindOffsetC1("ArrayProperty /Script/Engine.LevelActorContainer.Actors"));
		ClientConnectionsOffset = __int64(FindOffsetC1("ArrayProperty /Script/Engine.NetDriver.ClientConnections"));
		ServerStarted = true;
		while (true)
		{
			if (Connections != 0) {
				TArray<UObject*> Objects = *reinterpret_cast<TArray<UObject*>*>(__int64(FindObject("LevelActorContainer /Game/Athena/Maps/Athena_Faceoff.Athena_Faceoff.PersistentLevel.ActorCluster")) + __int64(FindOffsetC1("ArrayProperty /Script/Engine.LevelActorContainer.Actors")));
				TArray<UObject*> Clients = *reinterpret_cast<TArray<UObject*>*>(__int64(NetDriver) + __int64(FindOffsetC1("ArrayProperty /Script/Engine.NetDriver.ClientConnections")));
				for (int z = 0; z < Clients.Num(); z++) {
					UObject* ClientBOI = Clients[z];
					for (int i = 0; i < Objects.Num(); i++) {
						UObject* Actor = Objects[i];
						bool BReplicates = *reinterpret_cast<bool*>(__int64(Actor) + ReplicatesOffset);
						bool NetStartup = *reinterpret_cast<bool*>(__int64(Actor) + NetSetupOffset);
						uint8_t NetDormancy = *reinterpret_cast<uint8_t*>(__int64(Actor) + NetDormOffset);

						if (ClientBOI->IsValid() && Actor->IsValid() && BReplicates == true && (NetDormancy != 4U) && NetStartup == false) {
							ReplicateActor(Actor, ClientBOI);
						}
					}
				}
			}
			Sleep(1000 / 30);
		}
	}

	void StartServer() {
		Update();
		InitPreDefs();
#ifdef UE4_20 
		uintptr_t PRF_Addr = FindPattern(UE4_20_ReplicateFunction);
		uintptr_t CreateC_Addr = FindPattern(UE4_20_CreateChannel);
		uintptr_t InitHost_Addr = FindPattern(UE4_20_InitHost);
		uintptr_t RAI_Addr = FindPattern(UE4_20_ReplicateActor);
		uintptr_t SCA_Addr = FindPattern(UE4_20_SetChannelActor);
		uintptr_t WNCM_Addr = FindPattern(UE4_20_WorldNCM);
		uintptr_t WP_Addr = FindPattern(UE4_20_WelcomePlayer);
		uintptr_t SPA_Addr = FindPattern(UE4_20_SPA);
		uintptr_t AOB_NCM_Addr = FindPattern(UE4_20_AOB_NCM);
		uintptr_t AOB_NAC_Addr = FindPattern(UE4_20_NAC);
		uintptr_t ReplicateFunc_Addr = FindPattern(UE4_20_ReplicateFunction);
		uintptr_t PostLogin_Addr = FindPattern(UE4_20_PostLogin);
		uintptr_t SendClientAdjustment_Addr = FindPattern(UE4_20_SendClientAdjustment);
#elif UE4_16
		uintptr_t CreateC_Addr = FindPattern(UE4_16_CreateChannel);
		uintptr_t InitHost_Addr = FindPattern(UE4_16_InitHost);
		uintptr_t RAI_Addr = FindPattern(UE4_16_ReplicateActor);
		uintptr_t SCA_Addr = FindPattern(UE4_16_SetChannelActor);
		uintptr_t WNCM_Addr = FindPattern(UE4_16_WorldNCM);
		uintptr_t WP_Addr = FindPattern(UE4_16_WelcomePlayer);
		uintptr_t SPA_Addr = FindPattern(UE4_16_SPA);
		uintptr_t AOB_NCM_Addr = FindPattern(UE4_16_AOB_NCM);
		uintptr_t AOB_NAC_Addr = FindPattern(UE4_16_NAC);
#elif UE4_23
		uintptr_t PRF_Addr = FindPattern(UE4_23_ReplicateFunction);
		uintptr_t CreateC_Addr = FindPattern(UE4_23_CreateChannel);
		uintptr_t InitHost_Addr = FindPattern(UE4_23_InitHost);
		uintptr_t RAI_Addr = FindPattern(UE4_23_ReplicateActor);
		uintptr_t SCA_Addr = FindPattern(UE4_23_SetChannelActor);
		uintptr_t WNCM_Addr = FindPattern(UE4_23_WorldNCM);
		uintptr_t WP_Addr = FindPattern(UE4_23_WelcomePlayer);
		uintptr_t SPA_Addr = FindPattern(UE4_23_SPA);
		uintptr_t AOB_NCM_Addr = FindPattern(UE4_23_AOB_NCM);
		uintptr_t AOB_NAC_Addr = FindPattern(UE4_23_NAC);
		uintptr_t PostLogin_Addr = FindPattern(UE4_23_PostLogin);
#endif
		BeaconHost = SpawnActor(GWorld, FindObject("Class /Script/OnlineSubsystemUtils.OnlineBeaconHost", true), {}, {}, FActorSpawnParameters());
		CreateChannel = decltype(CreateChannel)(CreateC_Addr);
		SendClientAdjustment = decltype(SendClientAdjustment)(SendClientAdjustment_Addr);
		InitHost = decltype(InitHost)(InitHost_Addr);
		ReplicateFunctionInternal = decltype(ReplicateFunctionInternal)(ReplicateFunc_Addr);
		SetChannelActor = decltype(SetChannelActor)(SCA_Addr);
		ReplicateActorInternal = decltype(ReplicateActorInternal)(RAI_Addr);
		UWorld_NotifyControlMessage = decltype(UWorld_NotifyControlMessage)(WNCM_Addr);
		AC_ChannelOffset = __int64(FindOffsetC1("ObjectProperty /Script/Engine.Channel.Connection"));
		AlwaysRelvOffset = __int64(FindOffsetC1("BoolProperty /Script/Engine.Actor.bAlwaysRelevant"));
		ReplicatesOffset = __int64(FindOffsetC1("BoolProperty /Script/Engine.Actor.bReplicates"));
		NetDormOffset = __int64(FindOffsetC1("ByteProperty /Script/Engine.Actor.NetDormancy"));
		NetSetupOffset = __int64(FindOffsetC1("BoolProperty /Script/Engine.Actor.bNetStartup"));
		AC_ActorOffset = __int64(FindOffsetC1("ObjectProperty /Script/Engine.ActorChannel.Actor"));
		MH_CreateHook((void*)WP_Addr, Server::WelcomePlayer_Hook, (void**)&WelcomePlayer);
		MH_EnableHook((void*)WP_Addr);
		MH_CreateHook((void*)SPA_Addr, Server::SPA_Hook, (void**)&SpawnPlayActor);
		MH_EnableHook((void*)SPA_Addr);
		MH_CreateHook((void*)AOB_NCM_Addr, Server::AOB_NCM_Hook, nullptr);
		MH_EnableHook((void*)AOB_NCM_Addr);
		MH_CreateHook((void*)AOB_NAC_Addr, Server::AOB_NAC, nullptr);
		MH_EnableHook((void*)AOB_NAC_Addr);
		if (InitHost(BeaconHost)) {
			LOG("InitHost Called!");
		}
		NetDriver = *reinterpret_cast<UNetDriver**>(__int64(BeaconHost) + __int64(FindOffsetC1("ObjectProperty /Script/OnlineSubsystemUtils.OnlineBeacon.NetDriver")));
		LOG("Server Started!");
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ServerThread, 0, 0, 0);
	}
}

void MainThread() {
	Discord::SetMessage("Waiting to Start...");
	while (true)
	{
		if (InGame == false && GetAsyncKeyState(VK_F5) & 0x1) {
			InGame = true;
			//MessageBoxA(0, std::to_string(Finder::GetPropertySize(FindObject("ScriptStruct /Script/Engine.UniqueNetIdRepl",true))).c_str(), "Test", MB_OK);
			Update();
#ifdef Use_GMB
			auto URL = FString(L"Athena_Faceoff?game=Engine.GameMode");
#else
			auto URL = FString(L"Athena_Faceoff");
#endif
			GPlayerController->ProcessEvent(FindObject("Function /Script/Engine.PlayerController.SwitchLevel"), &URL);
		}

		if (GetAsyncKeyState(VK_F3) & 0x1) {
			//TODO (Kick)
		}

		if (Started == false && GetAsyncKeyState(VK_F1) & 0x1) {
			Started = true;
			Server::StartServer();
		}
		Sleep(1000 / 60);
	}
}

void* ProcessEventHook(UObject* Object, UObject* Function, void* Params) {
	std::string FuncName = Function->GetFullName();
	if (FuncName.find("ReadyToStartMatch") != std::string::npos && StartedMatch == false) {
		StartedMatch = true;
		Update();
		GPawn = SpawnActor(GWorld, FindObject("BlueprintGeneratedClass /Game/Athena/PlayerPawn_Athena.PlayerPawn_Athena_C"), new FVector(1, 1, 1), {}, FActorSpawnParameters());
		ProcessEventOG(GPlayerController, FindObject("Function /Script/Engine.Controller.Possess"), &GPawn);
		UObject* GameState = *reinterpret_cast<UObject**>(__int64(GWorld) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.World.GameState")));
		EAthenaGamePhase* GamePhase = reinterpret_cast<EAthenaGamePhase*>(reinterpret_cast<uintptr_t>(GameState) + FindOffsetC1("EnumProperty /Script/FortniteGame.FortGameStateAthena.GamePhase"));
		*GamePhase = EAthenaGamePhase::Aircraft;
		EAthenaGamePhase OGP = EAthenaGamePhase::None;
		GameState->ProcessEvent(FindObject("Function /Script/FortniteGame.FortGameStateAthena.OnRep_GamePhase"), &OGP);
		UObject* GameMode = *reinterpret_cast<UObject**>(__int64(GWorld) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.World.AuthorityGameMode")));
		//GameMode->ProcessEvent(FindObject("Function /Script/Engine.GameMode.StartMatch"));
		GPlayerController->ProcessEvent(FindObject("Function /Script/FortniteGame.FortPlayerController.ServerReadyToStartMatch"));
		Server::Game::ServerChoosePart(GPawn, FindObject("CustomCharacterPart /Game/Characters/CharacterParts/Female/Medium/Bodies/F_Med_Soldier_01.F_Med_Soldier_01"), EFortCustomPartType::Body);
		Server::Game::ServerChoosePart(GPawn, FindObject("CustomCharacterPart /Game/Characters/CharacterParts/Female/Medium/Heads/F_Med_Head1.F_Med_Head1"), EFortCustomPartType::Head);
		//ProcessEventOG(*reinterpret_cast<UObject**>(__int64(GPlayerController) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.Controller.Pawn"))), FindObject("Function /Script/FortniteGame.FortPlayerState.OnRep_CharacterParts"), nullptr);
	}

	if (FuncName.find("ReceiveTick") != std::string::npos && ServerStarted) {
		TArray<UObject*>* Clients = reinterpret_cast<TArray<UObject*>*>(__int64(NetDriver) + __int64(Server::ClientConnectionsOffset));
		for (int i = 0; i < Clients->Num(); i++) {
			auto Client = Clients->Data[i];
			auto PC = *reinterpret_cast<UObject**>(__int64(Client) + __int64(Offsets::Player::PlayerController));
			if (PC) {
				SendClientAdjustment(PC);
			}
		}
	}

	if (FuncName.find("ServerShortTimeout") != std::string::npos) {
		return NULL;
	}
	return ProcessEventOG(Object, Function, Params);
}