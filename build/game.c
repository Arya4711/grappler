#include "raylib.h"

void drawWorld();

int main() {
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;
	static const int FPS = 60;
	static const char *GAME_TITLE = "Grappler";
	static Camera2D camera;
	
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
	HideCursor();
	SetTargetFPS(FPS);
	drawWorld();
	WaitTime(5);
	CloseWindow();

	return 0;
}

void drawWorld() {
	BeginDrawing();
	ClearBackground(BLUE);
	DrawRectangle(0, 500, 800, 500, DARKGRAY);
	EndDrawing();
}