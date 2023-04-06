
#include "spi_tftlcd.h"
/****************************************************************************
 * ��    �ƣ�void LCD_GPIO_Init(void)
 * ��    �ܣ�STM32_ģ��SPI���õ���GPIO��ʼ��
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ������ʼ��ģ��SPI���õ�GPIO
 ****************************************************************************/
void LCD_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_Initure;
	//	__HAL_RCC_GPIOB_CLK_ENABLE();					//����GPIOBʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE(); // ����GPIOAʱ��

	GPIO_Initure.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_4;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;		// �������
													//	GPIO_Initure.Pull=GPIO_PULLUP;         			//����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // ����
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
}
/****************************************************************************
 * ��    �ƣ�void  SPIv_WriteData(uint8_t Data)
 * ��    �ܣ�STM32_ģ��SPIдһ���ֽ����ݵײ㺯��
 * ��ڲ�����Data
 * ���ڲ�������
 * ˵    ����STM32_ģ��SPI��дһ���ֽ����ݵײ㺯��
 ****************************************************************************/
void SPIv_WriteData(uint8_t Data)
{
}

/****************************************************************************
 * ��    �ƣ�uint8_t SPI_WriteByte(SPI_TypeDef* SPIx,uint8_t Byte)
 * ��    �ܣ�STM32_Ӳ��SPI��дһ���ֽ����ݵײ㺯��
 * ��ڲ�����SPIx,Byte
 * ���ڲ��������������յ�������
 * ˵    ����STM32_Ӳ��SPI��дһ���ֽ����ݵײ㺯��
 ****************************************************************************/
uint8_t SPI_WriteByte(SPI_TypeDef *SPIx, uint8_t Byte)
{
	return HAL_SPI_Transmit(&hspi1, &Byte, 1, 0XFF);
}

/****************************************************************************
 * ��    �ƣ�void SPI_SetSpeed(SPI_TypeDef* SPIx,uint8_t SpeedSet)
 * ��    �ܣ�����SPI���ٶ�
 * ��ڲ�����SPIx,SpeedSet
 * ���ڲ�������
 * ˵    ����SpeedSet:1,����;0,����;
 ****************************************************************************/
void SPI_SetSpeed(SPI_TypeDef *SPIx, uint8_t SpeedSet)
{
}

/****************************************************************************
 * ��    �ƣ�SPI2_Init(void)
 * ��    �ܣ�STM32_SPI2Ӳ�����ó�ʼ��
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����STM32_SPI2Ӳ�����ó�ʼ��
 ****************************************************************************/
void SPI1_Init(void)
{
}

/****************************************************************************
 * ��    �ƣ�Lcd_WriteIndex(uint8_t Index)
 * ��    �ܣ���Һ����дһ��8λָ��
 * ��ڲ�����Index   �Ĵ�����ַ
 * ���ڲ�������
 * ˵    ��������ǰ����ѡ�п��������ڲ�����
 ****************************************************************************/
void LCD_WR_REG(uint8_t Index)
{
	//   LCD_CS_CLR;
	LCD_RS_CLR;
//	 SW_delay_us(1);
#if USE_HARDWARE_SPI
	SPI_WriteByte(SPI1, Index);
#else
	SPIv_WriteData(Index);
#endif
	//   LCD_CS_SET;
}

/****************************************************************************
 * ��    �ƣ�Lcd_WriteData(uint8_t Data)
 * ��    �ܣ���Һ����дһ��8λ����
 * ��ڲ�����dat     �Ĵ�������
 * ���ڲ�������
 * ˵    �����������ָ����ַд�����ݣ��ڲ�����
 ****************************************************************************/
void LCD_WR_DATA(uint8_t Data)
{
	//   LCD_CS_CLR;
	LCD_RS_SET;
//	SW_delay_us(1);
#if USE_HARDWARE_SPI
	SPI_WriteByte(SPI1, Data);
#else
	SPIv_WriteData(Data);
#endif
	//   LCD_CS_SET;
}

/****************************************************************************
 * ��    �ƣ�void LCD_WriteReg(uint8_t Index,uint16_t Data)
 * ��    �ܣ�д�Ĵ�������
 * ��ڲ�����Index,Data
 * ���ڲ�������
 * ˵    ����������Ϊ��Ϻ�������Index��ַ�ļĴ���д��Dataֵ
 ****************************************************************************/
void LCD_WriteReg(uint8_t Index, uint16_t Data)
{
	LCD_WR_REG(Index);
	Lcd_WriteData_16Bit(Data);
}

/****************************************************************************
 * ��    �ƣ�void Lcd_WriteData_16Bit(uint16_t Data)
 * ��    �ܣ���Һ����дһ��16λ����
 * ��ڲ�����Data
 * ���ڲ�������
 * ˵    �����������ָ����ַд��һ��16λ����
 ****************************************************************************/
