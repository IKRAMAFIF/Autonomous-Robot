#include "MoteurPWM.h"
#include <math.h>
#include <stdlib.h>


void Moteur_init(Moteur_HandleTypeDef* moteur, TIM_HandleTypeDef* timer, uint32_t channel)
{
    moteur->pwm_timer = timer;
    moteur->channel = channel;
    moteur->direction = MOTEUR_STOP;
    moteur->vitesse = 0;

    HAL_TIM_PWM_Start(timer, channel);
    HAL_TIMEx_PWMN_Stop(timer, channel);
}


void Moteur_setSpeed(Moteur_HandleTypeDef* moteur, int percent)
{
    if (percent > 100)  percent = 100;
    if (percent < -100) percent = -100;

    moteur->vitesse = percent;

    // Conversion % -> PWM
    uint32_t pwm = (abs(percent) * SPEED_MAX_PWM) / 100;

    if (percent > 0)
    {
        Moteur_setDirection(moteur, MOTEUR_AVANCER);
        __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, pwm);
    }
    else if (percent < 0)
    {
        Moteur_setDirection(moteur, MOTEUR_RECULER);
        __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, pwm);
    }
    else
    {
        Moteur_setDirection(moteur, MOTEUR_STOP);
    }
}


void Moteur_setDirection(Moteur_HandleTypeDef* moteur, char direction)
{
    moteur->direction = direction;

    switch (direction)
    {
        case MOTEUR_AVANCER:
            HAL_TIM_PWM_Start(moteur->pwm_timer, moteur->channel);
            HAL_TIMEx_PWMN_Stop(moteur->pwm_timer, moteur->channel);
            break;

        case MOTEUR_RECULER:
            HAL_TIMEx_PWMN_Start(moteur->pwm_timer, moteur->channel);
            HAL_TIM_PWM_Stop(moteur->pwm_timer, moteur->channel);
            break;

        case MOTEUR_STOP:
        default:
            HAL_TIM_PWM_Stop(moteur->pwm_timer, moteur->channel);
            HAL_TIMEx_PWMN_Stop(moteur->pwm_timer, moteur->channel);
            __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, 0);
            break;
    }
}


void Moteur_stop(Moteur_HandleTypeDef* moteur)
{
    Moteur_setDirection(moteur, MOTEUR_STOP);
    __HAL_TIM_SET_COMPARE(moteur->pwm_timer, moteur->channel, 0);
}


void Robot_Init(h_Robot* robot, Moteur_HandleTypeDef* moteurD, Moteur_HandleTypeDef* moteurG)
{
    robot->moteur_droite = moteurD;
    robot->moteur_gauche = moteurG;

    robot->vitesse = 0;
    robot->omega = 0;
    robot->theta = 0;
    robot->direction = MOTEUR_STOP;
}


// AVANCER
void Robot_Start(h_Robot* robot, int vitesse_percent)
{
    Moteur_setSpeed(robot->moteur_droite,   vitesse_percent);
    Moteur_setSpeed(robot->moteur_gauche,  -vitesse_percent);
    robot->direction = MOTEUR_AVANCER;
}


// RECULER
void Robot_Recule(h_Robot* robot, int vitesse_percent)
{
    Moteur_setSpeed(robot->moteur_droite, -vitesse_percent);
    Moteur_setSpeed(robot->moteur_gauche,  vitesse_percent);
    robot->direction = MOTEUR_RECULER;
}


void Robot_Stop(h_Robot* robot)
{
    Moteur_stop(robot->moteur_droite);
    Moteur_stop(robot->moteur_gauche);
    robot->direction = MOTEUR_STOP;
}


// ROTATION
void Robot_setAngle(h_Robot* robot, float angle_deg, int vitesse_percent)
{
    float direction = (angle_deg > 0) ? 1 : -1;

    // moteur gauche avance, moteur droite recule (ou inverse selon ton montage)
    Moteur_setSpeed(robot->moteur_gauche,  vitesse_percent * direction);
    Moteur_setSpeed(robot->moteur_droite, -vitesse_percent * direction);

    HAL_Delay((int)(fabs(angle_deg) * 8));
    // ← 8 ms par degré → à ajuster selon ton robot

    Robot_Stop(robot);
}
