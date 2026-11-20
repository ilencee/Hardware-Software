/**
 * @file    Pwr12.c
 * @brief   12V 电源控制实现
 *
 * @author  ilencee
 * @date    2026-08-17
 * @version V1.1.0
 */

#include "Pwr12.h"

/**
 * @brief  初始化 12V 电源控制引脚（推挽输出，默认关闭）
 */
void Pwr12_Init(void)
{
    rcu_periph_clock_enable(PWR12_GPIO_CLK);   /* 使能 GPIOB 时钟 */
    gpio_mode_set(PWR12_GPIO, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PWR12_PIN);
    /* 12V 开关为低速控制信号，2MHz 输出速度满足需求并降低 EMI */
    gpio_output_options_set(PWR12_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, PWR12_PIN);
    gpio_bit_reset(PWR12_GPIO, PWR12_PIN);   /* 默认关闭，避免上电误动作 */
}


/**
 * @brief  开启 12V 电源
 */
void Pwr12_On(void)
{
    gpio_bit_set(PWR12_GPIO, PWR12_PIN);
}

/**
 * @brief  关闭 12V 电源
 */
void Pwr12_Off(void)
{
    gpio_bit_reset(PWR12_GPIO, PWR12_PIN);
}

/**
 * @brief  翻转 12V 电源状态
 */
void Pwr12_Toggle(void)
{
    if (gpio_output_bit_get(PWR12_GPIO, PWR12_PIN) == RESET) {
        gpio_bit_set(PWR12_GPIO, PWR12_PIN);
    } else {
        gpio_bit_reset(PWR12_GPIO, PWR12_PIN);
    }
}
