#pragma once
#include "framework.h"
#include <string>
#include <locale>
#include <vector>

enum class EVectorQuantization : uint8_t
{
	RoundWholeNumber = 0,
	RoundOneDecimal = 1,
	RoundTwoDecimals = 2,
	EVectorQuantization_MAX = 3
};

enum class ERotatorQuantization : uint8_t
{
	ByteComponents = 0,
	ShortComponents = 1,
	ERotatorQuantization_MAX = 2
};

enum class ESpawnActorCollisionHandlingMethod : uint8_t
{
	Undefined = 0,
	AlwaysSpawn = 1,
	AdjustIfPossibleButAlwaysSpawn = 2,
	AdjustIfPossibleButDontSpawnIfColliding = 3,
	DontSpawnIfColliding = 4,
	ESpawnActorCollisionHandlingMethod_MAX = 5
};

enum class ENetDormancy : uint8_t
{
	DORM_Never = 0,
	DORM_Awake = 1,
	DORM_DormantAll = 2,
	DORM_DormantPartial = 3,
	DORM_Initial = 4,
	DORM_MAX = 5
};

enum class EAutoReceiveInput : uint8_t
{
	Disabled = 0,
	Player0 = 1,
	Player1 = 2,
	Player2 = 3,
	Player3 = 4,
	Player4 = 5,
	Player5 = 6,
	Player6 = 7,
	Player7 = 8,
	EAutoReceiveInput_MAX = 9
};

enum class ENetRole : uint8_t
{
	ROLE_None = 0,
	ROLE_SimulatedProxy = 1,
	ROLE_AutonomousProxy = 2,
	ROLE_Authority = 3,
	ROLE_MAX = 4
};

enum class ETickingGroup : uint8_t
{
	TG_PrePhysics = 0,
	TG_StartPhysics = 1,
	TG_DuringPhysics = 2,
	TG_EndPhysics = 3,
	TG_PostPhysics = 4,
	TG_PostUpdateWork = 5,
	TG_LastDemotable = 6,
	TG_NewlySpawned = 7,
	TG_MAX = 8
};

enum class EFortCustomBodyType : uint8_t
{
	NONE = 0,
	Small = 1,
	Medium = 2,
	MediumAndSmall = 3,
	Large = 4,
	LargeAndSmall = 5,
	LargeAndMedium = 6,
	All = 7,
	Deprecated = 8,
	EFortCustomBodyType_MAX = 9
};

enum class EFortCustomGender : uint8_t
{
	Invalid = 0,
	Male = 1,
	Female = 2,
	Both = 3,
	EFortCustomGender_MAX = 4
};

enum class EMontagePlayReturnType : uint8_t
{
	MontageLength = 0,
	Duration = 1,
	EMontagePlayReturnType_MAX = 2
};

enum EObjectFlags
{
	RF_NoFlags = 0x00000000,
	RF_Public = 0x00000001,
	RF_Standalone = 0x00000002,
	RF_MarkAsNative = 0x00000004,
	RF_Transactional = 0x00000008,
	RF_ClassDefaultObject = 0x00000010,
	RF_ArchetypeObject = 0x00000020,
	RF_Transient = 0x00000040,
	RF_MarkAsRootSet = 0x00000080,
	RF_TagGarbageTemp = 0x00000100,
	RF_NeedInitialization = 0x00000200,
	RF_NeedLoad = 0x00000400,
	RF_KeepForCooker = 0x00000800,
	RF_NeedPostLoad = 0x00001000,
	RF_NeedPostLoadSubobjects = 0x00002000,
	RF_NewerVersionExists = 0x00004000,
	RF_BeginDestroyed = 0x00008000,
	RF_FinishDestroyed = 0x00010000,
	RF_BeingRegenerated = 0x00020000,
	RF_DefaultSubObject = 0x00040000,
	RF_WasLoaded = 0x00080000,
	RF_TextExportTransient = 0x00100000,
	RF_LoadCompleted = 0x00200000,
	RF_InheritableComponentTemplate = 0x00400000,
	RF_DuplicateTransient = 0x00800000,
	RF_StrongRefOnFrame = 0x01000000,
	RF_NonPIEDuplicateTransient = 0x02000000,
	RF_Dynamic = 0x04000000,
	RF_WillBeLoaded = 0x08000000,
};

