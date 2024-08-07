/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "tim.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t dataReceive;
#define bitcheck(byte,nbit) ((byte) & (1<<(nbit)))
uint8_t data[3];
uint16_t pwm;
uint8_t flagReceive;

void Set_PWM_Duty_Cycle(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t pwm)
{
    __HAL_TIM_SET_COMPARE(htim, Channel, pwm);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
          if(huart == &huart1)
          {
        	  HAL_UART_Receive_IT(&huart1, &dataReceive, 1);
          }
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for bitChecking */
osThreadId_t bitCheckingHandle;
const osThreadAttr_t bitChecking_attributes = {
  .name = "bitChecking",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for pwmSet */
osThreadId_t pwmSetHandle;
const osThreadAttr_t pwmSet_attributes = {
  .name = "pwmSet",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ledBlink */
osThreadId_t ledBlinkHandle;
const osThreadAttr_t ledBlink_attributes = {
  .name = "ledBlink",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartBitChecking(void *argument);
void StartPWM_Set(void *argument);
void StartLedBlink(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	/*HAL_UART_Receive_IT(&huart1, &dataReceive, 1);*/
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_UART_Receive_IT(&huart1, &dataReceive, 1);
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of bitChecking */
  bitCheckingHandle = osThreadNew(StartBitChecking, NULL, &bitChecking_attributes);

  /* creation of pwmSet */
  pwmSetHandle = osThreadNew(StartPWM_Set, NULL, &pwmSet_attributes);

  /* creation of ledBlink */
  ledBlinkHandle = osThreadNew(StartLedBlink, NULL, &ledBlink_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartBitChecking */
/**
* @brief Function implementing the bitChecking thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBitChecking */
void StartBitChecking(void *argument)
{
  /* USER CODE BEGIN StartBitChecking */
	int count;
  /* Infinite loop */
  for(;;)
  {
		if (bitcheck(dataReceive, 7)) {
			count++;
			data[count] = dataReceive;
		} else {
			count = 0;
			data[count] = dataReceive;
		}
    osDelay(1);
  }
  /* USER CODE END StartBitChecking */
}

/* USER CODE BEGIN Header_StartPWM_Set */
/**
* @brief Function implementing the pwmSet thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPWM_Set */
void StartPWM_Set(void *argument)
{
  /* USER CODE BEGIN StartPWM_Set */
  /* Infinite loop */
  for(;;)
  {
	if(bitcheck(data[0], 6)){
		pwm = (uint16_t)(data[1]&255)*20;
	}
	else{
		pwm = (uint16_t)(data[1]&127)*20;
	}
    osDelay(1);
  }
  /* USER CODE END StartPWM_Set */
}

/* USER CODE BEGIN Header_StartLedBlink */
/**
* @brief Function implementing the ledBlink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLedBlink */
void StartLedBlink(void *argument)
{
  /* USER CODE BEGIN StartLedBlink */

  /* Infinite loop */
  for(;;)
  {
	Set_PWM_Duty_Cycle(&htim1, TIM_CHANNEL_1, pwm);
    osDelay(1);
  }
  /* USER CODE END StartLedBlink */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

