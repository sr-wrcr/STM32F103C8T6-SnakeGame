#include "SSD1306.h"
#include "string.h"
#include "stdlib.h"

u8 OLED_GRAM[128][8]; // 数组映射

/*!
 *  @brief  OLED 更新显存
 *  @since  v1.0
 *  @note   OLED_Refresh(void) 【重要】更新显存到OLED，显存数组中的内容实现函数
 *  Sample usage: OLED_Refresh();
 */
 
void OLED_Refresh(void)
{
  u8 i, n;
  for (i = 0; i < 8; i++)
  {
    OLED_WrCmd(0xb0 + i); // 设置行起始地址,页数
    OLED_WrCmd(0x00);     // 设置低列起始地址
    OLED_WrCmd(0x10);     // 设置高列起始地址
    for (n = 0; n < 96; n++)//由于贪吃蛇的需要 只刷新地图中的 也就是零到96 //正常的范围这里是128 
      OLED_WrDat(OLED_GRAM[n][i]);
  }
}

/*!
 *  @brief  OLED 写数据
 *  @param  u8   I2C_Data  要写入的数据
 *  @since  v1.0
 *  @note   OLED_WrDat(u8 I2C_Data)
 *  Sample usage: OLED_WrDat(0x10);
 */
void OLED_WrDat(u8 I2C_Data)
{
  IicTransmit(I2C1, OLED_IIC_ADDR, 0x40, I2C_Data);
}

/*!
 *  @brief  OLED 写命令
 *  @param  u8   I2C_Command  要写入的命令
 *  @since  v1.0
 *  @note   OLED_WrCmd(u8 I2C_Command)
 *  Sample usage: OLED_WrCmd(0x10);
 */
void OLED_WrCmd(u8 I2C_Command)
{
  IicTransmit(I2C1, OLED_IIC_ADDR, 0x00, I2C_Command);
}

/*!
 *  @brief  OLED 设置坐标
 *  @param  u8   x  横坐标
 *  @param  u8   y  纵坐标
 *  @since  v1.0
 *  @note   OLED_Set_Pos(u8 x, u8 y)
 *  Sample usage: OLED_Set_Pos(0,0);
 */
void OLED_Set_Pos(u8 x, u8 y)
{
#if OLED_13
  x += 2; // 如果使用1.3寸的OLED，X坐标要+2才正确
#endif
  OLED_WrCmd(0xb0 + y);
  OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
  // OLED_WrCmd((x&0x0f));
  OLED_WrCmd((x & 0x0f) | 0x00);
}

/*!
 *  @brief  OLED 全屏
 *  @param  u8   bmp_dat  图片数据
 *  @since  v1.0
 *  @note   OLED_Fill(u8 bmp_dat)  填充图片
 *  Sample usage: OLED_Fill(bmp);
 */
void OLED_Fill(u8 bmp_dat)
{
  u8 y, x;
  for (y = 0; y < 8; y++)
  {
    OLED_WrCmd(0xb0 + y);
    OLED_WrCmd(0x00);
    // OLED_WrCmd(0x02);
    OLED_WrCmd(0x10);
    for (x = 0; x < Max_Column; x++)
      OLED_WrDat(bmp_dat);
  }
}

/**
 * @brief  OLED 清屏
 * @since  V1.0
 * @note   屏幕指令清屏
 * @par example:
           OLED_Clear();//清屏
 */
void OLED_Clear(void)
{
  u8 i, n;
  for (i = 0; i < 8; i++)
  {
    OLED_WrCmd(0xb0 + i); // 设置页地址（0~7）
#if OLED_13
    OLED_WrCmd(0x02); // 设置显示位置—列低地址,要是用1.3寸，这里是0x02,0.96寸是0x00;
#else
    OLED_WrCmd(0x00);
#endif
    OLED_WrCmd(0x10); // 设置显示位置—列高地址
    for (n = 0; n < 128; n++)
      OLED_WrDat(0);
  } // 更新显示
}

