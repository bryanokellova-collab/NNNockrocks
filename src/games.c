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

void UpdateMouseFunc(void) {
    Vector2 mousePos = GetMousePosition();
    Camera2D PlayerCamera = { 0 };
    PlayerCamera.target = mousePos; 
}

void GameAntiCheat(void) {
    if (speed >= 50.0f) {
        ShowBanScreen = true;
        showGame = false;

        snprintf(BanTitle, sizeof(BanTitle), "%s", "Unexpected Speed overflow");
        snprintf(BanReasonGlobal, sizeof(BanReasonGlobal), "%s", "Speed Hacks");

        LoadBanScreen(BanTitle, BanReasonGlobal);
    }
    else if (speed <= -1.0f) {
        ShowBanScreen = true;
        showGame = false;

        snprintf(BanTitle, sizeof(BanTitle), "%s", "Unexpected behaviour");
        snprintf(BanReasonGlobal, sizeof(BanReasonGlobal), "%s", "Negative speed value");

        LoadBanScreen(BanTitle, BanReasonGlobal);
    }
}

void CheckKeybindsFunc(void) {
    if (AvatarPosition.x > GetScreenWidth()) {
        AvatarPosition.x = -100.0f;
        speed = 0.0f;
    } 
    else if (AvatarPosition.x < -100.0f) {
        AvatarPosition.x = (float)GetScreenWidth();
        speed = 0.0f;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        AvatarPosition.x += speed;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) { 
        AvatarPosition.x -= speed;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        AvatarPosition.y -= speed;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        AvatarPosition.y += speed;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        AvatarPosition.y -= 99.0f; 
    }
    
    if (IsKeyDown(KEY_M)) {
        speed = -1.0f;
    }
}

void UpdateGame(void) {
    // 1. Process Anti-Cheat Checks
    GameAntiCheat();

    // 2. Process Input & Positions
    if (showGame) {
        CheckKeybindsFunc();
        UpdateMouseFunc();
    }

    // 3. Render Visuals
    DrawingFunc();
}

void DrawingFunc(void) {
    // Draw texture only if it has been properly loaded into memory
    if (showGame) {
        if (PlayerDefaultAvatar.id > 0) {
            DrawTextureV(PlayerDefaultAvatar, AvatarPosition, WHITE);
        } else {
            // Placeholder rectangle if texture isn't loaded yet
            DrawRectangleV(AvatarPosition, (Vector2){ 32, 32 }, RED);
        }
    }
    
    // UI Navigation Button
    Rectangle HomebuttonBounds = { 10.0f, 10.0f, 120.0f, 30.0f };
    if (GuiButton(HomebuttonBounds, " <- Leave")) {
        showGame = false;
        showHome = true;
    }
}