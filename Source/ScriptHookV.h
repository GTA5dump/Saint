#pragma once

typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);
typedef void(*PresentCallback)(void*);

enum eGameVersion : int
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,

	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,

	VER_1_0_372_2_STEAM,
	VER_1_0_372_2_NOSTEAM,

	VER_1_0_393_2_STEAM,
	VER_1_0_393_2_NOSTEAM,

	VER_1_0_393_4_STEAM,
	VER_1_0_393_4_NOSTEAM,

	VER_1_0_463_1_STEAM,
	VER_1_0_463_1_NOSTEAM,

	VER_1_0_505_2_STEAM,
	VER_1_0_505_2_NOSTEAM,

	VER_1_0_573_1_STEAM,
	VER_1_0_573_1_NOSTEAM,

	VER_1_0_617_1_STEAM,
	VER_1_0_617_1_NOSTEAM,

	VER_1_0_678_1_STEAM,
	VER_1_0_678_1_NOSTEAM,

	VER_1_0_757_2_STEAM,
	VER_1_0_757_2_NOSTEAM,

	VER_1_0_757_4_STEAM,
	VER_1_0_757_4_NOSTEAM,

	VER_1_0_791_2_STEAM,
	VER_1_0_791_2_NOSTEAM,

	VER_1_0_877_1_STEAM,
	VER_1_0_877_1_NOSTEAM,

	VER_1_0_944_2_STEAM,
	VER_1_0_944_2_NOSTEAM,

	VER_1_0_1011_1_STEAM,
	VER_1_0_1011_1_NOSTEAM,

	VER_1_0_1032_1_STEAM,
	VER_1_0_1032_1_NOSTEAM,

	VER_1_0_1103_2_STEAM,
	VER_1_0_1103_2_NOSTEAM,

	VER_1_0_1180_2_STEAM,
	VER_1_0_1180_2_NOSTEAM,

	VER_1_0_1290_1_STEAM,
	VER_1_0_1290_1_NOSTEAM,

	VER_1_0_1365_1_STEAM,
	VER_1_0_1365_1_NOSTEAM,

	VER_1_0_1493_0_STEAM,
	VER_1_0_1493_0_NOSTEAM,

	VER_1_0_1493_1_STEAM,
	VER_1_0_1493_1_NOSTEAM,

	VER_SIZE,
	VER_UNK = -1
};

class ScriptHookV {
public:
	//static NativeContext Context;
	static uint64_t Hash;
	//static vector<ModuleDetection> LoadedModuleMemory;

	static void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
	static void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
	static void scriptUnregister(HMODULE module);
	static BYTE* getScriptHandleBaseAddress(int handle);
	static void presentCallbackUnregister(PresentCallback cb);
	static void presentCallbackRegister(PresentCallback cb);
	static void nativeInit(uint64_t hash);
	static void nativePush64(uint64_t val);
	static uint64_t* nativeCall();
	static uint64_t* getGlobalPtr(int index);
	static int createTexture(const char* fileName);
	static void drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a);
	static void scriptWait(unsigned long waitTime);
	static void keyboardHandlerRegister(KeyboardHandler function);
	static void keyboardHandlerUnregister(KeyboardHandler function);
	static int getGameVersion();

	static int worldGetAllVehicles(int* arr, int arrSize);
	static int worldGetAllPeds(int* arr, int arrSize);
	static int worldGetAllObjects(int* arr, int arrSize);
	static int worldGetAllPickups(int* arr, int arrSize);
};