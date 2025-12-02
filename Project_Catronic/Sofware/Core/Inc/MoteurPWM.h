#ifndef MOTEURPWM_H
#define MOTEURPWM_H

#include "tim.h"
#include <stdint.h>

typedef enum {
    MOTOR_1 = 0,   // CH2 / CH2N
    MOTOR_2 = 1    // CH1 / CH1N
} MotorID;
typedef enum {
    ENCODER_1 = 0,   // Moteur 1 → TIM4 (PA11 B1, PA12 A1)
    ENCODER_2 = 1    // Moteur 2 → TIM3 (PC6 B2, PA5 A2)
} EncoderID;

void Motor_Init(void);
void Motor_SetSpeed(MotorID motor, int speed);
void Motor_Stop(MotorID motor);

void Encoder_Reset(EncoderID enc);
int32_t Encoder_GetCount(EncoderID enc);
void Motor_SetAngle(float angle_deg);
#endif
