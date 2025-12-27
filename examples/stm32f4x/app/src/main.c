#include "stm32f4xx_hal.h"
#include "main.h"
#include "sch.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart2;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void sch_task_dispatch(sch_task_t* task);
void sch_task_init(sch_task_t* task);

void echo_task_dispatch(sch_task_t* task);
void echo_task_init(sch_task_t* task);

void echo_task_dispatch(sch_task_t* task) {
  char buf[40] = {0};
  snprintf(buf, sizeof(buf), "system: %ld,\r\npreempt:%ld\r\n", sch_system_tasks_ready_set, sch_preempt_tasks_ready_set);
  HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}

void echo_task_init(sch_task_t* task) {

}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /*sch_task_t sch_task;
  sch_task_create(&sch_task, 10, 10, sch_task_dispatch, sch_task_init);
  sch_task_run(&sch_task, NULL);*/

  sch_task_t first_task;
  sch_task_create(&first_task, -3, 0, sch_task_dispatch, sch_task_init);
  sch_task_activate(&first_task);

  sch_task_t second_task;
  sch_task_create(&second_task, 3, 0, sch_task_dispatch, sch_task_init);
  sch_task_activate(&second_task);

  sch_task_t echo_data;
  sch_task_create(&echo_data, 2, 3, echo_task_dispatch, echo_task_init);
  sch_task_activate(&echo_data);
  sch_task_run(&echo_data, NULL);

  while (1)
  {
    
  }
}

void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);
}

void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 8, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 10, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void sch_task_dispatch(sch_task_t* task) {
  HAL_UART_Transmit(&huart2, (uint8_t*)"Hello\r\n", strlen("Hello\r\n"), 100);
}

void sch_task_init(sch_task_t* task) {

}

void _init(void) {

}