enum ELifetimeCondition
{
	COND_None = 0,
	COND_InitialOnly = 1,
	COND_OwnerOnly = 2,
	COND_SkipOwner = 3,
	COND_SimulatedOnly = 4,
	COND_AutonomousOnly = 5,
	COND_SimulatedOrPhysics = 6,
	COND_InitialOrOwner = 7,
	COND_Custom = 8,
	COND_ReplayOrOwner = 9,
	COND_ReplayOnly = 10,
	COND_SimulatedOnlyNoReplay = 11,
	COND_SimulatedOrPhysicsNoReplay = 12,
	COND_SkipReplay = 13,
	COND_Never = 15,
	COND_Max = 16,
};

enum class EFortQuickBars : uint8_t
{
	Primary,
	Secondary,
	Max_None,
	EFortQuickBars_MAX
};

enum class EAthenaGamePhase
{
	None = 0,
	Setup = 1,
	Warmup = 2,
	Aircraft = 3,
	SafeZones = 4,
	EndGame = 5,
	Count = 6,
	EAthenaGamePhase_MAX = 7
};

enum class EGameplayEffectDurationType : uint8_t
{
	Instant, Infinite, HasDuration, EGameplayEffectDurationType_MAX
};


struct FGuid
{
	int A;
	int B;
	int C;
	int D;
};
template<class T>
struct TArray
{
	friend class FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline T& operator[](int i) const
	{
		return Data[i];
	};

	inline BOOL IsValidIndex(int i) const
	{
		return i < Num();
	}

	inline void Add(T InputData)
	{
		Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	inline void Remove(int32_t Index)
	{
		TArray<T> NewArray;
		for (int i = 0; i < this->Count; i++)
		{
			if (i == Index)
				continue;

			NewArray.Add(this->operator[](i));
		}
		this->Data = (T*)realloc(NewArray.Data, sizeof(T) * (NewArray.Count));
		this->Count = NewArray.Count;
		this->Max = NewArray.Count;
	}

	T* Data;
	int Count;
	int Max;
};

enum EChannelCreateFlags
{
	None = (1 << 0),
	OpenedLocally = (1 << 1),
};

struct FString : public TArray<wchar_t>
{
	FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	}

	bool IsValid() const
	{
		return Data != nullptr;
	}

	const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

struct FName;

void(__fastcall* FNameToString)(FName* NameIn, FString& Out);
FName(__fastcall* FStringToName)(FString& StringIn);
void(__fastcall* FnFree)(__int64);


struct FName
{
	uint32_t ComparisonIndex;
	uint32_t DisplayIndex;

	FName() = default;

	std::string ToString()
	{
		FString temp;
		FNameToString(this, temp);

		std::string ret(temp.ToString());
		FnFree((__int64)temp.c_str());

		return ret;
	}
};

bool IsBadReadPtr(void* p)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
}

void* (__fastcall* ProcessEventOG)(void* Object, void* Function, void* Params);

struct UObject
{
	void** VTable;
	int32_t ObjectFlags;
	int32_t InternalIndex;
	UObject* Class;
	FName Name;
	UObject* Outer;

	bool IsA(UObject* cmp) const
	{
		if (cmp == Class)
			return false;
		return false;
	}

	bool IsValid() {
		return !IsBadReadPtr(this);
	}

	void* ProcessEvent(UObject* Function, void* Params = nullptr) {
		return ProcessEventOG(this, Function, Params);
	}

	std::string GetName()
	{
		return Name.ToString();
	}

	std::string GetFullName()
	{
		std::string temp;

		for (auto outer = Outer; outer; outer = outer->Outer)
		{
			temp = outer->GetName() + "." + temp;
		}

		temp = reinterpret_cast<UObject*>(Class)->GetName() + " " + temp + this->GetName();

		return temp;
	}
};
#define int32 int32_t
#define uint32 uint32_t

