#include "raylib.h"
#include "raygui.h"
#include "Manager.h"

static int currentTab = 0; 

void HomeSideBar(void) {
    int sidebarWidth = 220;
    
    DrawRectangle(0, 0, sidebarWidth, GetScreenHeight(), (Color){ 30, 31, 36, 255 });
    DrawRectangleLines(0, 0, sidebarWidth, GetScreenHeight(), (Color){ 57, 59, 65, 255 });

    DrawText("NOCKROCKS", 35, 30, 24, RAYWHITE);
    DrawLine(20, 70, sidebarWidth - 20, 70, (Color){ 57, 59, 65, 255 });

    if (GuiButton((Rectangle){ 20, 100, 180, 45 }, "Home")) {
        currentTab = 0; 
    }
    if (GuiButton((Rectangle){ 20, 160, 180, 45 }, "Games")) {
        currentTab = 1; 
    }
    if (GuiButton((Rectangle){ 20, 220, 180, 45 }, "Studio (Create)")) {
        showHome = false;
        ShowStudio = true;
    }
    if (GuiButton((Rectangle){ 20, GetScreenHeight() - 70, 180, 45 }, "Log Out")) {
        showHome = false;
        showLogin = true;
    }
}

void HomePanel(void) { 


    DrawLine(260, 80, GetScreenWidth() - 40, 80, (Color){ 57, 59, 65, 255 });

    if (currentTab == 0) {
        CheckKeybinds = false;
        ShowBanScreen = false;
        DrawText("Welcome back!", 260, 40, 28, RAYWHITE);
    } 
    else if (currentTab == 1) {
        DrawText("Discover Games", 260, 40, 28, RAYWHITE);
        showHome = false;
        showLogin = false;
        showGame = true;
    }
    else if (currentTab == 2) {
        CheckKeybinds = false;
        showGame = false;
        showHome = false;
        ShowStudio = false;
        ShowBanScreen = true;
    }
    else if (currentTab == 3){
        CheckKeybinds = false;
        showGame = false;
        showHome = false;
        ShowStudio = false;
        ShowBanScreen = false;
        ShowStudio = true;
    }
}

void LoadStudioHome(void) {
    ClearBackground((Color){ 25, 25, 30, 255 });
    DrawText("Nockrocks Studio", 50, 50, 36, RAYWHITE);
    DrawText("Design and create your experiences here.", 50, 100, 20, LIGHTGRAY);
    
    if (GuiButton((Rectangle){ 50, 150, 200, 45 }, "<- Back to Client")) {
        ShowStudio = false;
        showHome = true;
    }
}

void HandleAppScreens(void) {
    if (showGame) {
        UpdateGame();
    }

    BeginDrawing();
    
    if (showGame) {
        ClearBackground(RAYWHITE);
        DrawingFunc();
    } 
    else {
        ClearBackground((Color){ 19, 20, 24, 255 });
    
        if (showLogin) { 
            DrawLoginPanel(); 
        }
        else if (showHome) { 
            currentTab = 0;
            CheckKeybinds = false;
            HomeSideBar(); 
            HomePanel(); 
        }
        else if (ShowBanScreen){
            currentTab = 2;
            LoadBanScreen(BanReasonGlobal);
        }
        else if (ShowStudio) {
            currentTab = 3;
            LoadStudioHome();
        }
    }
    
    EndDrawing();
}