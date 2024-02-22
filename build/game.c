#include "rcore.c"
#include "game.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define GRAVITY 10

Vector2 getDirection();
void updatePos(Player*);

int main() {
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;
	static const int FPS = 60;
	static const char *GAME_TITLE = "Grappler";
	static Player player = { { 250, 400, PLAYER_WIDTH, PLAYER_HEIGHT }, { 0, 0 } };
	static Rectangle floor = { 0, 500, 800, 500 };
	
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
	HideCursor();
	SetTargetFPS(FPS);
	while (!WindowShouldClose()) {
		updatePos(&player);
		BeginDrawing();
			ClearBackground(BLUE);
			DrawRectangleRec(floor, DARKGRAY);
			DrawRectangleRec(player.collider, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

Vector2 getDirection() {
	Vector2 direction = { 0, 0 };

	// Bools are used as ints - if both keys are pressed they cancel each other out
	direction.x += IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

	return direction;
}

void updatePos(Player* player) {
	Vector2 direction = getDirection();
	float deltaTime = GetFrameTime();
	player->collider.x += direction.x * player->velocity.x * deltaTime;
	player->collider.y += direction.y * player->velocity.y * deltaTime;
}