struct UNetDriver : public UObject {
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	struct FString                                     NetConnectionClassName;                                   // 0x0030(0x0010) (ZeroConstructor, Config)
	int MaxDownloadSize;                                          // 0x0040(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      bClampListenServerTickRate : 1;                           // 0x0044(0x0001) (Config)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0045(0x0003) MISSED OFFSET
	int NetServerMaxTickRate;                                     // 0x0048(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	int MaxInternetClientRate;                                    // 0x004C(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	int MaxClientRate;                                            // 0x0050(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float ServerTravelPause;                                        // 0x0054(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float SpawnPrioritySeconds;                                     // 0x0058(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float RelevantTimeout;                                          // 0x005C(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float KeepAliveTime;                                            // 0x0060(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float InitialConnectTimeout;                                    // 0x0064(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float ConnectionTimeout;                                        // 0x0068(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float TimeoutMultiplierForUnoptimizedBuilds;                    // 0x006C(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	bool bNoTimeouts;// 0x0070(0x0001) (ZeroConstructor, Config, IsPlainOldData)
	unsigned char UnknownData02[0x7];                                       // 0x0071(0x0007) MISSED OFFSET
	class UNetConnection* ServerConnection;                                         // 0x0078(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UNetConnection*> ClientConnections;                                        // 0x0080(0x0010) (ZeroConstructor)
	unsigned char  UnknownData03[0x18];                                      // 0x0090(0x0018) MISSED OFFSET
	class UWorld* World;     // 0x00A8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UPackage* WorldPackage;                                             // 0x00B0(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData04[0x20];                                      // 0x00B8(0x0020) MISSED OFFSET
	class UClass* NetConnectionClass;                                       // 0x00D8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UProperty* RoleProperty;                                             // 0x00E0(0x0008) (ZeroConstructor, IsPlainOldData)
	class UProperty* RemoteRoleProperty;// 0x00E8(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FName NetDriverName;                                            // 0x00F0(0x0008) (ZeroConstructor, Config, IsPlainOldData)
	unsigned char UnknownData05[0x48];                                      // 0x00F8(0x0048) MISSED OFFSET
	float Time; // 0x0140(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char Pad[0x1C7];
	uint32_t ReplicationFrame;
	unsigned char UnknownData06[0x159];
};

struct UObjectItem
{
	UObject* Object;
	DWORD Flags;
	DWORD ClusterIndex;
	DWORD SerialNumber;
	DWORD SerialNumber2;
};

struct PreUObjectItem
{
	UObjectItem* FUObject[10];
};

class UObjectArray {
public:
	inline int Num() const
	{
		return NumElements;
	}

	inline UObject* GetByIndex(int32_t index) const
	{
		return Objects[index].Object;
	}

	inline UObjectItem* GetItemByIndex(int32_t index) const
	{
		if (index < NumElements)
		{
			return &Objects[index];
		}
		return nullptr;
	}

private:
	UObjectItem* Objects;
	int MaxElements;
	int NumElements;
};

class OAP {
public:
	int32_t ObjFirstGCIndex;
	int32_t ObjLastNonGCIndex;
	int32_t MaxObjectsNotConsideredByGC;
	int32_t OpenForDisregardForGC;
	UObjectArray Objects;
};

class NewUObjectArray {
public:
	UObjectItem* Objects[9];
};

struct GObjects
{
	NewUObjectArray* ObjectArray;
	BYTE _padding_0[0xC];
	uint32_t NumElements;

	inline void NumChunks(int* start, int* end) const
	{
		int cStart = 0, cEnd = 0;

		if (!cEnd)
		{
			while (1)
			{
				if (ObjectArray->Objects[cStart] == 0)
				{
					cStart++;
				}
				else
				{
					break;
				}
			}

			cEnd = cStart;
			while (1)
			{
				if (ObjectArray->Objects[cEnd] == 0)
				{
					break;
				}
				else
				{
					cEnd++;
				}
			}
		}

		*start = cStart;
		*end = cEnd;
	}

