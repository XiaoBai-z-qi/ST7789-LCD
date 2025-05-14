#include "lcd_driver.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"



void LCD_Write_Byte(uint8_t Byte)
{
    LCD_CS_RESET();
    HAL_SPI_Transmit(&hspi1, &Byte, 1, 1000);
    LCD_CS_SET();
}


void LCD_Write_Word(uint16_t Word)
{
    LCD_Write_Byte(Word >> 8);
    LCD_Write_Byte(Word);
}

void LCD_Write_Command(uint8_t Command)
{
    LCD_DC_RESET();
    LCD_Write_Byte(Command);
    LCD_DC_SET();
}

/**
 * @brief 设置LCD显示区域的地址
 *
 * 该函数用于设置LCD显示区域的起始和结束地址。
 *
 * @param x1 显示区域的起始列地址
 * @param y1 显示区域的起始行地址
 * @param x2 显示区域的结束列地址
 * @param y2 显示区域的结束行地址
 */
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if(USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1)
    {
        LCD_Write_Command(0x2a);//列地址设置
        LCD_Write_Word(x1);
        LCD_Write_Word(x2);
        LCD_Write_Command(0x2b);//行地址设置
        LCD_Write_Word(y1 + 20);
        LCD_Write_Word(y2 + 20);
        LCD_Write_Command(0x2c);//储存器写命令
    }else if(USE_HORIZONTAL == 2 || USE_HORIZONTAL == 3)
    {
        LCD_Write_Command(0x2a);//列地址设
        LCD_Write_Word(x1 + 20);
        LCD_Write_Word(x2 + 20);
        LCD_Write_Command(0x2b);//行地址设置
        LCD_Write_Word(y1);
        LCD_Write_Word(y2);
        LCD_Write_Command(0x2c);//储存器写命令
    }
    
}

void LCD_Init(void)
{
    LCD_RES_RESET();
    HAL_Delay(100);
    LCD_RES_SET();
    HAL_Delay(100);
    LCD_BLK_SET();
    HAL_Delay(100);

    //************* Start Initial Sequence **********//
	LCD_Write_Command(0x11); //Sleep out 
	HAL_Delay(120);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_Write_Command(0x36);
	if(USE_HORIZONTAL==0)LCD_Write_Byte(0x00);
	else if(USE_HORIZONTAL==1)LCD_Write_Byte(0xC0);
	else if(USE_HORIZONTAL==2)LCD_Write_Byte(0x70);
	else LCD_Write_Byte(0xA0);

	LCD_Write_Command(0x3A);			
	LCD_Write_Byte(0x05);

	LCD_Write_Command(0xB2);			
	LCD_Write_Byte(0x0C);
	LCD_Write_Byte(0x0C); 
	LCD_Write_Byte(0x00); 
	LCD_Write_Byte(0x33); 
	LCD_Write_Byte(0x33); 			

	LCD_Write_Command(0xB7);			
	LCD_Write_Byte(0x35);

	LCD_Write_Command(0xBB);			
	LCD_Write_Byte(0x32); //Vcom=1.35V
					
	LCD_Write_Command(0xC2);
	LCD_Write_Byte(0x01);

	LCD_Write_Command(0xC3);			
	LCD_Write_Byte(0x15); //GVDD=4.8V  颜色深度
				
	LCD_Write_Command(0xC4);			
	LCD_Write_Byte(0x20); //VDV, 0x20:0v

	LCD_Write_Command(0xC6);			
	LCD_Write_Byte(0x0F); //0x0F:60Hz        	

	LCD_Write_Command(0xD0);			
	LCD_Write_Byte(0xA4);
	LCD_Write_Byte(0xA1); 

	LCD_Write_Command(0xE0);
	LCD_Write_Byte(0xD0);   
	LCD_Write_Byte(0x08);   
	LCD_Write_Byte(0x0E);   
	LCD_Write_Byte(0x09);   
	LCD_Write_Byte(0x09);   
	LCD_Write_Byte(0x05);   
	LCD_Write_Byte(0x31);   
	LCD_Write_Byte(0x33);   
	LCD_Write_Byte(0x48);   
	LCD_Write_Byte(0x17);   
	LCD_Write_Byte(0x14);   
	LCD_Write_Byte(0x15);   
	LCD_Write_Byte(0x31);   
	LCD_Write_Byte(0x34);   

	LCD_Write_Command(0xE1);     
	LCD_Write_Byte(0xD0);   
	LCD_Write_Byte(0x08);   
	LCD_Write_Byte(0x0E);   
	LCD_Write_Byte(0x09);   
	LCD_Write_Byte(0x09);   
	LCD_Write_Byte(0x15);   
	LCD_Write_Byte(0x31);   
	LCD_Write_Byte(0x33);   
	LCD_Write_Byte(0x48);   
	LCD_Write_Byte(0x17);   
	LCD_Write_Byte(0x14);   
	LCD_Write_Byte(0x15);   
	LCD_Write_Byte(0x31);   
	LCD_Write_Byte(0x34);
	LCD_Write_Command(0x21); 

	LCD_Write_Command(0x29);

}

