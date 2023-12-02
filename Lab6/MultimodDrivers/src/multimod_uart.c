// multimod_uart.c
// Date Created: 2023-07-25
// Date Updated: 2023-07-27
// Defines for UART functions

/************************************Includes***************************************/

#include "../multimod_uart.h"


#include <stdbool.h>

#include <inc/tm4c123gh6pm.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>

#include <driverlib/uartstdio.h>
#include <driverlib/gpio.h>
#include <driverlib/uart.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>

/************************************Includes***************************************/

/********************************Public Functions***********************************/

// UART_Init
// Initializes UART serial communication with PC
// Return: void
void UART_Init() {
    // Enable port A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Enable UART0 module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure UART0 pins on port A
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTFIFODisable(UART0_BASE);

    // Set UART clock source
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    // Configure UART baud rate

    UARTStdioConfig(0, 115200, SysCtlClockGet());

}

// UART_BeagleBone_Init
// Initializes UART serial communication with Beaglebone
// Return: void
void UART_BeagleBone_Init(void) {
    // finish this function
    // Enable port B ( UART module 1 )
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // Enable UART1 module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);

    // Configure UART1 pins on Port B
    GPIOPinConfigure(GPIO_PC4_U4RX);
    GPIOPinConfigure(GPIO_PC5_U4TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    UARTFIFODisable(UART4_BASE);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART4))
    {
    }

    UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), 115200,
                    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    // set UART clock source
    //UARTClockSourceSet(UART4_BASE, UART_CLOCK_SYSTEM);

    //UARTStdioConfig(0, 115200, SysCtlClockGet());
}

void UART_BT_Init(void)
{
    // Enable port B ( UART module 1 )
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        // Enable UART1 module
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

        // Configure UART1 pins on Port B
        GPIOPinConfigure(GPIO_PC6_U3RX);
        GPIOPinConfigure(GPIO_PC7_U3TX);
        GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

        UARTFIFODisable(UART3_BASE);

        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART3))
        {
        }

        UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 1000000,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

}


void write_UART(uint32_t ui32Base, uint8_t byte)
{
    //wait until UART is ready
    while(!UARTSpaceAvail(ui32Base));

    // send byte
    UARTCharPut(ui32Base, byte);
}

uint8_t read_UART(uint32_t ui32Base)
{
    // wait while UART is ready
    while(!UARTCharsAvail(ui32Base));
    // return received byte
    return UARTCharGet(ui32Base);
}


/********************************Public Functions***********************************/