/*!
 *  @brief  OLED 画点
 *  @param  u8  x   横坐标
 *  @param  u8  y   纵坐标
 *  @since  v1.0
 *  @note   OLED_DrawPoint(u8 x,u8 y)  x:0~127 y:0~63
 *  Sample usage: OLED_DrawPoint(0,0);
 */
void OLED_DrawPoint(u8 x, u8 y)
{
  u8 i, m, n;
  i = y / 8;
  m = y % 8;
  n = 1 << m;
  OLED_GRAM[x][i] |= n; // 由显存更新函数实现显示
}

/*!
 *  @brief  OLED 画3*3点
 *  @param  u8  x   横坐标
 *  @param  u8  y   纵坐标
 *  @since  v1.0
 *  @note   OLED_DrawPoint(u8 x,u8 y)  x:0~127 y:0~63
 *           Sample usage: OLED_DrawPoint(0,0);
 */
void OLED_DrawPoint_3x3(u8 x, u8 y)
{
  OLED_DrawPoint(x, y);
  OLED_DrawPoint(x+1, y+1);
  OLED_DrawPoint(x+1, y-1);
  OLED_DrawPoint(x-1, y+1);
  OLED_DrawPoint(x-1, y-1);
  OLED_DrawPoint(x+1, y);
  OLED_DrawPoint(x-1, y);
  OLED_DrawPoint(x, y+1);
  OLED_DrawPoint(x, y-1);
}

/*!
 *  @brief  OLED 清除点
 *  @param  u8  x   横坐标
 *  @param  u8  y   纵坐标
 *  @since  v1.0
 *  @note   OLED_ClearPoint(u8 x,u8 y)  x:0~127 y:0~63
 *  Sample usage: OLED_ClearPoint(0,0);
 */
void OLED_ClearPoint(u8 x, u8 y)
{
  u8 i, m, n;
  i = y / 8;
  m = y % 8;
  n = 1 << m;
  OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
  OLED_GRAM[x][i] |= n;
  OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
}

/*!
 *  @brief  OLED 清除点（3x3）
 *  @param  u8  x   横坐标
 *  @param  u8  y   纵坐标
 *  @since  v1.0
 *  @note   OLED_ClearPoint_3x3(u8 x, u8 y)  x:0~125 y:0~61
 *  Sample usage: OLED_ClearPoint_3x3(0,0);
 */
void OLED_ClearPoint_3x3(u8 x, u8 y)
{
	OLED_ClearPoint(x, y);
  OLED_ClearPoint(x+1, y+1);
  OLED_ClearPoint(x+1, y-1);
  OLED_ClearPoint(x-1, y+1);
  OLED_ClearPoint(x-1, y-1);
  OLED_ClearPoint(x+1, y);
  OLED_ClearPoint(x-1, y);
  OLED_ClearPoint(x, y+1);
  OLED_ClearPoint(x, y-1);
}

/*!
 *  @brief  OLED 画线
 *  @param  u8  x1   起点横坐标
 *  @param  u8  y1   起点纵坐标
 *  @param  u8  x2   终点横坐标
 *  @param  u8  y2   终点纵坐标
 *  @since  v1.0
 *  @note   OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
 *  Sample usage: OLED_DrawLine(0,0,1,1);
 */
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2)
{
  u8 i, k, k1, k2;
  if (x1 == x2) // 画竖线
  {
    for (i = 0; i < (y2 - y1); i++)
    {
      OLED_DrawPoint(x1, y1 + i);
    }
  }
  else if (y1 == y2) // 画横线
  {
    for (i = 0; i < (x2 - x1); i++)
    {
      OLED_DrawPoint(x1 + i, y1);
    }
  }
  else // 画斜线
  {
    k1 = y2 - y1;
    k2 = x2 - x1;
    k = k1 * 10 / k2; // 斜率
    for (i = 0; i < (x2 - x1); i++)
    {
      OLED_DrawPoint(x1 + i, y1 + i * k / 10);
    }
  }
}

/*!
 *  @brief  OLED 画线
 *  @param  u8  x1   起点横坐标
 *  @param  u8  y1   起点纵坐标
 *  @param  u8  x2   终点横坐标
 *  @param  u8  y2   终点纵坐标
 *  @since  v1.0
 *  @note   OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
 *  Sample usage: OLED_DrawLine(0,0,1,1);
 */
