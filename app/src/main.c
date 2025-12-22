#include "stm32f4xx_hal.h"
#include "main.h"

int main(void)
{
    /* Инициализация HAL:
       - SysTick
       - NVIC
       - внутренние структуры */
    HAL_Init();

    /* Настройка системной частоты */
    SystemClock_Config();

    /* Включаем тактирование GPIOA */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};

    gpio.Pin   = GPIO_PIN_5;              /* PA5 (LED на Nucleo) */
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &gpio);

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
}

void _init(void) {}

