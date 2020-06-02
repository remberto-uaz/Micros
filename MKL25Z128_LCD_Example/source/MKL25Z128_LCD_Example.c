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
 * @file    MKL25Z128_LCD_Example.c
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
 * void LCD_Data(uint8_t *HIGH, uint8_t *LOW, uint8_t c)
 *
 * @param
 *
 * HIGH pointer to 8 bit register with high bits of c on the lower bits
 * LOW  pointer to 8 bit register with low bits of on the lower bits
 */
void LCD_Data(uint8_t *high, uint8_t *low, uint8_t c);
void Write_Data(uint8_t data);
void LCD_CMD(uint8_t cmd);
void LCD_Write(uint8_t data);
void LCD_Clear();
void LCD_Return();
void LCD_Mode(uint8_t ID, uint8_t S);
void LCD_Set(uint8_t D, uint8_t C, uint8_t B);
void LCD_Cursor(uint8_t SC, uint8_t RL);
void LCD_Activate(uint8_t DL, uint8_t N, uint8_t F);
void LCD_CGRAM(uint8_t Address);
void LCD_DDRAM(uint8_t Address);
void Delay (uint32_t delay);

#define DELAY 100

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

    PRINTF("Hello World\n");
    LCD_Set(1u,1u,1u);
    LCD_Clear();
    LCD_Write('M');
    LCD_Write('i');
    LCD_Write('c');
    LCD_Write('r');
    LCD_Write('o');
    LCD_Write('s');
//    LCD_Write('o');
//    LCD_Write('n');
//    LCD_Write('t');
//    LCD_Write('r');
//    LCD_Write('o');
//    LCD_Write('l');
//    LCD_Write('a');
//    LCD_Write('d');
//    LCD_Write('o');
//    LCD_Write('r');

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

void LCD_Data(uint8_t *high, uint8_t *low, uint8_t c)
{
  *high=(c & 0xF0) >> 4;
  *low= c & 0x0F;
}
void Write_Data(uint8_t data)
{

	for (uint8_t i=0;i<4;i++) //low
	{
		if(data & (1u<<i))
		{
			GPIO_SetPinsOutput(GPIOB, 1u<<i);
		}
		else
		{
			GPIO_ClearPinsOutput(GPIOB, 1u<<i);
		}
	}


	for (uint8_t i=0;i<4;i++) //High
	{
		if(data & (1u<<(i+4)))
		{
			GPIO_SetPinsOutput(GPIOE, 1u<<(i+20));
		}
		else
		{
			GPIO_ClearPinsOutput(GPIOE, 1u<<(i+20));
		}
	}
}
void LCD_CMD(uint8_t cmd)
{
	//Pone LCD_RS en bajo
	GPIO_ClearPinsOutput(GPIOC, 1u<<BOARD_INITPINS_LCD_RS_PIN);
	//Pone LCD_RW en bajo
	GPIO_ClearPinsOutput(GPIOC, 1u<<BOARD_INITPINS_LCD_RW_PIN);
	//Pone LCD_E en alto
	GPIO_SetPinsOutput(GPIOE, 1u<<BOARD_INITPINS_LCD_E_PIN);
	Write_Data(cmd);
	//Pone LCD_E en bajo
	GPIO_ClearPinsOutput(GPIOE, 1u<<BOARD_INITPINS_LCD_E_PIN);
	Delay(DELAY);

}
void LCD_Write(uint8_t data)
{
	//Pone LCD_RS en alto
	GPIO_SetPinsOutput(GPIOC, 1u<<BOARD_INITPINS_LCD_RS_PIN);
	//Pone LCD_RW en bajo
	GPIO_ClearPinsOutput(GPIOC, 1u<<BOARD_INITPINS_LCD_RW_PIN);
	//Pone LCD_E en alto
	GPIO_SetPinsOutput(GPIOE, 1u<<BOARD_INITPINS_LCD_E_PIN);
	Write_Data(data);
	//Pone LCD_E en bajo
	GPIO_ClearPinsOutput(GPIOE, 1u<<BOARD_INITPINS_LCD_E_PIN);
	Delay(DELAY);
}
void LCD_Clear()
{
	uint8_t cmd=0x01u;
	LCD_CMD(cmd);
}
void LCD_Return()
{
	uint8_t cmd=0x02u;
	LCD_CMD(cmd);
}
void LCD_Mode(uint8_t ID, uint8_t S)
{
	uint8_t cmd=4u;
	if(ID)
		cmd |=2u;
	if(S)
		cmd |=1u;
	LCD_CMD(cmd);
}
void LCD_Set(uint8_t D, uint8_t C, uint8_t B)
{
	uint8_t cmd=8u;
	if(D)
		cmd |= 4u;
	if(C)
		cmd |= 2u;
	if(B)
		cmd |= 1u;
	LCD_CMD(cmd);
}
void LCD_Cursor(uint8_t SC, uint8_t RL)
{
	uint8_t cmd=16u;
	if(SC)
		cmd |=8u;
	if(RL)
		cmd |=4u;
	LCD_CMD(cmd);
}
void LCD_Activate(uint8_t DL, uint8_t N, uint8_t F)
{
	uint8_t cmd=32u;
	if(DL)
		cmd |=16u;
	if(N)
		cmd |=8u;
	if(F)
		cmd |=4u;
	LCD_CMD(cmd);
}
void LCD_CGRAM(uint8_t Address)
{
	uint8_t cmd = 0x40u;
	cmd |= Address & 0x3Fu;
	LCD_CMD(cmd);
}
void LCD_DDRAM(uint8_t Address)
{
	uint8_t cmd = 0x80u;
	cmd |= Address & 0x7Fu;
	LCD_CMD(cmd);
}
void Delay(uint32_t delay)
{
	for(uint32_t i=0;i<delay;i++)
		__asm("NOP");
}