void OLED_ClearLine(u8 x1, u8 y1, u8 x2, u8 y2)
{
  u8 i, k, k1, k2;
  if (x1 == x2) // 画竖线
  {
    for (i = 0; i < (y2 - y1); i++)
    {
      OLED_ClearPoint(x1, y1 + i);
    }
  }
  else if (y1 == y2) // 画横线
  {
    for (i = 0; i < (x2 - x1); i++)
    {
      OLED_ClearPoint(x1 + i, y1);
    }
  }
  else // 画斜线
  {
    k1 = y2 - y1;
    k2 = x2 - x1;
    k = k1 * 10 / k2; // 斜率
    for (i = 0; i < (x2 - x1); i++)
    {
      OLED_ClearPoint(x1 + i, y1 + i * k / 10);
    }
  }
}


/*!
 *  @brief  m^n函数
 *  @param  u8  m   底
 *  @param  u8  n   幂
 *  @since  v1.0
 *  @note   OLED_pow(u8 m,u8 n)
 *  Sample usage: OLED_pow(2,3);
 */
u32 OLED_pow(u8 m, u8 n)
{
  u32 result = 1;
  while (n--)
    result *= m;
  return result;
}

/*!
 *  @brief  OLED 显示2个数字
 *  @param  u8  x      起点横坐标
 *  @param  u8  y      起点纵坐标
 *  @param  u32  num    显示的数字
 *  @param  u8  len    数字的位数
 *  @param  u8  size   字体大小
 *  @since  v1.0
 *  @note   OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
 *  Sample usage: OLED_ShowNum(80,3,score,2,16);
 */
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2)
{
  u8 t, temp;
  u8 enshow = 0;
  for (t = 0; t < len; t++)
  {
    temp = (num / OLED_pow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1))
    {
      if (temp == 0)
      {
        OLED_ShowChar(x + (size2 / 2) * t, y, ' ', 0, size2);
        continue;
      }
      else
        enshow = 1;
    }
    OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0', 0, size2);
  }
}
/*!
 *  @brief  OLED 显示2个数字
 *  @param  u8  x      起点横坐标
 *  @param  u8  y      起点纵坐标
 *  @param  int16_t  num    显示的数字
 *  @param  u8  len    数字的位数
 *  @param  u8  size   字体大小
 *  @since  v1.0
 *  @note   OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
 *  Sample usage: OLED_ShowNum(80,3,score,2,16);
 */
void OLED_ShowNum_int16(u8 x, u8 y, int16_t num, u8 len, u8 size2)
{
    u8 t, temp;
    u8 enshow = 0;
    uint16_t abs_num = abs(num);  // 取num的绝对值

    for (t = 0; t < len; t++)
    {
        temp = (abs_num / OLED_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_ShowChar(x + (size2 / 2) * t, y, ' ', 0, size2);
                continue;
            }
            else
                enshow = 1;
        }
        OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0', 0, size2);
    }

    if (num < 0)  // 如果num是负数，在数字前面显示一个负号
    {
        OLED_ShowChar(x, y, '-', 0, size2);
    }
}
/**
  * @brief  OLED显示浮点数字（十进制，带符号数）
 *  @param  uint8_t  x      起点横坐标
 *  @param  uint8_t  y      起点纵坐标
  * @param  float	Number 要显示的数字
  * @param  uint8_t	Length 要显示数字的长度，范围：1~10
  * @param  uint8_t Flength 要显示的小数点后几位
	* @param  uint8_t size   字体大小
  * @retval 无
  */
