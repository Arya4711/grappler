#include "rcore.c"
#include "game.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define GRAVITY 980
#define MOVE_SPEED 200
#define JUMP_FORCE 350
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int getDirectionX();
void updatePos(Player*, Rectangle*);
void updateVelocityY(Player*, Rectangle*);

int main() {
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

void updatePos(Player* player, Rectangle* toCollide) {
	// Updating velocity
	if (player->velocity.y != 0) {
		player->velocity.y += GRAVITY * GetFrameTime();
	}

	// Jump logic
	if (player->velocity.y == 0 && IsKeyPressed(KEY_SPACE)) {
		player->velocity.y = -JUMP_FORCE;
	}

	// Updating player position
	player->collider.x += MOVE_SPEED * getDirectionX() * GetFrameTime();
	player->collider.y += player->velocity.y * GetFrameTime();

	// Checks if the player moved off the screen and moves the player back if so
	if (player->collider.x + PLAYER_WIDTH > SCREEN_WIDTH) {
		player->collider.x = SCREEN_WIDTH - PLAYER_WIDTH;
	} else if (player->collider.x < 0) {
		player->collider.x = 0;
	}

	// Checks if the player moved below the floor and moves the player back if so - also nulls velocity
	if (player->collider.y + PLAYER_HEIGHT > toCollide->y) {
		player->collider.y = toCollide->y - PLAYER_HEIGHT;
		player->velocity.y = 0;
	}
}