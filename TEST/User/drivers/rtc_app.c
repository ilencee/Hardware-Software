/**
 * @file    rtc_app.c
 * @brief   DS1302 时钟应用层实现
 *
 * 4 位时钟板：显示 HH:MM，中间冒号每 500ms 翻转一次。
 * 每 200ms 轮询 DS1302 秒寄存器，秒值变化才刷新完整时间缓存。
 * 冒号亮灭由独立 500ms 定时器控制，与 DS1302 读取无关。
 *
 * @author  ilencee
 * @date    2026-09-08
 * @version V1.2.0
 */

#include "rtc_app.h"
#include "systick.h"

/* 内部时间缓存 */
static rtc1302_time_t s_rtc_time = {0U};

/* 上次轮询 DS1302 的系统滴答 */
static uint32_t s_last_poll = 0U;

/* 冒号翻转计时 */
static uint32_t s_last_colon = 0U;
static uint8_t s_colon_on = 1U; /* 初始亮 */

void RtcApp_Init(void)
{
    Rtc1302_Init();

    /* 读秒寄存器原始值，检查 CH 位判断时钟是否在走 */
    uint8_t sec_reg = Rtc1302_ReadReg(DS1302_REG_SEC);

    if (sec_reg & 0x80U)
    {
        /* CH=1，时钟暂停，写入默认 12:00:00 启动走时 */
        rtc1302_time_t default_time = {0};
        default_time.hour = 12U;
        Rtc1302_SetTime(&default_time); /* 内部已管写保护 */
    }

    /* 先读一次，保证缓存立即可用 */
    Rtc1302_GetTime(&s_rtc_time);
    s_last_poll = Systick_GetTickMs();
    s_last_colon = Systick_GetTickMs();
}

void RtcApp_Process(void)
{
    uint32_t now = Systick_GetTickMs();

    /* 每 200ms 轮询 DS1302 秒值 */
    if ((now - s_last_poll) >= RTC_APP_POLL_INTERVAL_MS)
    {
        s_last_poll = now;

        /* 只读秒寄存器，判断是否变化 */
        uint8_t sec_now = Rtc1302_ReadReg(DS1302_REG_SEC) & 0x7FU; /* 屏蔽 CH 位 */
        if (sec_now != s_rtc_time.sec)
        {
            /* 秒变了，刷新完整时间 */
            Rtc1302_GetTime(&s_rtc_time);
        }
    }

    /* 冒号每 500ms 翻转一次，独立于 DS1302 读取 */
    if ((now - s_last_colon) >= RTC_APP_COLON_INTERVAL_MS)
    {
        s_last_colon = now;
        s_colon_on = (s_colon_on == 0U) ? 1U : 0U;
    }
}

const rtc1302_time_t *RtcApp_GetTime(void)
{
    return &s_rtc_time;
}

uint8_t RtcApp_IsColonOn(void)
{
    return s_colon_on;
}
