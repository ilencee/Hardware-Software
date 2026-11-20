/**
 * @file    main.c
 * @brief   主程序入口
 *
 * @author  ilencee
 * @date    2026-08-15
 * @version V2.1.0
 */

#include "gd32e23x.h"
#include "systick.h"
#include "disp.h"
#include "fan.h"
#include "pump.h"
#include "uart.h"
#include "zero.h"
#include "Pwr12.h"
#include "triac.h"
#include "rtc_app.h"

/* 主循环节拍（单位 ms） */
#define MAIN_LOOP_PERIOD_MS 1U

int main(void)
{
    Systick_Config();
    Fan_Init();
    Pump_Init();
    Triac_Init();
    Pwr12_Init();
    Uart_Init();    /* 初始化与显示板通信的串口（USART1 @ PA2/PA3） */
    //Zero_Init();    /* 启用市电过零检测（PB0 + EXTI0 双边沿中断） */
    //Disp_Init();    /* 复位显示板协议解析状态机与统计计数 */

    /* 上电后直接开启风扇与水泵 */
    Fan_On();
    Pump_On();
    Pwr12_On();
    Triac_OnAll();   /* 上电后直接开启四路可控硅负载（HEAT/PTC/UVA/UVB） */

    /* 初始化 DS1302，上电默认 12:00:00 */
    RtcApp_Init();

    while (1) {
        //Disp_Process();
        //Uart_EchoTest();    /* 串口回显测试 */

        /* 每 500ms 读一次 DS1302 时间 */
        RtcApp_Process();

        /* 用时示例：const rtc1302_time_t *t = RtcApp_GetTime(); t->hour / t->min / t->sec */

        Systick_DelayMs(MAIN_LOOP_PERIOD_MS);
    }
}
