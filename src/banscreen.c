#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "Manager.h"
#include "raygui.h"

void BanScreen(const char *BanTitleBan, const char *BanReason) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 20, 20, 20, 255 });

    int boxWidth = 560;
    int boxHeight = 340;
    int boxX = (GetScreenWidth() - boxWidth) / 2;
    int boxY = (GetScreenHeight() - boxHeight) / 2;

    DrawRectangle(boxX, boxY, boxWidth, boxHeight, (Color){ 35, 35, 35, 255 });
    DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, (Color){ 60, 60, 60, 255 });

    DrawRectangle(boxX, boxY, boxWidth, 65, (Color){ 218, 41, 28, 255 });
    DrawText("Disconnected", boxX + 20, boxY + 18, 28, WHITE);

    DrawText("You have been banned.", boxX + 25, boxY + 85, 20, WHITE);
    DrawText(BanTitleBan, boxX + 25, boxY + 125, 16, (Color){ 180, 180, 180, 255 });
    
    char codeBuffer[128];
    snprintf(codeBuffer, sizeof(codeBuffer), "Details: %s", BanReason);
    DrawText(codeBuffer, boxX + 25, boxY + 155, 16, (Color){ 220, 100, 100, 255 });

    DrawLine(boxX + 25, boxY + 200, boxX + boxWidth - 25, boxY + 200, (Color){ 70, 70, 70, 255 });

    if (GuiButton((Rectangle){ (float)(boxX + 25), (float)(boxY + 230), (float)(boxWidth - 50), (float)45 }, "OK")) {
        ShowBanScreen = false;
        showGame = false;
        showHome = true;
    }
}

void LoadBanScreen(const char *title, const char *reason) {
    BanScreen(title, reason);
}