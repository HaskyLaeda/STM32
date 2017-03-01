//======================================================================================================================
//  28.06.2015         ver.  0.0.1             Name: STM32F10xXX_USART.h
//  Name: STM32F10xXX_USART.h
//  Description: Different function for init and direct USARTx of STM32F10xXX Series
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#ifndef __STM32F10xXX_USART_H          // Avoid multiple inclusion
  #define __STM32F10xXX_USART_H
  
  #include "includes.h"                  // Master file of includes
  #include "DataTypes.h"

  #ifdef __cplusplus
    extern "C"
    {
  #endif


//======================================================================================================================
//                                               Macros
//======================================================================================================================

    // Uart channel
  #define USART_1                 (0x1)
  #define USART_2                 (0x2)
  #define USART_3                 (0x3)
  #define UART_4                  (0x4)
  #define UART_5                  (0x5)
  

  #define RX_BUFFER_SIZE          (256)     // Размер буфера приема модулей UART
  #define TX_BUFFER_SIZE          (256)     // Размер буфера передачи модулей UART
//  #define FIFODEEP                (16)      // Размер аппаратных буферов передачи и приема

    // Standart Baudrate
  #define BR_115200               (115200)  // Cкорость 115200 бод
  #define BR_57600                (57600)   // Cкорость 57600 бод
  #define BR_38400                (38400)   // Cкорость 38400 бод
  #define BR_19200                (19200)   // Cкорость 19200 бод
  #define BR_9600                 (9600)    // Cкорость 9600 бод

    // Uart Interrupt Identification
  #define IIR_RSL                 (0x3)
  #define IIR_RDA                 (0x2)
  #define IIR_CTI                 (0x6)
  #define IIR_THRE                (0x1)





//======================================================================================================================
//                                               Types
//======================================================================================================================
   
   // Word Length type
typedef enum
{
    WordLength5 = 0,   // Длина данных в посылке 5 bit
    WordLength6 = 1,   // Длина данных в посылке 6 bit
    WordLength7 = 2,   // Длина данных в посылке 7 bit
    WordLength8 = 3    // Длина данных в посылке 8 bit
} TUART_WordLength;

  // Parity Select type
typedef enum
{
    StopBitOne = 0,    // Один стоповый бит
    StopBitTwo = 1,    // Два стоповых бита
} TStopBitNum;

  // Parity Select type
typedef enum
{
    ParityOdd       = 0,  // Проверка на нечетность
    ParityEven      = 1,  // Проверка на четность
    ParityStickHigh = 2,  // Устанавливается логическая 1 в бите четности
    ParityEvenLow   = 3,  // Устанавливается логический 0 в бите четности
    ParityNone      = 4   // Нет проверки на четность
} TUART_Parity;

  // FIFO Rx Trigger Level type ( уровень срабатывания защелки(прерывание(RDA) при приеме))
typedef enum
{
    FIFO_RX_Level0 = 0,   // 0x1    1 байт
    FIFO_RX_Level1 = 1,   // 0x4    4 байт
    FIFO_RX_Level2 = 2,   // 0x8    8 байт
    FIFO_RX_Level3 = 3    // 0xe   14 байт
} TUART_FIFO_RxTriggerLevel;

  // UART Interrupt type
typedef enum
{
    NoneInterrupt = 0,
    RBR       = (1 << 0),  // RDA, CRT/CTI
    THRE      = (1 << 1),  // THRE
    RLS       = (1 << 2),  // OE, PE, FE, RXFE
    ABTOIntEn = (1 << 8),  //
    ABEOIntEn = (1 << 9),
} TUART_InterruptEnable;

typedef struct
{
    Int8U RxBuffer[RX_BUFFER_SIZE];  // Буффер приема
    Int8U TxBuffer[TX_BUFFER_SIZE];  // Буффер передачи
    Int32U RxHeadPoint;              // Указатель на начало буффера приема
    Int32U RxTailPoint;              // Указатель на конец буффера передачи
    Int32U TxHeadPoint;              // Указатель на начало буффера приема
    Int32U TxTailPoint;              // Указатель на конец буффера передачи
    Int32U RxCount;                  // Количество байт в буффере приема
    Int32U TxCount;                  // Количество байт в буффере передачи
    union
    {
      Int32U ErrorFlags;             // Флаги ошибок
      struct
      {
        Int32U FIFO_OverrunError : 1;
        Int32U OverrunError      : 1;
        Int32U ParityError       : 1;
        Int32U FramingError      : 1;
        Int32U BreakIndication   : 1;
      };
    };
} TUART_Buffer;

typedef struct
{
    Int32U BaudRate;              // Baud Rate (Скорость max 115200 бод)
    TUART_WordLength WordLength;  // Длина передаваемых данных (WordLength5 ... WordLength8)
    TStopBitNum StopBitNum;       // Количество стоповых битов (StopBitOne or StopBitTwo)
    TUART_Parity UART_Parity;     // Parity mode (Режимы четности ParityOdd, ParityEven, ParityStickHigh, ParityEvenLow or ParityNone)
    bool BreakEnable;             // (Разрешить передачу останова ?)
    bool FIFO_Enable;             // (Использовать ли  FIFO буфер ?)
    TUART_FIFO_RxTriggerLevel FIFO_RxTriggerLevel;  // (Уровень заполнения аппаратного буффера для возникновения прерывания)
    Int32U InterruptEnable ;      // Interrupt Type: RBR, THRE, RLS
    TUART_Buffer UART_Buffer;     // Буффер приема и передачи
} TUART_Config;

//======================================================================================================================
//                                               Interface
//======================================================================================================================

void InitUSART1(void);


//Int32 UART_Init(TUART_Channel UART_Num, Int32U Fpclk, Int32U BaudRate, TUART_WordLength WordLength,
//                TStopBitNum StopBitNum, TUART_Parity UART_Parity, bool BreakEnable, bool FIFO_Enable,
//                TUART_FIFO_RxTriggerLevel FIFO_RxTriggerLevel, Int32U InterruptEnable);
//Int32  UART_SetConfig(TUART_Channel UART_Num, Int32U Fpclk);

Int32  UART_SendCharPolling(Int32U UART_Channel, Int8U DataChar);
Int32U UART_SendStringPolling(Int32U UART_Channel, pInt8U pString);
Int32U UART_SendDataPolling(Int32U UART_Channel, pInt8U pDataBlock, Int32U SizeDataBlock);
Int32  UART_GetCharPolling(Int32U UART_Channel, Int8U *Buf);
//
//Int32U UART_SendString(TUART_Channel UART_Num, Int8U *Buf);
//Int32  UART_SendChar( TUART_Channel UART_Num, Int8U DataChar);
//Int32  UART_GetChar(TUART_Channel UART_Num, Int8U *ch);
//
//void ISR_UART0(void);
//void ISR_UART1(void);


//======================================================================================================================
  #ifdef __cplusplus
   }
  #endif
//======================================================================================================================
#endif //__STM32F10xXX_USART_H
//=============================================  EOF  ==================================================================