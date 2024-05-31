#define _CRT_SECURE_NO_WARNINGS    // sprintf 보안 경고로 인한 컴파일 에러 방지
#pragma warning( disable : 4244 ) // C4244

#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>


enum State {
	Main,
	Game
} state;

struct RGB {
	int R;
	int G;
	int B;
}typedef RGB;


// BGM
CP_Sound backgroundMusic = NULL;
int isMouseHover;


// Functions
void main_screen_logo(void) {
	// Init Background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	// Logo
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 510, CP_System_GetWindowHeight() / 2 - 340, 950, 380);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 485, CP_System_GetWindowHeight() / 2 - 315, 900, 330);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(200.0f);
	CP_Font_DrawText("Tetris!", CP_System_GetWindowWidth() / 2 - 300, CP_System_GetWindowHeight() / 2 - 100);
}
void main_screen_button(int num) {
	RGB rgb1, rgb2;
	if (num == 1) {
		rgb1.R = 128; rgb1.G = 128; rgb1.B = 128;
		rgb2.R = 255; rgb2.G = 255; rgb2.B = 255;
	}
	else if (num == 2) {
		rgb1.R = 255; rgb1.G = 255; rgb1.B = 255;
		rgb2.R = 128; rgb2.G = 128; rgb2.B = 128;
	}
	else {
		rgb1.R = 255; rgb1.G = 255; rgb1.B = 255;
		rgb2.R = 255; rgb2.G = 255; rgb2.B = 255;
	}
	// Start Box
	CP_Settings_Fill(CP_Color_Create(rgb1.R, rgb1.G, rgb1.B, 255));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 700, CP_System_GetWindowHeight() / 2 + 200, 600, 190);
	// Start Text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(120.0f);
	CP_Font_DrawText("START", CP_System_GetWindowWidth() / 2 - 550, CP_System_GetWindowHeight() / 2 + 330);
	// Exit Box
	CP_Settings_Fill(CP_Color_Create(rgb2.R, rgb2.G, rgb2.B, 255));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 + 100, CP_System_GetWindowHeight() / 2 + 200, 600, 190);
	// Exit Text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(120.0f);
	CP_Font_DrawText("EXIT", CP_System_GetWindowWidth() / 2 + 300, CP_System_GetWindowHeight() / 2 + 330);
}
void main_button(void) {
	if (CP_System_GetWindowWidth() / 2 - 700 <= CP_Input_GetMouseX() &&
		CP_Input_GetMouseX() <= CP_System_GetWindowWidth() / 2 - 100 &&
		CP_System_GetWindowHeight() / 2 + 200 <= CP_Input_GetMouseY() &&
		CP_Input_GetMouseY() <= CP_System_GetWindowHeight() / 2 + 390) {
		if (!isMouseHover) {
			isMouseHover = 1;
		}
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
			state = Game;
		}
		main_screen_button(1);
	}
	else if (CP_System_GetWindowWidth() / 2 + 100 <= CP_Input_GetMouseX() &&
		CP_Input_GetMouseX() <= CP_System_GetWindowWidth() / 2 + 700 &&
		CP_System_GetWindowHeight() / 2 + 200 <= CP_Input_GetMouseY() &&
		CP_Input_GetMouseY() <= CP_System_GetWindowHeight() / 2 + 390) {
		if (!isMouseHover) {
			isMouseHover = 1;
		}
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			exit(0);
		main_screen_button(2);
	}
	else {
		isMouseHover = 0;
		main_screen_button(0);
	}
}
void main_process(void) {
	// Show Screen
	main_screen_logo();
	// Button
	main_button();
}
void game_process(void) {
	CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
}
void program_process(void) {
	switch (state) {
	case 0: //
		main_process();
		break;
	case 1: // Game
		game_process();
		break;
	}
}

void Main_Menu_Init(void)
{
	state = Main;
	isMouseHover = 0;

	backgroundMusic = CP_Sound_LoadMusic("Assets/breakOutBGM.mp3");
	CP_Sound_PlayMusic(backgroundMusic);

}

void Main_Menu_Update(void)
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		exit(0);
	}
	program_process();
}

void Main_Menu_Exit(void)
{
	CP_Sound_Free(&backgroundMusic);
}