void Lcd_WriteData_16Bit(uint16_t Data)
{
	LCD_WR_DATA(Data >> 8);
	LCD_WR_DATA(Data & 0xff);
}

/****************************************************************************
 * ��    �ƣ�void Lcd_Reset(void)
 * ��    �ܣ�Һ��Ӳ��λ����
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����Һ����ʼ��ǰ��ִ��һ�θ�λ����
 ****************************************************************************/
void Lcd_Reset(void)
{
	//	 LCD_RST_SET;
	//   HAL_Delay(20);
	//	 LCD_RST_CLR;
	//   HAL_Delay(100);
	//   LCD_RST_SET;
	//   HAL_Delay(50);

	LCD_RST_SET;
	HAL_Delay(10);
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(100);
}
/****************************************************************************
 * ��    �ƣ�void Lcd_Init(void)
 * ��    �ܣ�Һ����ʼ������
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����Һ����ʼ��_ILI9225_176X220
 ****************************************************************************/
void Lcd_Init(void)
{
#if USE_HARDWARE_SPI // ʹ��Ӳ��SPI
	SPI1_Init();
#else
	LCD_GPIO_Init();   // ʹ��ģ��SPI
					   //  LCD_LED_SET;
#endif
	Lcd_Reset(); // Reset before LCD Init.
	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xc3);
	LCD_WR_DATA(0X30);

	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0X12);
	LCD_WR_DATA(0X81);

	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x78); // 7a

	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);

	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x20);

	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC0);  // Power control
	LCD_WR_DATA(0x1b); // VRH[5:0]  21

	LCD_WR_REG(0xC1);  // Power control
	LCD_WR_DATA(0x12); // SAP[2:0];BT[3:0]

	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x32); // 32
	LCD_WR_DATA(0x3C);

	LCD_WR_REG(0xC7);  // VCM control2
	LCD_WR_DATA(0xAF); // 9e

	LCD_WR_REG(0x36); // Memory Access Control
#if USE_HORIZONTAL
	LCD_WR_DATA(0x68); // ��������0x68
#else
	LCD_WR_DATA(0x08); // ��������
#endif // FPC D:0X08   68
	//();

	LCD_WR_REG(0x21);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);

	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1b);
	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x04);

	LCD_WR_REG(0xB6); // Display Function Control
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0xA2);

	LCD_WR_REG(0xF6);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x30);

	LCD_WR_REG(0xF2); // 3Gamma Function Disable
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x26); // Gamma curve selected
	LCD_WR_DATA(0x01);

	LCD_WR_REG(0xE0); // Set Gamma
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x1d);
	LCD_WR_DATA(0x1a);
	LCD_WR_DATA(0x0a);
	LCD_WR_DATA(0x0d);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x49);
	LCD_WR_DATA(0X66);
	LCD_WR_DATA(0x3b);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x04); // 04

	LCD_WR_REG(0XE1); // Set Gamma '
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x1d);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x0f);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x4c);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x0f);
	LCD_WR_DATA(0x2E);
	LCD_WR_DATA(0x2f);
	LCD_WR_DATA(0x05); // 0F

	LCD_WR_REG(0x11); // Exit Sleep
	HAL_Delay(120);
	LCD_WR_REG(0x29); // display on
}

/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(uint16_t Xpos, uint16_t Ypos)
{
	LCD_WR_REG(0x2A);
	Lcd_WriteData_16Bit(Xpos);
	LCD_WR_REG(0x2B);
	Lcd_WriteData_16Bit(Ypos);
	LCD_WR_REG(0x2c);
}
/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
// ������ʾ����
void Lcd_SetRegion(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
	LCD_WR_REG(0x2A);
	Lcd_WriteData_16Bit(xStar);
	Lcd_WriteData_16Bit(xEnd);
	LCD_WR_REG(0x2B);
	Lcd_WriteData_16Bit(yStar);
	Lcd_WriteData_16Bit(yEnd);
	LCD_WR_REG(0x2c);
}

/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�����xy�������ɫ����
����ֵ����
*************************************************/
void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Data)
{
	Lcd_SetXY(x, y);
	Lcd_WriteData_16Bit(Data);
}

/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void Lcd_Clear(uint16_t Color)
{
	unsigned int i;
	Lcd_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
	//	 LCD_CS_CLR;
	LCD_RS_SET;
	for (i = 0; i < X_MAX_PIXEL * Y_MAX_PIXEL; i++)
	{
		// Lcd_WriteData_16Bit(Color);
#if USE_HARDWARE_SPI
		SPI_WriteByte(SPI1, Color >> 8);
		SPI_WriteByte(SPI1, Color);
#else
		SPIv_WriteData(Color >> 8);
		SPIv_WriteData(Color);
#endif
	}
	//		LCD_CS_SET;
}
