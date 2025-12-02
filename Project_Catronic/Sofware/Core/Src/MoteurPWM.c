#include "MoteurPWM.h"
#include <stdlib.h>
#include <math.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;   // Encoder moteur 2
extern TIM_HandleTypeDef htim4;   // Encoder moteur 1

void Motor_Init(void)
{
    // Moteur 2 → CH1 / CH1N
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);		// Forward
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	// Reverse

    // Moteur 1 → CH2 / CH2N
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

    // duty = 0 %
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    __HAL_TIM_SET_COUNTER(&htim3, 0);
    __HAL_TIM_SET_COUNTER(&htim4, 0);
}

void Motor_SetSpeed(MotorID motor, int speed)
{
    if (speed > 100)  speed = 100;
    if (speed < -100) speed = -100;

    uint32_t pwm = (abs(speed) * htim1.Instance->ARR) / 100;

    if (motor == MOTOR_1)
    {
        // MOTEUR 1 → TIM1_CH2 / TIM1_CH2N
        if (speed > 0)          // AVANT
        {
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
        }
        else if (speed < 0)     // ARRIÈRE
        {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
        }
        else                    // STOP
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
        }
    }
    else  // MOTOR_2
    {
        // MOTEUR 2 → TIM1_CH1 / TIM1_CH1N
        if (speed > 0)          // AVANT
        {
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
        }
        else if (speed < 0)     // ARRIÈRE
        {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
        }
        else                    // STOP
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
        }
    }
}


void Motor_Stop(MotorID motor)
{
    Motor_SetSpeed(motor, 0);
}

void Encoder_Reset(EncoderID enc)
{
    if (enc == ENCODER_1)
        __HAL_TIM_SET_COUNTER(&htim4, 0);
    else
        __HAL_TIM_SET_COUNTER(&htim3, 0);
}

int32_t Encoder_GetCount(EncoderID enc)
{
    if (enc == ENCODER_1)
        return __HAL_TIM_GET_COUNTER(&htim4);
    else
        return __HAL_TIM_GET_COUNTER(&htim3);
}

void Motor_SetAngle(float angle_deg)
{
	//ticks_per_deg = ticks_par_tour_de_roue * (L / (diametre_roue * 360));
	float ticks_per_deg = 5.3f;
    int speed = 50;

    // Reset encodeurs
    Encoder_Reset(ENCODER_1);
    Encoder_Reset(ENCODER_2);

    int direction = (angle_deg > 0) ? 1 : -1;
    speed *= direction;

    while (1)
    {
        int32_t m1 = Encoder_GetCount(ENCODER_1);
        int32_t m2 = Encoder_GetCount(ENCODER_2);

        int32_t delta = (m1 - m2);
        float angle_now = delta / ticks_per_deg;

        if (fabs(angle_now) >= fabs(angle_deg))
            break;

        Motor_SetSpeed(MOTOR_1,  speed);
        Motor_SetSpeed(MOTOR_2, -speed);

        HAL_Delay(5);
    }

    Motor_Stop(MOTOR_1);
    Motor_Stop(MOTOR_2);
}

