// 예외처리
#define _CRT_SECURE_NO_WARNINGS    // sprintf 보안 경고로 인한 컴파일 에러 방지
#pragma warning( disable : 4244 ) // C4244

// 선언
#include "cprocessing.h"
#include "logic.h"
#include "setting.h"
#include "color.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// 정의
#define board_width 10
#define board_height 20
#define board_space_length 20
#define board_space_interval_length 2
#define board_location_x 600
#define board_location_y 150

#define button_interval_length_x 20
#define button_interval_length_y 20
#define button_w 60
#define button_h 20
#define button_text_size 15
#define button_textInterval_x 10
#define button_textInterval_y 15

#define frame_interval 4

#define pause_frame_size_w 1000
#define pause_frame_size_h 700
#define puase_textsize1 120
#define puase_textsize2 60


// 열거형
enum gameState {
	Notyet,
	Processing,
	Pause,
	Setting,
	End,
} gameState;

// 구조체
struct Button {
	int isHovered; 
	float x;
	float y;
	float w;
	float h;
	char* text;
	float textSize;
	float textInterval_x;
	float textInterval_y;
}typedef Button;
struct board_space {
	float window_x; // 화면 상의 x 위치 값
	float window_y; // 화면 상의 y 위치 값
	int is_filled; // 0,1 값을 가지는 해당 칸의 채워짐 유무
} typedef board_space;

// 상수
const float board_size_x = board_width * (board_space_length + board_space_interval_length) + board_space_interval_length;
const float board_size_y = board_height * (board_space_length + board_space_interval_length) + board_space_interval_length;


// 전역 변수
board_space board[board_width][board_height];

Button restartButton;
Button settingButton;

float window_middle_w;
float window_middle_h;

int EffectCount;

