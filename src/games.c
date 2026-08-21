#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "Manager.h"
#include "raygui.h"

// Game Variables
Vector2 AvatarPosition = { 400.0f, 300.0f }; 
float speed = 2.0f;

void GamePanel(void) {
    DrawText("Game Library :", 170, 50, 48, WHITE);
    DrawText("Press ENTER to play!", 170, 100, 20, GRAY);
    
    if (IsKeyPressed(KEY_ENTER)) {
        showHome = false;
        showGame = true;
    }
}

void UpdateMouseFunc() {
    Vector2 mousePos = GetMousePosition();
    Camera2D PlayerCamera = { 0 };
    PlayerCamera.target = mousePos; 
}

void GameAntiCheat() {
    
    if(speed >= 50){

        ShowBanScreen = true;
        showGame = false;

        snprintf(BanReasonGlobal, sizeof(BanReasonGlobal), "%s", "Speed Hacks");

        LoadBanScreen(BanReasonGlobal);
    }
    
    

    else if(speed <= -1) {

        ShowBanScreen = true;
        showGame = false;

        snprintf(BanReasonGlobal, sizeof(BanReasonGlobal), "%s", "Negative speed value");

        LoadBanScreen(BanReasonGlobal);
    }

}





void CheckKeybindsFunc() {
    if(AvatarPosition.x > GetScreenWidth()) {
        AvatarPosition.x = -100;
        speed = 0;
    } 
    else if (AvatarPosition.x < -100) {
        AvatarPosition.x = GetScreenWidth();
        speed = 0;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
         AvatarPosition.x += speed;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) { 
        AvatarPosition.x -= speed;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))  {
          AvatarPosition.y -= speed;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
         AvatarPosition.y += speed;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        AvatarPosition.y -= 99; 
    }
    
    if (IsKeyDown(KEY_M)) {
        speed = 50;
    }




}

void UpdateGame(void) {

    GameAntiCheat();

    UpdateMouseFunc();

    GameAntiCheat();


}

void DrawingFunc() {
    CheckKeybinds = true;

    if (showGame == true) {
        DrawTextureV(PlayerDefaultAvatar, AvatarPosition, WHITE);
    }
    if(CheckKeybinds == true) {
        CheckKeybindBool = true;
    }
    if(CheckKeybindBool == true) {
        CheckKeybindsFunc();
    }
    
    Rectangle HomebuttonBounds = { 10.0f, 10.0f, 120.0f, 30.0f };
    if(GuiButton(HomebuttonBounds," <- Leave")) {
        showGame = false;
        showHome = true;
    }
}