#ifndef MULTIMOD_H_
#define MULTIMOD_H_

#include "multimod_BMI160.h"
#include "multimod_i2c.h"
#include "multimod_joystick.h"
#include "multimod_OPT3001.h"
#include "multimod_PCA9956b.h"
#include "multimod_uart.h"
#include "multimod_ST7789.h"
#include "multimod_spi.h"
#include "multimod_buttons.h"
#include "multimod_audio.h"

static void multimod_init() {
    UART_Init();
    UART_BeagleBone_Init();
    UART_BT_Init();
    ST7789_Init();
}

#endif /* MULTIMOD_H_ */
