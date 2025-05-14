#include "lcd.h"

uint8_t LCD_Buff[100];
volatile uint8_t LCD_DMA_Flag = 0;

void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint32_t num;
    LCD_Address_Set(x1, y1, x2, y2);

    num = ((x2 - x1 + 1) * (y2 - y1 + 1));
    for(uint8_t i = 0; i< 50; i++)
    {
        LCD_Buff[2*i] = color >> 8;
        LCD_Buff[2*i+1] = color;
    }

    while(num > 0)
    {
        uint32_t len = (num > 50) ? 50 : num;
        LCD_CS_RESET();
        HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)LCD_Buff, len*2);
        LCD_DMA_Wait();

        num -= len;
    }
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    LCD_CS_SET();
    LCD_DMA_Flag = 1;
}

void LCD_DMA_Wait(void)
{
    while(LCD_DMA_Flag == 0);
    LCD_DMA_Flag = 0;
}