void OLED_ShowNum_Float(uint8_t x, uint8_t y, float Number, uint8_t Length,uint8_t Flength,uint8_t size)
{
    uint8_t i;
    uint8_t flag = 5;
    float Number1;
    uint32_t Number2;
    if (Number >= 0)
    {
        OLED_ShowChar(x, y, '+',0,size);
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(x, y, '-',0,size);
        Number1 = -Number;
    }
    //将浮点数转换成整数然后显示
    Number2 = (int)(Number1 * OLED_pow(10,Flength));

    for (i = Length; i > 0; i--)                            
    {
        if(i == (Length - Flength))
        {
            OLED_ShowChar(x+ size/2*i + flag+6,y,'.',0,size);
            flag = 0;
            OLED_ShowChar(x+ size/2*i + flag+6, y, Number2 / OLED_pow(10, Length - i) % 10 + '0',0,size);
        }
        else
        {
            OLED_ShowChar(x+ size/2*i + flag+6, y, Number2 / OLED_pow(10, Length - i) % 10 + '0',0,size);
        }

    }    
}
/**
 * @brief  OLED 显示单字符
 * @param  u8  		 x      起点横坐标
 * @param  u8  		 y      起点纵坐标
 * @param  u8       char   显示的字符
 * @param  uint8_t  mode   显示模式 0,正常显示;1,反白显示
 * @param  u8       SIZE   字体大小 （12或16）
 * @since  V1.0
 * @note   在指定位置显示一个字符,包括部分字符
 * @par example:
           OLED_ShowChar(0, 0, 'w', 0, 12);//在(0,0)点显示一个大小为12的字符w
 */
void OLED_ShowChar(u8 x, u8 y, u8 chr, uint8_t mode, u8 SIZE)
{
  unsigned char c = 0, i = 0;
  c = chr - ' '; // 得到偏移后的值
  if (x > Max_Column - 1)
  {
    x = 0;
    y = y + 2;
  }
  if (SIZE == 16)
  {
    if (mode) // 反白
    {
      OLED_Set_Pos(x, y);
      for (i = 0; i < 8; i++)
        OLED_WrDat(~F8X16[c * 16 + i]);
      OLED_Set_Pos(x, y + 1);
      for (i = 0; i < 8; i++)
        OLED_WrDat(~F8X16[c * 16 + i + 8]);
    }
    else
    {
      OLED_Set_Pos(x, y);
      for (i = 0; i < 8; i++)
        OLED_WrDat(F8X16[c * 16 + i]);
      OLED_Set_Pos(x, y + 1);
      for (i = 0; i < 8; i++)
        OLED_WrDat(F8X16[c * 16 + i + 8]);
    }
  }
  else
  {
    if (mode) // 反白
    {
      OLED_Set_Pos(x, y);
      for (i = 0; i < 6; i++)
        OLED_WrDat(~F6x8[c][i]);
    }
    else
    {
      OLED_Set_Pos(x, y);
      for (i = 0; i < 6; i++)
        OLED_WrDat(F6x8[c][i]);
    }
  }
}

/**
 * @brief  OLED 显示字符串
 * @param  u16  		 x      起点横坐标
 * @param  u16  		 y      起点纵坐标 （16号字 ）
 * @param  uint8_t  *str   显示的字符串
 * @param  uint8_t  size   字体大小 （12或16）
 * @param  uint8_t  mode   显示模式  0,正常显示;1,反白显示
 * @since  v1.0
 * @note   包含中英文显示
* @par example:这里的y是零到八 不是零到64 
           OLED_ShowStr(0, 0, "w_pie", 12, 0);//在(0,0)点显示一个大小为12的字符串
 */
void OLED_ShowStr(u16 x, u16 y, uint8_t *str, uint8_t size1, uint8_t mode)
{
  u16 x0 = x;
  //uint16_t Index = 0;
  uint8_t bHz = 0;  // 字符或者中文
  while (*str != 0) // 数据未结束
  {
    if (!bHz)
    {
      if (x > 128)
        return;
      if (*str > 0x80)
        bHz = 1; // 中文
      else       // 字符
      {
        if (*str == 0x0D) // 换行符号
        {
          y += size1;
          x = x0;
          str++;
        }
        else
        {
          OLED_ShowChar(x, y, *str, mode, size1);
          x += size1 / 2;
          ; // 字符,为全字的一半
        }
        str++;
      }
    }
    else // 中文
    {
      if (x > 128)
        return;
      bHz = 0; // 有汉字库
      OLED_DrawFont16(x, y, str, mode);
      str += 2;
      x += size1; // 下一个汉字偏移
    }
  }
}