	inline int32_t Num() const
	{
		return NumElements;
	}

	inline UObject* GetItemByIndex(int32_t index) const
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex = 0, chunkSize = 0xFFFF, chunkPos;
		UObjectItem* Object;

		NumChunks(&cStart, &cEnd);

		chunkIndex = index / chunkSize;
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
#pragma warning( push )
#pragma warning( disable : 26451 )
			Object = ObjectArray->Objects[chunkPos] + (index - chunkSize * chunkIndex);
#pragma warning( pop )
			if (!Object) { return NULL; }

			return Object->Object;
		}

		return nullptr;
	}
};

#ifdef UE4_23
GObjects* GObjs;
#else
UObjectArray* GObjs;
#endif

template <class TEnum>
class TEnumAsByte
{
public:
	TEnumAsByte()
	{
	}

	TEnumAsByte(TEnum _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	operator TEnum() const
	{
		return static_cast<TEnum>(value);
	}

	TEnum GetValue() const
	{
		return static_cast<TEnum>(value);
	}

private:
	uint8_t value;
};

struct UField : UObject
{
	UField* Next;
	void* padding_01;
	void* padding_02;
};

struct FField
{
	void* idk;
	void* Class;
	void* Owner;
	void* padding;
	FField* Next;
	FName Name;
	EObjectFlags FlagsPrivate;

	std::string GetName()
	{
		return Name.ToString();
	}

	std::string GetFullName()
	{
		std::string temp;

		for (auto outer = Next; outer; outer = outer->Next)
		{
			temp = outer->GetName() + "." + temp;
		}

		temp = static_cast<UObject*>(Class)->GetName() + " " + temp + this->GetName();
		return temp;
	}
};

struct FWeakObjectPtr
{
public:
	inline bool SerialNumbersMatch(UObjectItem* ObjectItem) const
	{
		return ObjectItem->SerialNumber == ObjectSerialNumber;
	}

	int32_t ObjectIndex;
	int32_t ObjectSerialNumber;
};

template<class T, class TWeakObjectPtrBase = FWeakObjectPtr>
struct TWeakObjectPtr : private FWeakObjectPtr
{
public:

	TWeakObjectPtr(UObject* Object) {
		ObjectIndex = Object->InternalIndex;
	}

	inline T* Get() const
	{
		return (T*)TWeakObjectPtrBase::Get();
	}

	inline T& operator*() const
	{
		return *Get();
	}

	inline T* operator->() const
	{
		return Get();
	}

	inline bool IsValid() const
	{
		return TWeakObjectPtrBase::IsValid();
	}
};

struct FProperty : FField
{
	int32_t ArrayDim;
	int32_t ElementSize;
	int32_t PropertyFlags;
	uint16_t RepIndex;
	TEnumAsByte<ELifetimeCondition> BlueprintReplicationCondition;
	int32_t Offset_Internal;
	FName RepNotifyFunc;
	FProperty* PropertyLinkNext;
	FProperty* NextRef;
	FProperty* DestructorLinkNext;
	FProperty* PostConstructLinkNext;
};

struct UStruct : UField
{
	UStruct* SuperStruct;
	UField* Children;
	FField* ChildProperties;
	int32_t PropertiesSize;
	int32_t MinAlignment;
	TArray<uint8_t> Script;
	FProperty* PropertyLink;
	FProperty* RefLink;
	FProperty* DestructorLink;
	FProperty* PostConstructLink;
};

struct FText
{
	char UnknownData[0x18];
};

UObject* GPawn;

uintptr_t GetAddressFromOffset(DWORD Offset) {
	return reinterpret_cast<uintptr_t>(GetModuleHandle(NULL) + __int64(Offset));
}

uintptr_t FindPattern(const char* signature, bool bRelative = false, uint32_t offset = 0)
{
	uintptr_t base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
	static auto patternToByte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?') ++current;
				bytes.push_back(-1);
			}
			else { bytes.push_back(strtoul(current, &current, 16)); }
		}
		return bytes;
	};

	const auto dosHeader = (PIMAGE_DOS_HEADER)base_address;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)base_address + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = patternToByte(signature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(base_address);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			uintptr_t address = reinterpret_cast<uintptr_t>(&scanBytes[i]);
			if (bRelative)
			{
				address = ((address + offset + 4) + *(int32_t*)(address + offset));
				return address;
			}
			return address;
		}
	}
	return NULL;
}

