// G8RTOS_Threads.c
// Date Created: 2023-07-25
// Date Updated: 2023-07-27
// Defines for thread functions.

/************************************Includes***************************************/

#include "./threads.h"

#include "./MultimodDrivers/multimod.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printByteAsNumber(uint32_t ui32Base, uint8_t byte)
{
    uint8_t hundreds = byte / 100;
    uint8_t tens = (byte / 10) % 10;
    uint8_t ones = byte % 10;

    // Convert to ASCII and print
    UARTCharPut(ui32Base, '0' + hundreds);
    UARTCharPut(ui32Base, '0' + tens);
    UARTCharPut(ui32Base, '0' + ones);
}

/************************************Includes***************************************/

/*************************************Defines***************************************/
/*************************************Defines***************************************/

/*********************************Global Variables**********************************/
/*********************************Global Variables**********************************/

/*************************************Threads***************************************/
void Idle_Thread(void) {
    while(1);
}

void Read_Beagle(void)
{
    uint8_t read_byte = 0;
    while(1)
    {
        G8RTOS_WaitSemaphore(&sem_UART);

        G8RTOS_WaitSemaphore(&dimensions_reg);
        for (uint8_t i=0; i<4; i++)
        {
            read_byte = read_UART(UART4_BASE);
            dimensions[i] = read_byte;
            //printByteAsNumber(UART0_BASE, read_byte);
            //UARTCharPut(UART0_BASE, ' ');
        }
        G8RTOS_SignalSemaphore(&dimensions_reg);

        G8RTOS_SignalSemaphore(&sem_UART);
        sleep(10);
    }
}

void check_bt(void)
{
    uint8_t read_byte = 0;
    while(1)
    {
        G8RTOS_WaitSemaphore(&sem_UART);
        read_byte = read_UART(UART3_BASE);
        //write_UART(UART0_BASE, read_byte);
        if (read_byte == 97)
        {
            UARTCharPut(UART0_BASE, 'x');
            UARTCharPut(UART0_BASE, ':');
            printByteAsNumber(UART0_BASE, dimensions[0]);
            UARTCharPut(UART0_BASE, ' ');
            UARTCharPut(UART0_BASE, 'y');
            UARTCharPut(UART0_BASE, ':');
            printByteAsNumber(UART0_BASE, dimensions[1]);
            UARTCharPut(UART0_BASE, ' ');
            UARTCharPut(UART0_BASE, 'w');
            UARTCharPut(UART0_BASE, ':');
            printByteAsNumber(UART0_BASE, dimensions[2]);
            UARTCharPut(UART0_BASE, ' ');
            UARTCharPut(UART0_BASE, 'h');
            UARTCharPut(UART0_BASE, ':');
            printByteAsNumber(UART0_BASE, dimensions[3]);

        }
        G8RTOS_SignalSemaphore(&sem_UART);
    }
    sleep(50);
}

/*
void ReadUART_coor(void)
{
    while(1)
    {
        // read coordinates from UART

        // and write the coordinates to FIFO

        // dont forget to use semaphores
        sleep(50);
    }
}*/

void Draw_Display(void)
{
    static uint8_t x, y, w, h = 0;
    uint8_t new_x, new_y, new_w, new_h = 0;
    while(1)
    {

        // read coordinates from FIFO
        // I did not want to use FIFO because maybe a size of 16 may cause a delay
        // so just used an array to hold just 1 dimension at a time instead
        G8RTOS_WaitSemaphore(&dimensions_reg);
        new_x = dimensions[0];
        new_y = dimensions[1];
        new_w = dimensions[2];
        new_h = dimensions[3];
        G8RTOS_SignalSemaphore(&dimensions_reg);

        ST7789_DrawRectangle(x, y, w, h, ST7789_BLACK);
        ST7789_DrawRectangle(new_x, new_y, new_w, new_h, ST7789_BLUE);

        // change code to draw square outline, not filled.



        x = new_x;
        y = new_y;
        w = new_w;
        h = new_h;

        //sleep(20);
    }
}
/*************************************Threads***************************************/

/********************************Periodic Threads***********************************/
/********************************Periodic Threads***********************************/


/*******************************Aperiodic Threads***********************************/
/*******************************Aperiodic Threads***********************************/
