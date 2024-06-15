// /* @Note
//  * Compatibility HID Example:
//  * This program provides examples of the pass-through of USB-HID data and serial port
//  *  data based on compatibility HID device. And the data returned by Get_Report request is
//  *  the data sent by the last Set_Report request.Speed of UART1/2 is 115200bps.
//  *
//  * Interrupt Transfers:
//  *   UART2_RX   ---> Endpoint2
//  *   Endpoint1  ---> UART2_TX
//  *
//  *   Note that the first byte is the valid data length and the remaining bytes are
//  *   the transmission data for interrupt Transfers.
//  *
//  * Control Transfers:
//  *   Set_Report ---> UART1_TX
//  *   Get_Report <--- last Set_Report packet
//  *
//  *  */

#include "debug.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_prop.h"
#include "usbd_compatibility_hid.h"
// /* Global define */


// /* Global Variable */    

// /*********************************************************************
//  * @fn      Var_Init
//  *
//  * @brief   Software parameter initialization
//  *
//  * @return  none
//  */
void Var_Init(void)
{
    uint16_t i;
    RingBuffer_Comm.LoadPtr = 0;
    RingBuffer_Comm.StopFlag = 0;
    RingBuffer_Comm.DealPtr = 0;
    RingBuffer_Comm.RemainPack = 0;
    for(i=0; i<DEF_Ring_Buffer_Max_Blks; i++)
    {
        RingBuffer_Comm.PackLen[i] = 0;
    }
}

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    //USB
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init(); 
    USART_Printf_Init(115200);
	// printf("SystemClk:%d\r\n",SystemCoreClock);
	// printf("USBHD Compatibility HID Example\r\n");
    /* Variables init */
	Var_Init();

    /* UART2 init */
    UART2_Init();
    UART2_DMA_Init();

    /* Timer init */
    TIM2_Init();

    /* USBD init */
    Set_USBConfig();
    USB_Init();
    USB_Interrupts_Config();
    
    while(1)
    {
        if( bDeviceState == CONFIGURED )
        {
            UART2_Rx_Service();
            UART2_Tx_Service();
        }
    }

    //LED
    u8 i = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
#if 0
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    printf("GPIO Toggle TEST\r\n");
#endif
    GPIO_Toggle_INIT();
    // GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
    while(1)
    {
        Delay_Ms(500);
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
        // GPIO_WriteBit(GPIOB, GPIO_Pin_8, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }

}