template <typename T = UObject*> static T __fastcall FindObject(std::string ObjectToFind, bool IsEqual = false)
{
	for (int i = 0; i < GObjs->Num(); i++)
	{
#ifdef UE4_20
		auto Object = GObjs->GetItemByIndex(i)->Object;
#elif UE4_16
		auto Object = GObjs->GetItemByIndex(i)->Object;
#else 
		auto Object = GObjs->GetItemByIndex(i);
#endif

		if (Object == nullptr)
		{
			continue;
		}

		if (IsEqual)
		{
			if (Object->GetFullName() == ObjectToFind)
			{
				return (T)Object;
			}
		}
		else
		{
			if (Object->GetFullName().find(ObjectToFind) != std::string::npos)
			{
				return (T)Object;
			}
		}
	}
	return nullptr;
}

template <typename T = UObject*> static T __fastcall FindObjectShort(std::string ObjectToFind)
{
	for (int i = 0; i < GObjs->Num(); i++)
	{
#ifdef UE4_20
		auto Object = GObjs->GetItemByIndex(i)->Object;
#elif UE4_16
		auto Object = GObjs->GetItemByIndex(i)->Object;
#else 
		auto Object = GObjs->GetItemByIndex(i);
#endif

		if (Object == nullptr)
		{
			continue;
		}

		if (Object->GetName() == ObjectToFind)
		{
			return (T)Object;
		}
	}
	return nullptr;
}

inline DWORD FindOffsetC1(const char* VariableFullName)
{
	UObject* VariableObj = FindObject(VariableFullName, true);
	if (VariableObj)
	{
		return *(uint32_t*)(__int64(VariableObj) + 0x44);
	}
	return NULL;
}

UObject* GWorld;

uintptr_t AC_ActorsOffset;

