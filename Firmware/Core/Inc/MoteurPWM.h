#ifndef MOTEURPWM_H
#define MOTEURPWM_H

#include "tim.h"
#include "stdint.h"

// Directions
#define MOTEUR_AVANCER 'A'
#define MOTEUR_RECULER 'R'
#define MOTEUR_STOP    'S'

// Robot params
#define Ts   0.01f         // période échantillonnage
#define L    0.158f        // distance entre roues (m)
#define SPEED_MAX_PWM 8500 // ARR max



typedef struct {
    TIM_HandleTypeDef* pwm_timer;
    uint32_t channel;
    char direction;
    int vitesse;
} Moteur_HandleTypeDef;

typedef struct {
    float vitesse;
    float omega;
    float theta;
    char direction;

    Moteur_HandleTypeDef* moteur_droite;
    Moteur_HandleTypeDef* moteur_gauche;
} h_Robot;


void Moteur_init(Moteur_HandleTypeDef* moteur, TIM_HandleTypeDef* timer, uint32_t channel);
void Moteur_setSpeed(Moteur_HandleTypeDef* moteur, int percent);
void Moteur_setDirection(Moteur_HandleTypeDef* moteur, char direction);
void Moteur_stop(Moteur_HandleTypeDef* moteur);


void Robot_Init(h_Robot* robot, Moteur_HandleTypeDef* moteurD, Moteur_HandleTypeDef* moteurG);
void Robot_Start(h_Robot* robot, int vitesse_percent);
void Robot_Recule(h_Robot* robot, int vitesse_percent);
void Robot_Stop(h_Robot* robot);
void Robot_setAngle(h_Robot* robot, float angle_deg, int vitesse_percent);

#endif
