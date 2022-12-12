/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    LPC5528_Led_Blink.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC5528.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "fsl_gpio.h"

/* TODO: insert other definitions and declarations here. */
void delay_ms(uint32_t value)
{
    uint32_t d = CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000 / 10 * value;
    uint32_t i;
    for (i = 0U; i < d; ++i)
    {
        __asm("NOP");
    }
}

/*
 * @brief   Application entry point.
 */
int main(void) {

	gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 1, };

    /* Init board hardware. */
    BOARD_InitBootPins();

    //BOARD_InitBootClocks();
    BOARD_BootClockFRO12M();

    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    GPIO_PortInit ( GPIO, BOARD_INITPINS_LED_PORT );
    GPIO_PinInit  ( GPIO, BOARD_INITPINS_LED_PORT, BOARD_INITPINS_LED_PIN, &led_config );
    GPIO_PinWrite ( GPIO, BOARD_INITPINS_LED_PORT, BOARD_INITPINS_LED_PIN, 0U );

    /* Force the counter to be placed into memory. */
    //volatile static int i = 0 ;

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	GPIO_PinWrite ( GPIO, BOARD_INITPINS_LED_PORT, BOARD_INITPINS_LED_PIN, 1U );

    	delay_ms(500);

    	GPIO_PinWrite ( GPIO, BOARD_INITPINS_LED_PORT, BOARD_INITPINS_LED_PIN, 0U );

    	delay_ms(500);
    }
    return 0 ;
}
