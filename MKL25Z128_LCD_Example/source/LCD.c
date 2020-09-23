/*
 * LCD.c
 *
 *  Created on: Jun 3, 2020
 *      Author: remberto
 */
#include "LCD.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

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
