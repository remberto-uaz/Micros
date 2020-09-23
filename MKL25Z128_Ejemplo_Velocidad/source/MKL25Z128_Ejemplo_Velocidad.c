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
 * @file    MKL25Z128_Ejemplo_Velocidad.c
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

#include "fsl_tpm.h"

/* TODO: insert other definitions and declarations here. */
#define MAX_COUNTER 20u
#define SECS 2u
#define TIEMPO (SECS*256)-1

void delay(uint32_t ticks);
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

    PRINTF("Inizializando temporizadores %f\n",3.2f);

    /*
     * TPM0
     * 		Conteo de Eventos
     * 		señal de reloj externo
     * 		prescalador de 1
     * 		conteo hasta 20 eventos
     *
     * TPM1
     * 		Tiempo de 10 segundos
     * 		reloj de 32.768KHz
     * 		prescalador de 128
     * 		conteo de 0 a 2559 equivalente a 10 segundos
     */

    tpm_config_t config0,config1;				//	Variables para configuracion de TPM0 y TPM1
    TPM_GetDefaultConfig(&config0);
    config1=config0;
    TPM_Init(TPM0, &config0);
    TPM_SetTimerPeriod(TPM0, MAX_COUNTER);
    TPM_StartTimer(TPM0, kTPM_ExternalClock);

    config1.prescale=kTPM_Prescale_Divide_128;
    TPM_Init(TPM1, &config1);
    TPM_SetTimerPeriod(TPM1, (uint16_t ) TIEMPO);
    TPM_StartTimer(TPM1, kTPM_SystemClock);
    uint8_t pulsos;
    float v;
    /* Enter an infinite loop. */
    while(1) {
       if(TPM_GetStatusFlags(TPM1) & 1u<<8u)
       {
    	   TPM_ClearStatusFlags(TPM1,1u<<8u);
    	   pulsos=TPM_GetCurrentTimerCount(TPM0);
    	   v=1.0*pulsos/(SECS);
    	   PRINTF("Velocidad %3.1f Eventos/segundo\n",v);
    	   TPM0->CNT=0;
       }
    }
    return 0 ;
}
void delay(uint32_t ticks)
{
	for(uint32_t i =0; i<ticks;i++)
	{
		__asm("NOP");
	}
}
