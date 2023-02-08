/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 14:30:05
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 15:04:38
 * @FilePath: \F407IGT6_HALL\Hal\btn.c
 */
#include "btn.h"
#include "main.h"
#include "stdint.h"
#include "stdio.h"
#include "multi_button.h"
#include "bldc.h"
#include "variable.h"

static struct button key0;
static struct button key1;
static struct button key2;

const int maxDuty = 6700;
int tempDuty = 0;

static uint8_t ReadKey0()
{
    return (uint8_t)HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin);
}

static uint8_t ReadKey1()
{
    return (uint8_t)HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
}

static uint8_t ReadKey2()
{
    return (uint8_t)HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
}

void Key0_CB(void *btn)
{
    uint32_t btn_event_val;
    btn_event_val = get_button_event((struct button *)btn);

    switch (btn_event_val)
    {
    case PRESS_DOWN:
        tempDuty += 500;
        if (tempDuty >= maxDuty)
        {
            tempDuty = maxDuty / 2;
        }

        if (tempDuty >= 0)
        {
            // 顺时针转
            motorParameter.pwmDuty = tempDuty;
            motorParameter.dir = CW;
        }
        else
        {
            motorParameter.pwmDuty = -tempDuty;
            motorParameter.dir = CCW;
        }

        printf("Key0 down,pwm duty:%d\n", motorParameter.pwmDuty);
        StartMotor();
        break;
    default:
        break;
    }
}

void Key1_CB(void *btn)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch (btn_event_val)
    {
    case PRESS_DOWN:
        tempDuty -= 500;
        if (tempDuty <= -maxDuty)
        {
            tempDuty = -maxDuty / 2;
        }

        if (tempDuty >= 0)
        {
            // 顺时针转
            motorParameter.pwmDuty = tempDuty;
            motorParameter.dir = CW;
        }
        else
        {
            motorParameter.pwmDuty = -tempDuty;
            motorParameter.dir = CCW;
        }

        printf("1 down,pwm duty:%d\n", motorParameter.pwmDuty);
        StartMotor();
        break;
    default:
        break;
    }
}

void Key2_CB(void *btn)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch (btn_event_val)
    {
    case PRESS_DOWN:
        StopMotor();
        motorParameter.pwmDuty = 0;
        printf("key2 down\n");
        break;
    default:
        break;
    }
}

void BtnInit(void)
{
    button_init(&key0, ReadKey0, PRESS_DOWN);
    button_init(&key1, ReadKey1, PRESS_DOWN);
    button_init(&key2, ReadKey2, PRESS_DOWN);

    button_attach(&key0, PRESS_DOWN, Key0_CB);
    button_attach(&key1, PRESS_DOWN, Key1_CB);
    button_attach(&key2, PRESS_DOWN, Key2_CB);

    button_start(&key0);
    button_start(&key1);
    button_start(&key2);
}
