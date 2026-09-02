/**
 * @file    Pwr12.h
 * @brief   12V 电源控制接口声明
 *
 * @author  ilencee
 * @date    2026-08-17
 * @version V1.1.0
 */

#ifndef _PWR12_H_
#define _PWR12_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gd32e23x.h"

/* ===== 引脚配置（默认 PB8，按实际硬件接线修改） ===== */
#define PWR12_PIN      GPIO_PIN_1
#define PWR12_GPIO     GPIOA
#define PWR12_GPIO_CLK RCU_GPIOA

/**
 * @brief  初始化 12V 电源控制引脚（推挽输出，默认关闭）
 */
void Pwr12_Init(void);

/**
 * @brief  开启 12V 电源
 */
void Pwr12_On(void);

/**
 * @brief  关闭 12V 电源
 */
void Pwr12_Off(void);

/**
 * @brief  翻转 12V 电源状态
 */
void Pwr12_Toggle(void);

#ifdef __cplusplus
}
#endif

#endif /* _PWR12_H_ */
