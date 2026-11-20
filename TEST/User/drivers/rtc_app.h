/**
 * @file    rtc_app.h
 * @brief   DS1302 时钟应用层接口声明
 *
 * 4 位时钟板：显示 HH:MM，中间冒号每 500ms 翻转一次。
 * DS1302 周期检测秒值变化刷新缓存，冒号由独立 500ms 定时器控制。
 *
 * @author  ilencee
 * @date    2026-09-08
 * @version V1.2.0
 */

#ifndef _RTC_APP_H_
#define _RTC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "1302.h"

/* 每 200ms 轮询 DS1302 秒值是否变化 */
#define RTC_APP_POLL_INTERVAL_MS   200U

/* 冒号每 500ms 翻转一次（亮 500ms / 灭 500ms） */
#define RTC_APP_COLON_INTERVAL_MS  500U

/**
 * @brief  初始化 DS1302，上电若时钟暂停则写 12:00:00 启动走时
 */
void RtcApp_Init(void);

/**
 * @brief  主循环调用，检测秒值变化时刷新时间缓存
 */
void RtcApp_Process(void);

/**
 * @brief  获取最近一次读取到的时间（十进制）
 * @return 时间结构体指针（始终非空，指向内部静态变量）
 */
const rtc1302_time_t *RtcApp_GetTime(void);

/**
 * @brief  冒号是否点亮（每 500ms 翻转一次）
 * @return 1=亮，0=灭
 */
uint8_t RtcApp_IsColonOn(void);

#ifdef __cplusplus
}
#endif

#endif /* _RTC_APP_H_ */