static TArray<UObject*>* __fastcall FindAllObjects()
{
	UObject* AC = *reinterpret_cast<UObject**>(__int64(GWorld) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.World.PersistentLevel")) + __int64(FindOffsetC1("ObjectProperty /Script/Engine.Level.ActorCluster")));
	TArray<UObject*>* RetActors = reinterpret_cast<TArray<UObject*>*>(__int64(AC) + __int64(AC_ActorsOffset));
	return RetActors;
}

struct FVector {
	float X;
	float Y;
	float Z;

	FVector() {
		X = Y = Z = 0;
	}

	FVector(float NX, float NY, float NZ) {
		X = NX;
		Y = NY;
		Z = NZ;
	}
};

enum class EFortCustomPartType : uint8_t
{
	Head = 0,
	Body = 1,
	Hat = 2,
	Backpack = 3,
	Charm = 4,
	Face = 5,
	NumTypes = 6,
	EFortCustomPartType_MAX = 7
};

class GameMode : public UObject {
public:
	void StartMatch() {
		ProcessEvent(FindObject("Function /Script/Engine.GameMode.StartMatch"));
	}
};

class CheatManager : UObject {
public:
	void DestroyAll(UObject* Class) {
		ProcessEvent(FindObject("Function /Script/Engine.CheatManager.DestroyAll"), &Class);
	}
};

class PlayerController : UObject {
public:
	void SwitchLevel(FString& URL) {
		ProcessEvent(FindObject("Function /Script/Engine.PlayerController.SwitchLevel"), &URL);
	}

	void StartFire(unsigned char& FireMode) {
		ProcessEvent(FindObject("Function /Script/Engine.PlayerController.StartFire"), &FireMode);
	}

	void SetName(FString& NewName) {
		ProcessEvent(FindObject("Function /Script/Engine.PlayerController.SetName"), &NewName);
	}

	void ClientWasKicked(FText& KickReason) {
		ProcessEvent(FindObject("Function /Script/Engine.PlayerController.ClientWasKicked"), &KickReason);
	}

	void Possess(UObject* TargetPawn) {
		ProcessEvent(FindObject("Function /Script/Engine.Controller.Possess"), &TargetPawn);
	}

	void ServerReadyToStartMatch() {
		ProcessEvent(FindObject("Function /Script/FortniteGame.FortPlayerController.ServerReadyToStartMatch"));
	}
};

struct FActorSpawnParameters
{
	FActorSpawnParameters() : Name(), Template(nullptr), Owner(nullptr), Instigator(nullptr), OverrideLevel(nullptr), bRemoteOwned(0), bNoFail(0),
		bDeferConstruction(0),
		bAllowDuringConstructionScript(1),
		NameMode(),
		ObjectFlags()
	{
		SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}
	;


	FName Name;

	UObject* Template;

	UObject* Owner;

	UObject* Instigator;

	UObject* OverrideLevel;

	ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingOverride;

private:

	uint8_t bRemoteOwned : 1;

public:

	bool IsRemoteOwned() const { return bRemoteOwned; }

	uint8_t bNoFail : 1;


	uint8_t bDeferConstruction : 1;

	uint8_t bAllowDuringConstructionScript : 1;


	enum class ESpawnActorNameMode : uint8_t
	{
		Required_Fatal,

		Required_ErrorAndReturnNull,

		Required_ReturnNull,

		Requested
	};


	ESpawnActorNameMode NameMode;

	EObjectFlags ObjectFlags;
};

struct FURL {
	FString Protocol; //unreal || http
	FString Host; //blank for local || ip
	int32_t Port;
	FString Map; //Athena_Terrain || Apollo_Terrain
	FString Redirect; //No Clue
	TArray<FString> Options; //No Clue
	FString Portal; //No Clue
	int32_t Valid;
};

static UObject* (__fastcall* SpawnActor)(UObject* World, UObject* Class, FVector* Loc, FVector* Rot, const FActorSpawnParameters& SpawnParameters);
static UObject* (__fastcall* GetFirstPlayerController)(UObject* World);

struct UniqueNetIdRepl {
	unsigned char UK00[0x28];
};

namespace Finder {
	struct UField : UObject
	{
		UField* Next;
		/*void* padding_01;
		void* padding_02;*/
	};

	struct UStruct : UField
	{
		struct StructBOI* Super;
		UField* Children;
		uint32_t Size;
		char pad[0x44];
	};

	int32_t GetPropertySize(UObject* Struct) {
		UStruct* TStruct = reinterpret_cast<UStruct*>(Struct);
		return TStruct->Size;
	}
}

struct FReplicationFlags
{
	union
	{
		struct
		{
			/** True if replicating actor is owned by the player controller on the target machine. */
			uint32_t bNetOwner : 1;
			/** True if this is the initial network update for the replicating actor. */
			uint32_t bNetInitial : 1;
			/** True if this is actor is RemoteRole simulated. */
			uint32_t bNetSimulated : 1;
			/** True if this is actor's ReplicatedMovement.bRepPhysics flag is true. */
			uint32_t bRepPhysics : 1;
			/** True if this actor is replicating on a replay connection. */
			uint32_t bReplay : 1;
			/** True if this actor's RPCs should be ignored. */
			uint32_t bIgnoreRPCs : 1;
			/** True if we should not swap the role and remote role of this actor when receiving properties. */
			uint32_t bSkipRoleSwap : 1;
			/** True if we should only compare role properties in CompareProperties */
			uint32_t bRolesOnly : 1;
			/** True if we should force all properties dirty on initial replication. */
			uint32_t bForceInitialDirty : 1;
			/** True if we should serialize property names instead of handles. */
			uint32_t bSerializePropertyNames : 1;
			/** True if a subclass of UActorChannel needs custom subobject replication */
			uint32_t bUseCustomSubobjectReplication : 1;

		};

		uint32_t Value;
	};
	FReplicationFlags()
	{
		Value = 0;
	}
};

