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
 * @file    MKL25Z128_Keypad_example.c
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
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Teclado Matricial\n");

    uint8_t ren[4];

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	//Poner la columna 1 en bajo
    	GPIO_ClearPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_1_PIN);

    	//Leer los renglones
    	ren[0] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_1_PIN);
    	ren[1] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_2_PIN);
    	ren[2] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_3_PIN);
    	ren[3] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_4_PIN);

    	if(!ren[0])
    		printf("1");
    	if(!ren[1])
    		printf("4");
    	if(!ren[2])
    		printf("7");
    	if(!ren[3])
    		printf("*");

    	//Poner la columna 2 en bajo
		GPIO_SetPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_1_PIN);
		GPIO_ClearPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_2_PIN);

		//Leer los renglones
		ren[0] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_1_PIN);
		ren[1] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_2_PIN);
		ren[2] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_3_PIN);
		ren[3] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_4_PIN);

		if(!ren[0])
			printf("2");
		if(!ren[1])
			printf("5");
		if(!ren[2])
			printf("8");
		if(!ren[3])
			printf("0");
		//Poner la columna 3 en bajo
		GPIO_SetPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_2_PIN);
		GPIO_ClearPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_3_PIN);

		//Leer los renglones
		ren[0] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_1_PIN);
		ren[1] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_2_PIN);
		ren[2] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_3_PIN);
		ren[3] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_4_PIN);

		if(!ren[0])
			printf("3");
		if(!ren[1])
			printf("6");
		if(!ren[2])
			printf("9");
		if(!ren[3])
			printf("#");
		//Poner la columna 4 en bajo
		GPIO_SetPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_3_PIN);
		GPIO_ClearPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_4_PIN);

		//Leer los renglones
		ren[0] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_1_PIN);
		ren[1] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_2_PIN);
		ren[2] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_3_PIN);
		ren[3] = GPIO_ReadPinInput(GPIOE, BOARD_INITPINS_Renglon_4_PIN);

		if(!ren[0])
			printf("A");
		if(!ren[1])
			printf("B");
		if(!ren[2])
			printf("C");
		if(!ren[3])
			printf("D");
		GPIO_SetPinsOutput(GPIOB, 1u << BOARD_INITPINS_Columna_4_PIN);

    }
    return 0 ;
}
