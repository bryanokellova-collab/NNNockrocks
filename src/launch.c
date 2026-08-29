#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "Manager.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_USERS 150
#define MAX_CHARS 32
#define USERS_FILE "users.bin"

typedef struct {
    char username[MAX_CHARS];
    char password[MAX_CHARS];
} User;

static User userDatabase[MAX_USERS];
static int userCount = 0;
static Texture2D logoTexture;
static char usernameText[MAX_CHARS] = "\0";
static char passwordText[MAX_CHARS] = "\0";
static bool usernameEditMode = false;
static bool passwordEditMode = false;



static void LoadUsers(void) {
    FILE *file = fopen(USERS_FILE, "rb");
    if (file != NULL) {
        fread(&userCount, sizeof(int), 1, file);
        if (userCount > MAX_USERS) userCount = MAX_USERS;
        fread(userDatabase, sizeof(User), userCount, file);
        fclose(file);
    }
}

static void SaveUsers(void) {
    FILE *file = fopen(USERS_FILE, "wb");
    if (file != NULL) {
        fwrite(&userCount, sizeof(int), 1, file);
        fwrite(userDatabase, sizeof(User), userCount, file);
        fclose(file);
    }
}

void UnloadResources() {
    UnloadTexture(PlayerDefaultAvatar);
    if (logoTexture.id > 0) UnloadTexture(logoTexture);
}

void CheckIfKeysArePressed(void) {
    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
    if ((IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) && IsKeyPressed(KEY_F4)) {
        UnloadResources();
        CloseWindow();
        exit(0);
    }
}

static void LoadAppIconAndTextures(void) { 
    Image logoImg = LoadImage("logo.png");
    if (logoImg.data != NULL) {
        SetWindowIcon(logoImg);
        UnloadImage(logoImg); 
    }
    logoTexture = LoadTexture("logo.png");
}

void DrawLoginPanel(void) {
    Rectangle panel = { (float)GetScreenWidth()/2 - 220, (float)GetScreenHeight()/2 - 210, 440, 420 };
    
    DrawRectangleRec(panel, (Color){ 30, 31, 36, 255 });
    DrawRectangleLinesEx(panel, 1.5f, (Color){ 57, 59, 65, 255 });

    if (logoTexture.id > 0) {
        float logoSize = 100.0f;
        Rectangle srcRec = { 0.0f, 0.0f, (float)logoTexture.width, (float)logoTexture.height };
        Rectangle destRec = { panel.x + (panel.width / 2) - (logoSize / 2), panel.y + 20, logoSize, logoSize };
        DrawTexturePro(logoTexture, srcRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }

    GuiLabel((Rectangle){ panel.x + 30, panel.y + 135, 380, 30 }, "Username:");
    if (GuiTextBox((Rectangle){ panel.x + 30, panel.y + 165, 380, 45 }, usernameText, MAX_CHARS, usernameEditMode)) {
        usernameEditMode = !usernameEditMode;
    }
    
    GuiLabel((Rectangle){ panel.x + 30, panel.y + 225, 380, 30 }, "Password:");
    if (GuiTextBox((Rectangle){ panel.x + 30, panel.y + 255, 380, 45 }, passwordText, MAX_CHARS, passwordEditMode)) {
        passwordEditMode = !passwordEditMode;
    }

    bool isInputValid = (usernameText[0] != '\0' && passwordText[0] != '\0');

    if (GuiButton((Rectangle){ panel.x + 30, panel.y + 335, 180, 45 }, "Login")) {
        if (isInputValid) {
            for (int i = 0; i < userCount; i++) {
                if (TextIsEqual(usernameText, userDatabase[i].username) && TextIsEqual(passwordText, userDatabase[i].password)) {
                    showLogin = false; 
                    showHome = true;
                    break;
                }
            }
        }
    }

    if (GuiButton((Rectangle){ panel.x + 230, panel.y + 335, 180, 45 }, "Create Account")) {
        if (isInputValid && userCount < MAX_USERS) {
            TextCopy(userDatabase[userCount].username, usernameText);
            TextCopy(userDatabase[userCount].password, passwordText);
            userCount++;
            
            SaveUsers(); 
            showLogin = false; 
            showHome = true;
        }
    }
}

int main(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Nockrocks");
    SetTargetFPS(60);
    
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24); 
    
    LoadUsers(); 
    LoadAppIconAndTextures(); 

    PlayerDefaultAvatar = LoadTexture("Dav.png");
    PlayerDefaultAvatar.height = 150;
    PlayerDefaultAvatar.width = 150;
    
    // Main Loop
    while (!WindowShouldClose()) {
        CheckIfKeysArePressed();
        
        // home.c now handles all state logic and drawing
        HandleAppScreens(); 
    } 
    
    UnloadResources();
    CloseWindow();
    return 0;
}