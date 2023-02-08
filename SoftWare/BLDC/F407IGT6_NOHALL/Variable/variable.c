/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 11:18:28
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 16:57:15
 * @FilePath: \F407IGT6_NOHALL\Variable\variable.c
 */
#include "variable.h"

MotorParameter motorParameter;

void VariableInit(void)
{
    motorParameter.dir = CW; // 默认顺时针
    motorParameter.hallState = 0;
    motorParameter.pwmDuty = 0;
    motorParameter.isStart = 0;
    motorParameter.maxDuty = 8000;
}
