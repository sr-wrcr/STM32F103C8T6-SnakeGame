#ifndef __SSD1306_H_
#define __SSD1306_H_

#include <include.h>

#define OLED_IIC_ADDR 0x7a

#define Brightness 0x6f
#define OLED_13 0
#define Max_Column 128
#define Max_Row 64

extern u8 OLED_GRAM[128][8];
void OLED_Refresh(void);
void OLED_WrDat(u8 IIC_Data);
void OLED_WrCmd(u8 IIC_Command);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Fill(u8 bmp_dat);
void OLED_Clear(void);

void OLED_DrawPoint(u8 x, u8 y);
void OLED_ClearPoint(u8 x, u8 y);
void OLED_DrawPoint_3x3(u8 x, u8 y);
void OLED_ClearPoint_3x3(u8 x, u8 y);
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_ClearLine(u8 x1, u8 y1, u8 x2, u8 y2);

void OLED_Init(void);
extern u32 OLED_pow(u8 m, u8 n);

void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2);
void OLED_ShowNum_int16(u8 x, u8 y, int16_t num, u8 len, u8 size2);
void OLED_ShowNum_Float(uint8_t x, uint8_t y, float Number, uint8_t Length,uint8_t Flength,uint8_t size);

void OLED_ShowChar(u8 x, u8 y, u8 chr, uint8_t mode, u8 SIZE);
void OLED_ShowStr(u16 x, u16 y, uint8_t *str, uint8_t size1, uint8_t mode);
void OLED_ShowStr_Center(u16 x, u16 y, uint8_t *str, uint8_t size1, uint8_t mode);

void OLED_DrawFont16(u16 x, u16 y, uint8_t *s, uint8_t mode);
void OLED_DrawFont16_Str(u16 x, u16 y, uint8_t *str, uint8_t mode);
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);

#endif /* __SSD1306_H_ */
