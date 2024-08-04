

#include "ch32x035.h"
#include "debug.h"
#include "ch32x035_usbpd.h"

int main(void)
{
    USART_Printf_Init(9600);
    while (1)
    {
        printf("HelloWorld\n");
    }
}