#define _SHELL_C_SRC

//-------------------------MODULES USED-------------------------------------
#include <string.h>
#include "stm32f3xx_hal.h"
#include "main.h"
#include "ledctrl.h"
#include "shell.h"

//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------
static void MX_USART2_UART_Init(void);
static void handle_rx_bytes(char * p_byte);


//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------

const char c_menu[] = "\
****************************************\r\n\
*                                      *\r\n\
*   Welcome to Lager's Peripheral Demo *\r\n\
*--------------------------------------*\r\n\
*                                      *\r\n\
*                                      *\r\n\
* 'h' - Print \"Hello World\"            *\r\n\
* 'l' - Turn On Led                    *\r\n\
* 'k' - Turn Off Led                   *\r\n\
*                                      *\r\n\
*                                      *\r\n\
****************************************\r\n";

static UART_HandleTypeDef g_huart2;

//-------------------------EXPORTED FUNCTIONS-------------------------------
void shell_init(void)
{
	MX_USART2_UART_Init();
	const char demo_msg[] = "Welcome to lager stm32l0 demo\r\n";
	HAL_UART_Transmit(&g_huart2, (uint8_t *)demo_msg, sizeof(demo_msg), 0xffffffff);

}

void shell_run(void)
{
	char c = 0;
	while('q' != c){
		c = 0;
		HAL_UART_Receive(&g_huart2, (uint8_t *)&c, sizeof(c), 0x10);
		if(0 != c){
			handle_rx_bytes(&c);
		}
	}
}

//-------------------------LOCAL FUNCTIONS----------------------------------
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  g_huart2.Instance = USART2;
  g_huart2.Init.BaudRate = 115200;
  g_huart2.Init.WordLength = UART_WORDLENGTH_8B;
  g_huart2.Init.StopBits = UART_STOPBITS_1;
  g_huart2.Init.Parity = UART_PARITY_NONE;
  g_huart2.Init.Mode = UART_MODE_TX_RX;
  g_huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  g_huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  g_huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  g_huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&g_huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}


static void handle_rx_bytes(char * p_byte)
{
    switch(*p_byte){
        case 'h':{
            HAL_UART_Transmit(&g_huart2, (uint8_t *)"Hello World\r\n", sizeof("Hello World\r\n"), 0xffffffff);
            break;
        }

        case 'l':{
            const char led_on_msg[] = "Turning on LED 0.\r\n";
            HAL_UART_Transmit(&g_huart2, (uint8_t *)led_on_msg, sizeof(led_on_msg), 0xffffffff);
            ledctrl_onoff(true);

            break;
        }

        case 'k':{
            const char led_off_msg[] = "Turning off LED 0.\r\n";
            HAL_UART_Transmit(&g_huart2, (uint8_t *)led_off_msg, sizeof(led_off_msg), 0xffffffff);
            ledctrl_onoff(false);

            break;
        }



        default:{
        	HAL_UART_Transmit(&g_huart2, (uint8_t *)c_menu, sizeof(c_menu), 0xffffffff);
            break;
        }
    }
}



