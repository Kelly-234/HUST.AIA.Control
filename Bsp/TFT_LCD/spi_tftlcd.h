

#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_
#include "init.h"

/////////////////////////////////////�û�������///////////////////////////////////
// ֧�ֺ��������ٶ����л�
#define USE_HORIZONTAL 1
// �����Ƿ�ʹ�ú��� 		0,��ʹ��.1,ʹ��.

//-----------------------------SPI ��������--------------------------------------//
#define USE_HARDWARE_SPI 1 // 1:Enable Hardware SPI;0:USE Soft SPI

//-------------------------��Ļ������������--------------------------------------//
#define LCD_X_SIZE 320
#define LCD_Y_SIZE 240

#if USE_HORIZONTAL // ��������˺���
#define X_MAX_PIXEL LCD_Y_SIZE
#define Y_MAX_PIXEL LCD_X_SIZE
#else
#define X_MAX_PIXEL LCD_X_SIZE
#define Y_MAX_PIXEL LCD_Y_SIZE
#endif
//////////////////////////////////////////////////////////////////////////////////
#define RED 0xf800
#define MAGENTA 0xF81F //  Ʒ��
#define MAROON 0x7800  //   ���ɫ
#define GREEN 0x07e0
#define DGREEN 0x03E0 //  ����ɫ
#define OLIVE 0x7BE0  //   �����
#define BLUE 0x001f
#define NAVY 0x000F //    ����ɫ
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xEF7D  // ��ɫ0 3165 00110 001011 00101
#define GRAY1 0x8410  // ��ɫ1      00000 000000 00000
#define GRAY2 0x4208  // ��ɫ2  1111111111011111
#define LGRAY 0xC618  //  �Ұ�ɫ
#define DGRAY 0x7BEF  //  ���ɫ
#define CYAN 0x07FF   //  ��ɫ
#define DCYAN 0x03EF  //   ����ɫ
#define PURPLE 0x780F //   ��ɫ

/*�ⲿ���������ģ��SPI*/
// #define LCD_RS         	GPIO_PIN_6	//PB14������TFT --DC
// #define LCD_SCL        	GPIO_PIN_5	//PC10������TFT --CLK
// #define LCD_SDA        	GPIO_PIN_7	//PC12������TFT - SDI
// #define LCD_RST         GPIO_PIN_4

////Һ�����ƿ���1�������궨��
// #define	LCD_RS_SET  	 GPIOA->BSRR=LCD_RS
// #define	LCD_SDA_SET  	 GPIOA->BSRR=LCD_SDA
// #define	LCD_SCL_SET    GPIOA->BSRR=LCD_SCL
// #define LCD_RST_SET    GPIOA->BSRR=LCD_RST

////Һ�����ƿ���0�������궨��
// #define	LCD_RS_CLR  	 GPIOA->BRR=LCD_RS
// #define	LCD_SDA_CLR  	 GPIOA->BRR=LCD_SDA
// #define	LCD_SCL_CLR  	 GPIOA->BRR=LCD_SCL
// #define LCD_RST_CLR    GPIOA->BRR=LCD_RST

/*�ⲿ������Ӳ��SPI����ͨ�ܽŲ���*/
#define LCD_RS_SET LCD_RS_GPIO_Port->BSRR = LCD_RS_Pin
#define LCD_RS_CLR LCD_RS_GPIO_Port->BRR = LCD_RS_Pin
#define LCD_RST_SET LCD_RST_GPIO_Port->BSRR = LCD_RST_Pin
#define LCD_RST_CLR LCD_RST_GPIO_Port->BRR = LCD_RST_Pin

void LCD_GPIO_Init(void);
void LCD_WR_REG(uint8_t Index);
void LCD_WR_DATA(uint8_t Data);
void Lcd_WriteReg(uint8_t Index, uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x, uint16_t y);
void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x, uint16_t y);
void Lcd_SetRegion(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);
void Lcd_WriteData_16Bit(uint16_t Data);

#endif
