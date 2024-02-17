#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "md5.h"
#include "obfuscate.h"
#define obfuscatestring(s) std::string(AY_OBFUSCATE(s))
#include "VirtualizerSDK.h"
#include "Signatures.hpp"
#include "Hooking.hpp"
#include "NativeHook.hpp"
#include "ScriptManager.hpp"
#include "LogScript.hpp"
#include "ScriptCallback.hpp"
#include "Invoker.hpp"
#include "CustomText.hpp"
#include "D3DRenderer.hpp"
#include "UI/Framework.hpp"
#include "Translation.hpp"
#include "FiberHelper.hpp"
#include "Script.h"
#include "Render.h"
#include "Discord/DiscordHandler.hpp"
#include <Windows.h>
#include <ShellAPI.h>
#include <urlmon.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "Features.h"
#include "Exception.h"

#pragma comment (lib, "urlmon.lib") 
#pragma comment(lib, "winmm.lib")

const char* meower = "";
bool fileExists(const std::string& filePath) {
	std::ifstream file(filePath);
	return file.good();
}
bool does_exist(const char* path, const char* file) {
	std::string MenuFolderPath = path;
	if (fileExists(MenuFolderPath + file)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}
void load_dir() {
	using namespace Saint;
	fs::create_directories("C:\\Saint\\");
	fs::create_directories("C:\\Saint\\Sounds");
	fs::create_directories("C:\\Saint\\Themes");
	fs::create_directories("C:\\Saint\\Textures");
	fs::create_directories("C:\\Saint\\Textures\\Header");


	//int yes18 = _wmkdir((const wchar_t*)"C:\\Saint\\Fonts\\Chinese-Rocks.ttf");
	if (!does_exist("C:\\Saint\\", "Textures.ytd")) {
		int yes19 = _wmkdir((const wchar_t*)"C:\\Saint\\Textures.ytd");
	}
	int yes18 = _wmkdir((const wchar_t*)"C:\\Saint\\Sounds\\Intro.wav");
	if (!does_exist("C:\\Saint\\Sounds\\", "Notification.wav")) {
		//int yes20 = _wmkdir((const wchar_t*)"C:\\Saint\\Sounds\\Notification.wav");
	}
	int yes25 = _wmkdir((const wchar_t*)"C:\\Saint\\Themes\\ParagonV2.json");
	if (!does_exist("C:\\Saint\\Themes\\", "ParagonV2.json")) {

	}
	int yes26 = _wmkdir((const wchar_t*)"C:\\Saint\\Textures\\Template.ytd");
	if (!does_exist("C:\\Saint\\Textures\\", "Template.ytd")) {

	}
	int yes27 = _wmkdir((const wchar_t*)"C:\\Saint\\Textures\\Header\\AnimTemp.ytd");
	if (!does_exist("C:\\Saint\\Textures\\Header\\", "AnimTemp.ytd")) {
	}
	std::string path;
	std::ofstream file;
	std::string notification_path = std::string("C:\\Saint\\Sounds\\Notification.wav");
	std::string tooltips_path = std::string("C:\\Saint\\tooltips.txt");
	std::string texture_path = std::string("C:\\Saint\\Textures.ytd");
	std::string Theme1_path = std::string("C:\\Saint\\Themes\\ParagonV2.json");
	std::string Theme12_path = std::string("C:\\Saint\\Textures\\Paragon.ytd");
	std::string Theme13_path = std::string("C:\\Saint\\Themes\\Default.json");
	std::string Theme14_path = std::string("C:\\Saint\\Textures\\Template.ytd");
	std::string Theme15_path = std::string("C:\\Saint\\Textures\\Header\\AnimTemp.ytd");
	//URLDownloadToFileA(0, "https://saintcheats.xyz/Chinese-Rocks.ttf", DownloadPP.c_str(), 0, 0);


	if (!does_exist("C:\\Saint\\Textures", "Template.ytd")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1116038150364598373/1121251087190610020/Template.ytd", Theme14_path.c_str(), 0, 0);
	}

	if (!does_exist("C:\\Saint\\Textures\\Header", "AnimTemp.ytd")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1116038150364598373/1121251321153065020/AnimTemp.ytd", Theme15_path.c_str(), 0, 0);
	}


	if (!does_exist("C:\\Saint\\Themes", "ParagonV2.json")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/978449512668475454/1120684494031163423/ParagonV2.json", Theme1_path.c_str(), 0, 0);
	}

	if (!does_exist("C:\\Saint\\Themes", "Default.json")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1116038150364598373/1121248187638878218/Default.json", Theme13_path.c_str(), 0, 0);
	}

	if (!does_exist("C:\\Saint\\Textures", "Paragon.ytd")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/978449512668475454/1120684493699817592/Paragon.ytd", texture_path.c_str(), 0, 0);
	}


	if (!does_exist("C:\\Saint\\", "Textures.ytd")) {
		URLDownloadToFileA(0, "https://saintcheats.xyz/Textures.ytd", texture_path.c_str(), 0, 0);
	}
	
	if (!does_exist("C:\\Saint\\Sounds\\", "Notification.wav")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1104892686386876427/1104971663755464814/Notification.wav", notification_path.c_str(), 0, 0); // dont work nice tim
	}
	if (!does_exist("C:\\Saint\\", "tooltips.txt")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1081813761796608095/1110040729134321675/tooltips.txt", tooltips_path.c_str(), 0, 0);
	}
}
std::string wideToString(std::wstring strw) {
	if (strw.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &strw[0], (int)strw.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &strw[0], (int)strw.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
#ifndef DEV
std::string gethwid(void) {
	HW_PROFILE_INFOW winapiHWID;
	GetCurrentHwProfileW(&winapiHWID);
	return md5(wideToString(winapiHWID.szHwProfileGuid));
}
std::string encryptDecrypt(std::string toEncrypt) {
	char key[3] = { 'V', 'B', 'C' };
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	return output;
}
#endif
std::string branding = " | Saint Cheats";
std::array<std::string, 3> Titles = {
	"What am I doing wrong - Patek/Jayden." + branding,
	"Unleash your inner vali" + branding,
	"\"is this scooby?\"" + branding
};
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace Saint;
	if (reason == DLL_PROCESS_ATTACH)
	{
		g_Module = hInstance;
		CreateThread(nullptr, 0, [](LPVOID) -> DWORD
			{
				std::unique_ptr<NativeHooks> g_NativeHook;
#ifndef DEV
				VIRTUALIZER_DOLPHIN_BLACK_START
					bool authed2 = false;
				ATOM Atom1;
				std::string hash;
				std::ifstream i(obfuscatestring("C:\\Saint\\key.txt"));
				std::stringstream s;
				s << i.rdbuf();
				i.close();
				std::string key = s.str();
				auto client = httplib::SSLClient(obfuscatestring("saintcheats.xyz"));
				auto response2 = client.Get(obfuscatestring("/saintauth.php?init=true"));
				std::string hwid = gethwid();
				std::string times = std::to_string(time(NULL));
				std::string times2 = encryptDecrypt(response2->body);
				httplib::MultipartFormDataItems form = {
					{obfuscatestring("key"), key},
					{obfuscatestring("hwid"), hwid},
					{obfuscatestring("key1"), times},
					{obfuscatestring("key2"), times2},
				};
				auto response = client.Post(obfuscatestring("/saintauth.php"), form);
				std::string body = response->body;
				if (body == obfuscatestring("err2"))
				{
					exit(-1);
					goto yeet;
				}
				hash = md5(key + times + obfuscatestring("ikey"));
				if (body == hash) {
					exit(-1);
					goto yeet;
				}
				hash = md5(key + times + hwid + obfuscatestring("ihwid"));
				if (body == hash) {
					exit(-1);
					goto yeet;
				}
				hash = md5(key + times + hwid + obfuscatestring("success"));
				if (body != hash) {
					exit(-1);
					goto yeet;
				}
				else {
					authed2 = true;
				}
#endif
				g_Logger = std::make_unique<Logger>();
				exceptions::initExceptionHandler();
				g_Logger->Info(R"( 
					   _____ ___    _____   ________
					  / ___//   |  /  _/ | / /_  __/
					  \__ \/ /| |  / //  |/ / / /   
					 ___/ / ___ |_/ // /|  / / /    
					/____/_/  |_/___/_/ |_/ /_/     
                                
				)");
				g_Logger->Info("Version: %s", MENU_VERSION);
				g_Logger->Info("This build was compiled on " __DATE__);

				//	PlaySound(TEXT("C:\\Saint\\Sounds\\Intro.wav"), NULL, SND_FILENAME | SND_ASYNC);
				g_FiberPool.registerFbrPool();

				g_GameFunctions = std::make_unique<GameFunctions>();
				g_GameVariables = std::make_unique<GameVariables>();
				pointers = std::make_unique<Pointers>();
				srand(time(NULL));
				//SetWindowTextA(g_GameVariables->m_GameWindow, Titles[rand() % Titles.size()].c_str());
#ifndef DEV
				Atom1 = GlobalFindAtomA(AY_OBFUSCATE("R'g^gc]]pQkEE.wWQp"));
				if (!Atom1)
				{
					exit(-1);
					goto yeet;
				}
				while (Atom1) {
					GlobalDeleteAtom(Atom1);
					Atom1 = GlobalFindAtomA(AY_OBFUSCATE("R'g^gc]]pQkEE.wWQp"));
				}

				g_Logger->Info("Authed completed.");
				if (authed2) {
					authed = 0x84E68052;
				}
#else
				g_Logger->Error("Running in dev mode! NEVER release a dev build.");
				authed = 0x84E68052;
				
#endif	
				//Game Functions
				// 
				// Wait for the game to load
				if (authed != 0x84E68052)
					goto yeet;
				if (*g_GameVariables->m_GameState != 0)
					g_Logger->Info("Waiting For Game To Load.");

				while (*g_GameVariables->m_GameState != 0)
				{
					std::this_thread::sleep_for(3s);
					std::this_thread::yield();
				}
				g_Logger->Info("Game Loaded.");

				g_GameVariables->PostInit();
				g_CustomText = std::make_unique<CustomText>();
				g_D3DRenderer = std::make_unique<D3DRenderer>();
				g_Render = std::make_unique<UserInterface::Framework>();
				g_ScriptManager = std::make_unique<ScriptManager>();
				g_MainScript = std::make_shared<MainScript>();
				g_LogScript = std::make_shared<LogScript>();
				g_CallbackScript = std::make_shared<CallbackScript>();
				g_ScriptManager->AddScript(g_LogScript);
				g_ScriptManager->AddScript(g_CallbackScript);
				g_FiberManager.add(std::make_unique<fbr>([=] { g_MainScript->Tick(); }), "main_script");
				g_Hooking = std::make_unique<Hooking>();
				g_Hooking->Hook();
				g_NativeHook = std::make_unique<NativeHooks>();
				g_Discord->Init();
				g_Render->LoadVariablesFromJson("C:\\Saint\\Themes\\Default.json");

				//registering
				load_dir();
				if (!does_exist("C:\\Saint\\", "tooltips.txt")) {
					Noti::InsertNotification({ ImGuiToastType_None, 2000, "No tooltip file found.", });
				}
				if (does_exist("C:\\Saint\\Sounds\\", "Notification.wav")) { // prevent crashes
					Noti::InsertNotification({ ImGuiToastType_None, 2000, "Welcome, thanks for buying Saint!", });
				}
				//PlaySound(TEXT("C:\\Saint\\Sounds\\Intro.wav"), NULL, SND_FILENAME | SND_ASYNC);

				if (tutorial.get_theme_path() != "NoneActive" || tutorial.get_theme_path() != "" || tutorial.get_theme_path() != " ") {
					g_Render->LoadVariablesFromJson(tutorial.get_theme_path());
				}

				
				while (g_Running)
				{

					if (Flags->isDev()) {
						if (IsKeyPressed(VK_DELETE))
							g_Running = false;
					}
					std::this_thread::sleep_for(3ms);
					std::this_thread::yield();
				}
				std::this_thread::sleep_for(500ms);
				exceptions::uninitExceptionHandler();
				PlaySound(NULL, NULL, 0);
				g_Discord->Shutdown();

				g_NativeHook.reset();

				g_Hooking->Unhook();

				g_ScriptManager.reset();
				g_LogScript.reset();
				g_MainScript.reset();
				g_CallbackScript.reset();

				g_Render.reset();
				g_D3DRenderer.reset();
				g_CustomText.reset();

				std::this_thread::sleep_for(500ms);

				g_Hooking.reset();

				//SetWindowTextA(g_GameVariables->m_GameWindow, "Grand Theft Auto V");
				g_GameVariables.reset();
				g_GameFunctions.reset();
				pointers.reset();

				g_Logger->Info("Come Again!");
				g_Logger.reset();
			yeet:
#ifndef DEV
				VIRTUALIZER_DOLPHIN_BLACK_END
#endif
					OPENSSL_thread_stop();
				FreeLibraryAndExitThread(g_Module, 0);

			}, nullptr, 0, nullptr);
	}

	return true;
}
