/**
 * @file main.c
 * @brief Entry point of the code, Starts in Function main()
 */

#include "ch32x035.h"
#include "debug.h"
#include "ch32x035_usbpd.h"

// 
PD_CONTROL PD_Ctrl; /* PD Control Related Structures */

// 
void PD_Init();

int main(void)
{
    USART_Printf_Init(921600);
    printf("USART_Printf Enabled\r\n");

    PD_Init();

    while (1)
    {
        // printf("HelloWorld\n");
    }
}

/**
 * @brief PD_Init_GPIO
 * 
 * Sets PC14/PC15 to Floating input, 
 * Sets PC14/PC15 high threshold to ~2.2V
 * Dissables LDO because VDD is < 4V
 */
void PD_Init_GPIO(void)
{
    // Set GPIO_Pin_14/15 to GPIO_Mode_IN_FLOATING
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);               /* Open PD I/O clock, AFIO clock and PD clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBPD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Alternate function IO
    // Set PD pins high threshold to ~2.2V
    AFIO->CTLR |= USBPD_IN_HVT;
    // Set if VDD < 4V, dissables LDO for PD pullups
    AFIO->CTLR |= USBPD_PHY_V33;
}

/**
 * @brief PD_Init(), ...
 * 
 * Calls PD_Init_GPIO
//  * Enables DMA for USB_PD
//  * Enable interrupt for:
//  *  - BUFFER or DMA error interrupt flag
//  *  - Receive bit or 5bit interrupt flag
//  *  - Receive byte or SOP interrupt flag
//  *  - Receive completion interrupt flag
//  *  - Receive reset interrupt flag
//  *  - Transfer completion interrupt flag
 * 
 * @return none
 */
void PD_Init()
{
    PD_Init_GPIO();

    // // USB_PD enable DirectMemoryAccess(MDA)
    // USBPD->CONFIG = PD_DMA_EN;

    // // Enable interrupt for:
    // // - BUFFER or DMA error interrupt flag
    // // - Receive bit or 5bit interrupt flag
    // // - Receive byte or SOP interrupt flag
    // // - Receive completion interrupt flag
    // // - Receive reset interrupt flag
    // // - Transfer completion interrupt flag
    // USBPD->STATUS = BUF_ERR | IF_RX_BIT | IF_RX_BYTE | IF_RX_ACT | IF_RX_RESET | IF_TX_END;


    // // 
    // // /* Initialize all variables */
    // // memset( &PD_Ctrl.PD_State, 0x00, sizeof( PD_CONTROL ) );
    // // Adapter_SrcCap[ 0 ] = 1;
    // // memcpy( &Adapter_SrcCap[ 1 ], SrcCap_5V3A_Tab, 4 );
    // // PD_PHY_Reset( );
    // // PD_Rx_Mode( );
}