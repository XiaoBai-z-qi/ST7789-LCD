#include "lcd_driver.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"



static void LCD_Write_Byte(uint8_t Byte)
{
    LCD_CS_RESET();
    HAL_SPI_Transmit(&hspi1, &Byte, 1, 1000);
    LCD_CS_SET();
}


static void LCD_Write_Word(uint16_t Word)
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

