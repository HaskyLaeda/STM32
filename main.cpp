#include "includes.h"

Int8U Flag1;

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// ���������� �������. ���� ����� ������� ��� ��������� ������.
#define	ERROR_ACTION(CODE,POS)		do{}while(0)

void InitInterrupt(void)
{
 
  return;
}

void vBlinker (void *pvParameters)
{
 while(1)
 {
	GPIOB->BSRR = GPIO_BSRR_BS1;  // ������������� �� ������ PB1 �������� 1
	vTaskDelay(600);								// �������� 1500��
	GPIOB->BRR = GPIO_BRR_BR1;    // ������������� �� ������ PB1 �������� 0
	vTaskDelay(20);									// �������� 50��
 }
}

int main(void)
{  
  InitPinout();
  InitInterrupt();
  InitSysTick();
  InitUSART1();
  
if (pdTRUE != xTaskCreate(vBlinker, "Blinker", configMINIMAL_STACK_SIZE, NULL,
                          tskIDLE_PRIORITY + 1, NULL)) ERROR_ACTION(TASK_NOT_CREATE,0);	
// ������� ������.
	
// ��������� ��������� � ���������. 	
vTaskStartScheduler();  

//  while(1)
//  {
//    if (Flag1 == 1)
//    {
//      Flag1 = 0;
////      UART_SendCharPolling(USART_1, 'H');
//      UART_SendStringPolling(USART_1, (pInt8U)("Hellow world!!!  \r\n"));      
//    };    
//    GPIOB->BSRR = GPIO_BSRR_BS1;  // ������������� �� ������ PB1 �������� 1
//    for (volatile unsigned int i=0; i<2000000; i++) {}
//    GPIOB->BRR = GPIO_BRR_BR1;    // ������������� �� ������ PB1 �������� 0
//    for (volatile unsigned int i=0; i<2000000; i++) {}               
//  }
  //return 0;
};








 






