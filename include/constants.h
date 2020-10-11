#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DBG true

#define WINDOW_H 800
#define WINDOW_W 900

#define FLOOR_SIZE 1500
#define DRAW_DISTANCE 30000
#define SKY_HEIGHT 1000

// Câmeras
enum Camera {AltoTorre, Chase, ChaseLateral};
#define FATOR_LIDER_CAM_OFFSET_HORZ 300
#define FATOR_LIDER_CAM_OFFSET_VERT 100
#define PASSO 10

// Movimento do líder
#define YAW_ANGLE M_PI/20
#define PITCH_ANGLE M_PI/20

// addBoid
#define MIN_DIST_BOID 5
#define MAX_DIST_SPAWN_BOID 15

// Boid::update
#define BOID_PASSO 0.1
#define MAX_INITIAL_VEL 3
#define BOID_MAX_VEL 5
#define WING_FLAP_INTERVAL 230
#define WING_FLAP_PROP 10

// velocidadesSimilares
#define CAMPO_VISAO_INI 150
#define FATOR_VEL_LOCAL_MIN 0
#define FATOR_VEL_LOCAL_INI 0.05
#define FATOR_VEL_LOCAL_MAX 1
#define FATOR_VEL_LOCAL_DELTA 0.05

// voarParaCentro
#define FATOR_CENTRALIZAR_INI 0.0000005

// manterDistanciaOutros
#define MIN_DIST 30
#define FATOR_SEPARACAO_MIN 0
#define FATOR_SEPARACAO_INI 0.3
#define FATOR_SEPARACAO_MAX 0.8
#define FATOR_SEPARACAO_DELTA 0.005

// seguirLider
#define FATOR_LIDER_INI 0.4
#define FATOR_OBSTACULOS 0.2

// manterLimites
#define BOID_OFFSET_MARGIN 200
#define FATOR_CURVA_INI 0.03

#define FPS 60


#endif /* CONSTANTS_H */