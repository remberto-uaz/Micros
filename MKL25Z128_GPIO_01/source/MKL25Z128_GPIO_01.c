/*
 * Copyright 2016-2020 NXP
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
 * @file    MKL25Z128_GPIO_01.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

#define LED_ROJO	18u	/* Pin number for LED Rojo*/
#define MASK(x) (1UL << (x))

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    /************************************************************************
     *
     * 	Código Agregado
     *
     * 	Se va utilizar el led rojo que está conectado en la FRDM el pin PTB_18
  	***********************************************************************/
    /*
     *				 -			1. Clock Gating			-
     * 	Habilitar el reloj (clock gating) en el Puerto B
     * 	Modificar el System Clock Gating Control register 5 (SIM_SCG5) en el bit 10 correspondiente l Puerto B
     */

    	  	  SIM->SCGC5 |= MASK(10u);//1u << 10u;

    	/*
    	 * 				-			2. Pin MUX			-
    	 * 	Establecer el IOMUX del pin PTB18 con el GPIO
    	 * 	Es la ALT1 001
    	 * 	se estblece en el PORTB_PCR[18] en los bits 10 9 y 8
    	 * 	es decir se establece un 1 recorrido 8 bits
    	 */

    	  	  PORTB->PCR[LED_ROJO] |= MASK(8u);//1u << 8u;

    /*
     * 				-			3. Pin Direction			-
     * 	Establecer como salida el pin 18 definido como LED_ROJO 18u
     * 	A través del GPIOB_PDDR POrt Data Direction Register
     */
    	  	  GPIOB->PDDR |= MASK(LED_ROJO);//1u << 18u;

    PRINTF("Encender el led Rojo\n");

    		GPIOB->PCOR |= MASK(LED_ROJO);//;

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        GPIOB->PTOR |= MASK(LED_ROJO);
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
