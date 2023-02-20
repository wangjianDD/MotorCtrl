/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 15:37:33
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-20 09:47:44
 * @FilePath: \F401RET6_Pump\Hal\tm1650.c
 */
#include "tm1650.h"
#include "cmsis_os.h"
#include "main.h"
#include "softiic.h"

static uint8_t s_7number[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00}; // 7段显示方式0~9 第10位为不显示位
static uint8_t s_8number[11] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x00}; // 8段显示方式0~9

/**
 * @brief TM1650写
 *
 * @param addr
 * @param data
 */
void TM1650_Write(uint8_t addr, uint8_t data)
{
    iic_start();        // 发送起始信号
    iic_sendByte(addr); // 写地址
    iic_waitAck();      // 等待应答
    iic_sendByte(data); // 写入数据
    iic_ack();          // 发送应答
    iic_stop();         // 发送停止信号
}

/**
 * @brief TM1650设置显示模式
 *
 * @param brightness
 * @param mode
 * @param state
 */
void TM1650_SetDisplay(uint8_t brightness, uint8_t mode, uint8_t state)
{
    if (state)
    {
        if (mode == 7) // 7段显示方式
        {
            TM1650_Write(0x48, brightness * 16 + 1 * 4 + 1);
        }
        else if (mode == 8) // 8段显示方式
        {
            TM1650_Write(0x48, brightness * 16 + 1);
        }
    }
    else
    {
        TM1650_Write(0x48, 0x00); // 关闭显示
    }
}

/**
 * @brief TM1650清空缓存
 *
 */
void TM1650_Clear(void)
{
    for (uint8_t j = 0; j < 4; j++)
    {
        TM1650_SetIndexNumber(j, 7, 10);
    }
}

/**
 * @brief TM1650 4位单独设置数字
 *
 * @param index
 * @param mode
 * @param num
 */
void TM1650_SetIndexNumber(uint8_t index, uint8_t mode, uint8_t num)
{
    uint8_t indexAddr = 0;
    uint8_t numValue = 0;

    if (mode == 7) // 7段显示方式
    {
        numValue = s_7number[num];
    }
    else if (mode == 8) // 8段显示方式
    {
        numValue = s_8number[num];
    }

    if (index == 0)
    {
        indexAddr = 0x68;
    }
    else if (index == 1)
    {
        indexAddr = 0x6A;
    }
    else if (index == 2)
    {
        indexAddr = 0x6C;
    }
    else if (index == 3)
    {
        indexAddr = 0x6E;
    }

    TM1650_Write(indexAddr, numValue);
}

/**
 * @brief TM1650直接设置数字显示
 *
 * @param num
 */
void TM1650_SetNumber(uint16_t num)
{
    TM1650_Clear();
    uint8_t index = 3;
    if (num > 9999)
    {
        return;
    }

    // 拆分位数
    while (num)
    {
        TM1650_SetIndexNumber(index, 7, num % 10);
        index--;
        num /= 10;
    }
}