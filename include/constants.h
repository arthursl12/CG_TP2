#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DBG true

#define WINDOW_H 800
#define WINDOW_W 900

#define FLOOR_SIZE 1500
#define DRAW_DISTANCE 30000
#define SKY_HEIGHT 1000

#define PASSO 10

// addBoid
#define MIN_DIST_BOID 5
#define MAX_DIST_SPAWN_BOID 15

// Boid::update
#define BOID_PASSO 0.1
#define MAX_INITIAL_VEL 3
#define BOID_MAX_VEL 5

// velocidadesSimilares
#define CAMPO_VISAO 150
// #define FATOR_VEL_LOCAL 0.005

// voarParaCentro
// #define FATOR_CENTRALIZAR 0.005

// manterDistanciaOutros
#define FATOR_SEPARACAO_MIN 0
#define FATOR_SEPARACAO_INI 0.005
#define FATOR_SEPARACAO_MAX 0.8
#define FATOR_SEPARACAO_DELTA 0.005
#define MIN_DIST 30

// manterLimites
#define BOID_OFFSET_MARGIN 200
#define FATOR_CURVA_MIN 0.015
#define FATOR_CURVA_INI 0.03
#define FATOR_CURVA_MAX 0.035
#define FATOR_CURVA_DELTA 0.002

#define FPS 60


#endif /* CONSTANTS_H */