// 함수
void DrawRect(float x, float y, float w, float h, int color) {
	CP_Settings_Fill(CP_Color_CreateHex(color));
	CP_Graphics_DrawRect(x, y, w, h);
}
void DrawFrame() {
	float fi2 = frame_interval * 2;
	DrawRect(board_location_x - fi2, board_location_y - fi2, board_size_x-2, board_size_y + fi2 * 2, White);
	DrawRect(board_location_x, board_location_y , board_size_x - 18, board_size_y, Black);
}
void ShowExamBoard() {
	for (int i = 0; i < board_width; i++) {
		for (int j = 0; j < board_height; j++) {
			DrawRect(board[i][j].window_x, board[i][j].window_y, board_space_length, board_space_length, White);
		}
	}
}
void BoardInit(float loc_x, float loc_y) {
	for (int i = 0; i < board_width; i++) {
		for (int j = 0; j < board_height; j++) {
			board[i][j].window_x = board_space_interval_length + (i * board_space_length) + loc_x;
			board[i][j].window_y = board_size_y - ((board_space_interval_length + board_space_length) * (j + 1)) + loc_y;
			board[i][j].is_filled = 0;
		}
	}
}
void ButtonInit(void) {
	// Init restartButton
	restartButton.isHovered = 0;
	restartButton.x = board_size_x / 2 + board_location_x - button_w - button_interval_length_x;
	restartButton.y = board_size_y + board_location_y + button_interval_length_y;
	restartButton.w = button_w;
	restartButton.h = button_h;
	restartButton.text = "Restart";
	restartButton.textSize = button_text_size;
	restartButton.textInterval_x = button_textInterval_x;
	restartButton.textInterval_y = button_textInterval_y;

	// Init settingButton
	settingButton.isHovered = 0;
	settingButton.x = restartButton.x + button_w + button_interval_length_x;
	settingButton.y = restartButton.y;
	settingButton.w = button_w;
	settingButton.h = button_h;
	settingButton.text = "Setting";
	settingButton.textSize = button_text_size;
	settingButton.textInterval_x = button_textInterval_x;
	settingButton.textInterval_y = button_textInterval_y;
}
int IsHoveredFunc(Button button) {
	float mx = CP_Input_GetMouseX(), my = CP_Input_GetMouseY();
	if (button.x <= mx && mx <= button.x + button.w && button.y <= my && my <= button.y + button.h)
		return 1;
	else
		return 0;
}
void GameScreenButton(Button button) {
	// Start Box
	CP_Settings_Fill(CP_Color_CreateHex(button.isHovered ? Gray : White));
	CP_Graphics_DrawRect(button.x, button.y, button.w, button.h);
	// Start Text
	CP_Settings_Fill(CP_Color_CreateHex(Black));
	CP_Settings_TextSize(button.textSize);
	CP_Font_DrawText(button.text, button.x + button.textInterval_x, button.y + button.textInterval_y);
}
int StartEffect(void) {
	// 이펙트가 안끝났다면 0, 끝나면 1을 반환
	// 차후 구현
	return 1;
} //Yet
void StartingGame(void) {
	//시작 이펙트 후 진행
	if (StartEffect()) {
		gameState = Processing;
	}
}
void EndState(void) {

}
void SettingState(void) {

}
void PauseState(void) {
	if (CP_Input_KeyTriggered(KEY_P)) {
		gameState = Processing;
		return;
	}
	DrawRect(window_middle_w - pause_frame_size_w/2, window_middle_h - pause_frame_size_h / 2, pause_frame_size_w, pause_frame_size_h, White);
	CP_Settings_Fill(CP_Color_CreateHex(Black));
	CP_Settings_TextSize(puase_textsize1);
	CP_Font_DrawText("Pause", window_middle_w - 160, window_middle_h - 80);

	CP_Settings_TextSize(puase_textsize2);
	CP_Font_DrawText("If you want to retry, you push the 'R'", window_middle_w - 400, window_middle_h + 30);
	CP_Font_DrawText("otherwise you push the 'P' again!", window_middle_w - 380, window_middle_h + 100);
}
void GameButton(void) {
	if (IsHoveredFunc(restartButton)) {
		restartButton.isHovered = 1;
		settingButton.isHovered = 0;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
			StartingGame();
		}
	}
	else if (IsHoveredFunc(settingButton)) {
		restartButton.isHovered = 0;
		settingButton.isHovered = 1;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
			if (gameState == Processing) {
				gameState = Setting;
			}
		}
	}
	else {
		restartButton.isHovered = 0;
		settingButton.isHovered = 0;
	}
	GameScreenButton(restartButton);
	GameScreenButton(settingButton);
}
void ShowHoldBlock(void){

} // Yet
void ShowInfo(void) {

} // Yet
void GUI(void) {
	CP_Graphics_ClearBackground(CP_Color_CreateHex(Black));
	DrawFrame();
	GameButton();
	ShowHoldBlock();
	ShowInfo();
}

// 프로세스 함수
void GameProcess(void) {
	GUI();
	BlockProcess();
	//ShowExamBoard();
}

// 싸이클 함수
void Game_Init(void)
{
	window_middle_w = CP_System_GetWindowWidth() / 2;
	window_middle_h = CP_System_GetWindowHeight() / 2;
	BoardInit(board_location_x, board_location_y);
	ButtonInit();
	gameState = Notyet;
	EffectCount = 0;
}

void Game_Update(void)
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		exit(0);
	}

	switch (gameState) {
		case Notyet :
			//시작하기 버튼 누르기
			GUI();
			if (CP_Input_KeyTriggered(KEY_R)) {
				BoardInit(board_location_x, board_location_y);
				StartingGame();
			}
			break;
		case Processing :
			if (CP_Input_KeyTriggered(KEY_P)) {
				gameState = Pause;
				break;
			}
			GameProcess();
			break;
		case Pause :
			PauseState();
			break;
		case Setting : 
			SettingState();
			break;
		case End :
			EndState();
			break;
	}	
}

void Game_Exit(void)
{

}