#ifndef MANAGER_H
#define MANAGER_H

#include <stdbool.h>
#include "raylib.h"

extern bool showLogin;
extern bool showHome;
extern bool ShowStudio;
extern bool ShowStudioSidebar;
extern bool showGame;

extern Texture2D PlayerDefaultAvatar;

extern char ProjectName[128];
extern bool ShowCodeEditor;
extern const char *BanErrorCode;
extern char *CurrentGameHeader;
extern bool CheckKeybinds;
extern bool CheckKeybindBool;
extern bool ShowBanScreen;
extern char BanReasonGlobal[128]; // Properly declared as extern
extern char BanTitle[128];
extern float speed;



void LoadBanScreen(const char BanTitleBan,char *BanReason);

// UI & Routing Prototypes
void HandleAppScreens(void);
void DrawLoginPanel(void);
void GamePanel(void);
void AboutPanel(void);
void HomeSideBar(void);
void HomePanel(void);
void LoadStudioHome(void);

// Game Logic Prototypes
void UpdateGame(void);
void DrawingFunc();
void GameAntiCheat(void);
void CheckIfKeysArePressed(void);
void UnloadResources(void);

#endif