/*!
 *  @brief  OLED 自动居中显示字符串
 *  @param  u16  		 x      起点横坐标
 *  @param  u16  		 y      起点纵坐标
 *  @param  uint8_t  *str   显示的字符串
 *  @param  uint8_t  size   字体大小
 *  @param  uint8_t  mode   显示模式
 *  @since  v1.0
 *  @note   OLED_ShowStr_Center(u16 x, u16 y,uint8_t *str,uint8_t size1,uint8_t mode)
            自动居中显示  	x:0~127 y:0~63 mode:1,反白显示;0,正常显示
 *  Sample usage: OLED_ShowStr_Center(0, 1, "w_pie", 12, 0);
 */
void OLED_ShowStr_Center(u16 x, u16 y, uint8_t *str, uint8_t size1, uint8_t mode)
{
  u16 x0;
  uint8_t Str_Size;
  uint8_t bHz = 0; // 字符或者中文
  Str_Size = strlen((const char *)str);
  x = (128 - Str_Size * 8) / 2;
  x0 = x;
  while (*str != 0) // 数据未结束
  {
    if (!bHz) //! bHz)
    {
      if (x > 128)
        return;
      if (*str > 0x80)
        bHz = 1; // 中文
      else       // 字符
      {
        if (*str == 0x0D) // 换行符号
        {
          y += size1;
          x = x0;
          str++;
        }
        else
        {
          OLED_ShowChar(x, y, *str, mode, size1);
          x += size1 / 2;
          ; // 字符,为全字的一半
        }
        str++;
      }
    }
    else // 中文
    {
      if (x > 128)
        return;
      bHz = 0; // 有汉字库
      OLED_DrawFont16(x, y, str, mode);
      str += 2;
      x += size1; // 下一个汉字偏移
    }
  }
}

/*!
 *  @brief  OLED 显示单个汉字
 *  @param  u16  		 x      起点横坐标
 *  @param  u16  		 y      起点纵坐标
 *  @param  uint8_t  *str   显示的汉字
 *  @param  uint8_t  mode   显示模式
 *  @since  v1.0
 *  @note   OLED_DrawFont16(u16 x, u16 y, uint8_t *s,uint8_t mode)
            显示单个16X16中文字体  	x:0~127 y:0~63 mode:0,反白显示;1,正常显示
 *  Sample usage: OLED_DrawFont16(30, 3, "中文",  0);
 */
void OLED_DrawFont16(u16 x, u16 y, uint8_t *s, uint8_t mode)
{
  u16 k;
  u16 HZnum;
  HZnum = font_Size(); // 自动统计字库汉字数目
  for (k = 0; k < HZnum; k++)
  {
    if ((tfont16[k].Index[0] == *s) && (tfont16[k].Index[1] == *(s + 1)))
    {
      u8 t;

      if (!mode)
      {
        OLED_Set_Pos(x, y);
        for (t = 0; t < 16; t++)
        {
          OLED_WrDat(tfont16[k].Msk[t]);
        }
        OLED_Set_Pos(x, y + 1);
        for (t = 0; t < 16; t++)
        {
          OLED_WrDat(tfont16[k].Msk[t + 16]);
        }
      }
      else // 反白
      {
        OLED_Set_Pos(x, y);
        for (t = 0; t < 16; t++)
        {
          OLED_WrDat(~tfont16[k].Msk[t]);
        }
        OLED_Set_Pos(x, y + 1);
        for (t = 0; t < 16; t++)
        {
          OLED_WrDat(~tfont16[k].Msk[t + 16]);
        }
      }

      continue;
    }
    // continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
  }
}

/*!
 *  @brief  OLED 显示多个汉字
 *  @param  u16  		 x      起点横坐标
 *  @param  u16  		 y      起点纵坐标
 *  @param  uint8_t  *str   显示的汉字
 *  @param  uint8_t  mode   显示模式
 *  @since  v1.0
 *  @note   OLED_DrawFont16_Str(u16 x, u16 y,uint8_t *str,uint8_t mode)
            显示多个汉字(16X16)  	x:0~127 y:0~63 mode:0,反白显示;1,正常显示
 *  Sample usage: OLED_DrawFont16_Str(30, 3, "中文",  0);
 */
