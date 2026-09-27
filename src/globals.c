#include "Manager.h"

// Centralized global definitions
Texture2D PlayerDefaultAvatar = { 0 };
bool showLogin = true;
bool showHome = false;
bool ShowStudio = false;
bool ShowStudioSidebar = false;
bool showGame = false;
bool CheckKeybinds = false;
char *CurrentGameHeader = ""; 
bool CheckKeybindBool = false;
bool ShowBanScreen = false;
char BanReasonGlobal[128] = "Unknown violation";
char BanTitle[128] = "";
char ProjectName[128] = "";
bool ShowCodeEditor = false;
const char *BanErrorCode = "ERR_NONE";