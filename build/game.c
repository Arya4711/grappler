#include "rcore.c"
#include "game.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define GRAVITY 50

int getDirectionX();
void updatePos(Player*, Rectangle*);
void updateVelocityY(Player*, bool);

int main() {
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;
	static const int FPS = 60;
	static const char* GAME_TITLE = "Grappler";
	static Player player = { { 250, 300, PLAYER_WIDTH, PLAYER_HEIGHT }, { 0, 50 } };
	static Rectangle floor = { 0, 500, 800, 300 };
	
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
	HideCursor();
	SetTargetFPS(FPS);
	while (!WindowShouldClose()) {
		updatePos(&player, &floor);
		BeginDrawing();
			ClearBackground(BLUE);
			DrawRectangleRec(floor, DARKGRAY);
			DrawRectangleRec(player.collider, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

int getDirectionX() {
	// Bools are used as ints - if both keys are pressed they cancel each other out
	return IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
}

void updateVelocityY(Player* player, bool colliding) {
	if (colliding) {
		player->velocity.y = 0;
	}

	player->velocity.y *= GRAVITY * GetFrameTime();
}

void updatePos(Player* player, Rectangle* toCollide) {
	int directionX = getDirectionX();
	updateVelocityY(player, CheckCollisionRecs(player->collider, *toCollide));
	player->collider.x += directionX * player->velocity.x * GetFrameTime();
	player->collider.y += player->velocity.y * GetFrameTime();
}