void OLED_DrawFont16_Str(u16 x, u16 y, uint8_t *str, uint8_t mode)
{
  uint8_t *p_Str = str;
  while (*p_Str != 0) // 数据未结束
  {
    OLED_DrawFont16(x, y, p_Str, mode);
    p_Str += 2;
    x += 16;
  }
}

/*!
 *  @brief  OLED 显示BMP图片
 *  @param  u8   x0      起始点横坐标
 *  @param  u8   y0      起始点纵坐标
 *  @param  u8   x1      结束点横坐标
 *  @param  u8   y1      结束点纵坐标
 *  @param  u8   BMP[]   显示的图片数据
 *  @since  V1.0
 *  @note   OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[])
            BMP[]为数组  	起始点坐标(x,y),x的范围0～127，y为页的范围0～7
 *  Sample usage: OLED_DrawBMP(0, 0,128, 8,BMP);
 */
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
  uint16_t j = 0;
  u8 x, y;
  if (y1 % 8 == 0)
    y = y1 / 8;
  else
    y = y1 / 8 + 1;
  for (y = y0; y < y1; y++)
  {
    OLED_Set_Pos(x0, y);
    for (x = x0; x < x1; x++)
    {
      OLED_WrDat(BMP[j++]);
    }
  }
}

/**
* @brief  OLED 初始化
* @pre    使用前需初始化硬件I2C
* @since  V1.0
* @par example:
                      OLED_Init();//OLED屏幕初始化
*/
void OLED_Init(void)
{
  //	I2C_Init(I2C_PORT);//I2C总线初始化
  delay_ms(200);
  OLED_WrCmd(0xae); //--关闭OLED显示
#if OLED_13
  OLED_WrCmd(0x02); //---set low column address（使用0.96寸时，改为0x00)
#else
  OLED_WrCmd(0x00);
#endif
	OLED_WrCmd(0x20); 			//--设置模式
  OLED_WrCmd(0x10);       //---页显示
  OLED_WrCmd(0x40);       //--设置显示开始行(0x00~0x3F)
  OLED_WrCmd(0x81);       //--对比度设置
  OLED_WrCmd(Brightness); // 255;默认0X7F (亮度设置,越大越亮)
  OLED_WrCmd(0xa0);       //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  OLED_WrCmd(0xc0);       // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  OLED_WrCmd(0xa6);       //--set normal display   a6为正常显示 a7为反向显示
  OLED_WrCmd(0xa8);       //--设置驱动路数(1 to 64)
  OLED_WrCmd(0x3f);       //--默认0X3F(1/64)
  OLED_WrCmd(0xd3);       //-//设置显示偏移(垂直）,Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WrCmd(0x00);       //-默认为0
  OLED_WrCmd(0xd5);       // 设置时钟分频因子,震荡频率
  OLED_WrCmd(0x80);       //[3:0],分频因子;[7:4],震荡频率, Set Clock as 100 Frames/Sec
  OLED_WrCmd(0xd9);       //--设置预充电周期
  OLED_WrCmd(0xf1);       // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WrCmd(0xda);       //--set com pins hardware configuration
  OLED_WrCmd(0x12);
  OLED_WrCmd(0xdb); //--设置VCOMH 电压倍率
  OLED_WrCmd(0x40); // Set VCOM Deselect Level
  OLED_WrCmd(0x20); //-设置内存地址模式 (0x00/0x01/0x02)
  OLED_WrCmd(0x02); ////[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10
  OLED_WrCmd(0x8d); //--电荷泵设置set Charge Pump enable/disable
  OLED_WrCmd(0x14); //--set(0x10) disable
  OLED_WrCmd(0xa4); // Disable Entire Display On (0xa4/0xa5)(白屏/黑屏）
  OLED_WrCmd(0xa6); // Disable Inverse Display On (0xa6/a7)(正常/反白）
  OLED_WrCmd(0xaf); //--开显示
  OLED_Clear();
}

