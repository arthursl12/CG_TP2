#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DBG true

#define WINDOW_H 800
#define WINDOW_W 900

#define PASSO 5

#define T_COL 10
#define MAX_COL 12
#define MIN_COL 7
#define MAX_ROW 7
#define MIN_ROW 1
#define TILE_H_W_RATIO 2.5
#define TILE_WIDTH 64
#define TILE_H_SPACE 6
#define TILE_V_SPACE 6
#define MAP_OFFSET 90
#define MIN_MAP_Y 400

#define PADDLE_HEIGHT 20
#define PADDLE_WIDTH 160
#define PADDLE_MIN_W 100
#define PADDLE_MAX_W 220
#define PADDLE_Y 55
#define PADDLE_MAX_SPEED 30
#define MOUSE_CENTER_TOLERANCE 20
#define MAX_WIDTH_SPEED_BAR 150

#define BALL_SIZE 10
#define BALL_MAX_X_SPEED 7
#define BALL_MAX_Y_SPEED 7

#define POWERUP_SIZE 30
#define POWERUP_MAX_DY 1.5
#define POWERUP_MAX_DX 2
#define POWERUP_ACC 0.05
#define POWERUP_CHANCE 0.3

#define TILE_SCORE 25

#define FPS 60

enum Cores {Vermelho, Laranja, Amarelo, Verde, Azul, Violeta, Special};
extern short sDirection;

#endif /* CONSTANTS_H */