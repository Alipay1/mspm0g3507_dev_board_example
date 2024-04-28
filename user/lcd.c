#include "lcd.h"
#include "lcdfont.h"

/**
************************************************************************
* @brief:      	LCD_Writ_Bus: LCD涓茶鏁版嵁鍐欏叆鍑芥暟
* @param:      	dat - 瑕佸啓鍏ョ殑涓茶鏁版嵁
* @retval:     	void
* @details:    	灏嗕覆琛屾暟鎹啓鍏CD锛屾牴鎹娇鐢ㄧ殑閫氫俊鏂瑰紡閫夋嫨浣跨敤杞欢妯℃嫙SPI锛圲SE_ANALOG_SPI瀹忓畾涔変负鐪燂級鎴栫‖浠禨PI銆�
*               - 褰揢SE_ANALOG_SPI瀹忓畾涔変负鐪熸椂锛岄�氳繃GPIO鎺у埗SCLK銆丮OSI鍜孋S淇″彿锛屽惊鐜皢8浣嶆暟鎹啓鍏ャ��
*               - 褰揢SE_ANALOG_SPI瀹忓畾涔変负鍋囨椂锛岄�氳繃HAL_SPI_Transmit鍑芥暟浣跨敤纭欢SPI浼犺緭1瀛楄妭鏁版嵁銆�
************************************************************************
**/

//void SPI_Controller_transmitData(uint8_t *data, uint8_t dataLength)
//{
//    int i = 0;
//    for (i = 0; i < dataLength; i++) {
//        while (DL_SPI_isBusy(SPI_0_INST))
//            ;
//        DL_SPI_transmitData8(SPI_0_INST, data[i]);
//    }
//}
void LCD_Writ_Bus(uint8_t dat)
{
	LCD_CS_Clr();
#if USE_SIMULATE_SPI == 1
	for (uint8_t i = 0; i < 8; i++)
	{
		LCD_SCLK_Clr();
		if (dat & 0x80)
		{
			LCD_MOSI_Set();
		}
		else
		{
			LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat <<= 1;
	}
#else
//	SPI_Controller_transmitData(&dat,1);
    while (DL_SPI_isBusy(SPI_0_INST))
        ;
    DL_SPI_transmitData8(SPI_0_INST, dat);
#endif

	LCD_CS_Set();
}
/**
************************************************************************
* @brief:      	LCD_WR_DATA8: 鍚慙CD鍐欏叆8浣嶆暟鎹�
* @param:      	dat - 瑕佸啓鍏ョ殑8浣嶆暟鎹�
* @retval:     	void
* @details:    	璋冪敤LCD_Writ_Bus鍑芥暟灏�8浣嶆暟鎹啓鍏CD銆�
************************************************************************
**/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}
/**
************************************************************************
* @brief:      	LCD_WR_DATA: 鍚慙CD鍐欏叆16浣嶆暟鎹�
* @param:      	dat - 瑕佸啓鍏ョ殑16浣嶆暟鎹�
* @retval:     	void
* @details:    	璋冪敤LCD_Writ_Bus鍑芥暟灏�16浣嶆暟鎹殑楂�8浣嶅拰浣�8浣嶅垎鍒啓鍏CD銆�
************************************************************************
**/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}
/**
************************************************************************
* @brief:      	LCD_WR_REG: 鍚慙CD鍐欏叆瀵勫瓨鍣ㄥ湴鍧�
* @param:      	dat - 瑕佸啓鍏ョ殑瀵勫瓨鍣ㄥ湴鍧�
* @retval:     	void
* @details:    	閫氳繃璋冪敤LCD_Writ_Bus鍑芥暟鍚慙CD鍐欏叆瀵勫瓨鍣ㄥ湴鍧�銆�
************************************************************************
**/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr(); // 鍐欏懡浠�
	LCD_Writ_Bus(dat);
	LCD_DC_Set(); // 鍐欐暟鎹�
}
/**
************************************************************************
* @brief:      	LCD_Address_Set: 璁剧疆LCD鏄剧ず鍖哄煙鐨勫湴鍧�鑼冨洿
* @param:      	x1, y1, x2, y2 - 鏄剧ず鍖哄煙鐨勫乏涓婅鍜屽彸涓嬭鍧愭爣
* @retval:     	void
* @details:    	鏍规嵁灞忓箷鏂瑰悜閫氳繃璋冪敤LCD_WR_REG鍜孡CD_WR_DATA鍑芥暟锛岃缃甃CD鐨勫垪鍦板潃鍜岃鍦板潃锛岀劧鍚庡啓鍏ュ偍瀛樺櫒杩涜鏄剧ず銆�
************************************************************************
**/
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (USE_HORIZONTAL == 0)
	{
		LCD_WR_REG(0x2a); // 鍒楀湴鍧�璁剧疆
		LCD_WR_DATA(x1 + 52);
		LCD_WR_DATA(x2 + 52);
		LCD_WR_REG(0x2b); // 琛屽湴鍧�璁剧疆
		LCD_WR_DATA(y1 + 40);
		LCD_WR_DATA(y2 + 40);
		LCD_WR_REG(0x2c); // 鍌ㄥ瓨鍣ㄥ啓
	}
	else if (USE_HORIZONTAL == 1)
	{
		LCD_WR_REG(0x2a); // 鍒楀湴鍧�璁剧疆
		LCD_WR_DATA(x1 + 53);
		LCD_WR_DATA(x2 + 53);
		LCD_WR_REG(0x2b); // 琛屽湴鍧�璁剧疆
		LCD_WR_DATA(y1 + 40);
		LCD_WR_DATA(y2 + 40);
		LCD_WR_REG(0x2c); // 鍌ㄥ瓨鍣ㄥ啓
	}
	else if (USE_HORIZONTAL == 2)
	{
		LCD_WR_REG(0x2a); // 鍒楀湴鍧�璁剧疆
		LCD_WR_DATA(x1 + 40);
		LCD_WR_DATA(x2 + 40);
		LCD_WR_REG(0x2b); // 琛屽湴鍧�璁剧疆
		LCD_WR_DATA(y1 + 53);
		LCD_WR_DATA(y2 + 53);
		LCD_WR_REG(0x2c); // 鍌ㄥ瓨鍣ㄥ啓
	}
	else
	{
		LCD_WR_REG(0x2a); // 鍒楀湴鍧�璁剧疆
		LCD_WR_DATA(x1 + 40);
		LCD_WR_DATA(x2 + 40);
		LCD_WR_REG(0x2b); // 琛屽湴鍧�璁剧疆
		LCD_WR_DATA(y1 + 52);
		LCD_WR_DATA(y2 + 52);
		LCD_WR_REG(0x2c); // 鍌ㄥ瓨鍣ㄥ啓
	}
}
/**
************************************************************************
* @brief:      	LCD_Fill: 鍦↙CD鎸囧畾鍖哄煙濉厖鎸囧畾棰滆壊
* @param:      	xsta, ysta, xend, yend - 濉厖鍖哄煙鐨勫乏涓婅鍜屽彸涓嬭鍧愭爣
*              	color - 濉厖棰滆壊
* @retval:     	void
* @details:    	閫氳繃璋冪敤LCD_Address_Set鍑芥暟璁剧疆LCD鏄剧ず鍖哄煙鐨勫湴鍧�鑼冨洿锛岀劧鍚庡湪璇ヨ寖鍥村唴濉厖鎸囧畾棰滆壊銆�
************************************************************************
**/
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
	uint16_t i, j;
	LCD_Address_Set(xsta, ysta, xend - 1, yend - 1); // 璁剧疆鏄剧ず鑼冨洿
	for (i = ysta; i < yend; i++)
	{
		for (j = xsta; j < xend; j++)
		{
			LCD_WR_DATA(color);
		}
	}
}
/**
************************************************************************
* @brief:      	LCD_DrawPoint: 鍦↙CD鎸囧畾浣嶇疆鐢荤偣
* @param:      	x, y - 鐐圭殑鍧愭爣
*              	color - 鐐圭殑棰滆壊
* @retval:     	void
* @details:    	閫氳繃璋冪敤LCD_Address_Set鍑芥暟璁剧疆LCD鏄剧ず鍖哄煙鐨勫湴鍧�鑼冨洿锛岀劧鍚庡湪鎸囧畾浣嶇疆鐢荤偣锛岄鑹茬敱color鍙傛暟鎸囧畾銆�
************************************************************************
**/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_Address_Set(x, y, x, y); // 璁剧疆鍏夋爣浣嶇疆
	LCD_WR_DATA(color);
}
/**
************************************************************************
* @brief:      	LCD_DrawLine: 鍦↙CD涓婄敾绾�
* @param:      	x1, y1 - 绾跨殑璧峰鍧愭爣
*              	x2, y2 - 绾跨殑缁撴潫鍧愭爣
*              	color - 绾跨殑棰滆壊
* @retval:     	void
* @details:    	閫氳繃璁＄畻鍧愭爣澧為噺锛岄�夋嫨鍩烘湰澧為噺鍧愭爣杞达紝浠庤捣濮嬪潗鏍囧埌缁撴潫鍧愭爣閫愮偣鐢荤嚎锛岄鑹茬敱color鍙傛暟鎸囧畾銆�
************************************************************************
**/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; // 璁＄畻鍧愭爣澧為噺
	delta_y = y2 - y1;
	uRow = x1; // 鐢荤嚎璧风偣鍧愭爣
	uCol = y1;
	if (delta_x > 0)
		incx = 1; // 璁剧疆鍗曟鏂瑰悜
	else if (delta_x == 0)
		incx = 0; // 鍨傜洿绾�
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; // 姘村钩绾�
	else
	{
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
		distance = delta_x; // 閫夊彇鍩烘湰澧為噺鍧愭爣杞�
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++)
	{
		LCD_DrawPoint(uRow, uCol, color); // 鐢荤偣
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}
/**
************************************************************************
* @brief:      	LCD_DrawRectangle: 鍦↙CD涓婄敾鐭╁舰
* @param:      	x1, y1 - 鐭╁舰鐨勫乏涓婅鍧愭爣
*              	x2, y2 - 鐭╁舰鐨勫彸涓嬭鍧愭爣
*              	color - 鐭╁舰鐨勯鑹�
* @retval:     	void
* @details:    	閫氳繃璋冪敤LCD_DrawLine鍑芥暟鐢诲嚭鐭╁舰鐨勫洓鏉¤竟锛岄鑹茬敱color鍙傛暟鎸囧畾銆�
************************************************************************
**/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	LCD_DrawLine(x1, y1, x2, y1, color);
	LCD_DrawLine(x1, y1, x1, y2, color);
	LCD_DrawLine(x1, y2, x2, y2, color);
	LCD_DrawLine(x2, y1, x2, y2, color);
}
/**
************************************************************************
* @brief:      	Draw_Circle: 鍦↙CD涓婄敾鍦�
* @param:      	x0, y0 - 鍦嗗績鍧愭爣
*              	r - 鍦嗙殑鍗婂緞
*              	color - 鍦嗙殑棰滆壊
* @retval:     	void
* @details:    	浣跨敤涓偣鐢诲渾娉曪紝浠ュ渾蹇�(x0, y0)涓轰腑蹇冿紝鍗婂緞涓簉锛屽湪LCD涓婄敾鍑哄渾锛�
*              	棰滆壊鐢眂olor鍙傛暟鎸囧畾銆�
************************************************************************
**/
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
	int a, b;
	a = 0;
	b = r;
	while (a <= b)
	{
		LCD_DrawPoint(x0 - b, y0 - a, color); // 3
		LCD_DrawPoint(x0 + b, y0 - a, color); // 0
		LCD_DrawPoint(x0 - a, y0 + b, color); // 1
		LCD_DrawPoint(x0 - a, y0 - b, color); // 2
		LCD_DrawPoint(x0 + b, y0 + a, color); // 4
		LCD_DrawPoint(x0 + a, y0 - b, color); // 5
		LCD_DrawPoint(x0 + a, y0 + b, color); // 6
		LCD_DrawPoint(x0 - b, y0 + a, color); // 7
		a++;
		if ((a * a + b * b) > (r * r)) // 鍒ゆ柇瑕佺敾鐨勭偣鏄惁杩囪繙
		{
			b--;
		}
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowChinese: 鍦↙CD涓婃樉绀烘眽瀛楀瓧绗︿覆
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀烘眽瀛楀瓧绗︿覆鐨勫乏涓婅鍧愭爣
*              	s - 瑕佹樉绀虹殑姹夊瓧瀛楃涓诧紝姣忎釜姹夊瓧鍗犱袱涓瓧鑺�
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 姹夊瓧瀛椾綋澶у皬锛屾敮鎸�12x12銆�16x16銆�24x24銆�32x32
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鏍规嵁sizey閫夋嫨瀛椾綋澶у皬锛屽湪LCD涓婃樉绀烘眽瀛楀瓧绗︿覆锛屽彲浠ラ�夋嫨鏄剧ず妯″紡銆�
************************************************************************
**/
void LCD_ShowChinese(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	while (*s != 0)
	{
		if (sizey == 12)
			LCD_ShowChinese12x12(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 16)
			LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 24)
			LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 32)
			LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
		else
			return;
		s += 2;
		x += sizey;
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowChinese12x12: 鍦↙CD涓婃樉绀�12x12姹夊瓧
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀烘眽瀛楃殑宸︿笂瑙掑潗鏍�
*              	s - 瑕佹樉绀虹殑姹夊瓧锛屾瘡涓眽瀛楀崰涓や釜瀛楄妭
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 姹夊瓧瀛椾綋澶у皬锛屾敮鎸�12x12
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀�12x12姹夊瓧锛屽彲浠ラ�夋嫨鏄剧ず妯″紡銆�
************************************************************************
**/
void LCD_ShowChinese12x12(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j, m = 0;
	uint16_t k;
	uint16_t HZnum;		  // 姹夊瓧鏁扮洰
	uint16_t TypefaceNum; // 涓�涓瓧绗︽墍鍗犲瓧鑺傚ぇ灏�
	uint16_t x0 = x;
	TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;

	HZnum = sizeof(tfont12) / sizeof(typFNT_GB12); // 缁熻姹夊瓧鏁扮洰
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont12[k].Index[0] == *(s)) && (tfont12[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 闈炲彔鍔犳柟寮�
					{
						if (tfont12[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
						m++;
						if (m % sizey == 0)
						{
							m = 0;
							break;
						}
					}
					else // 鍙犲姞鏂瑰紡
					{
						if (tfont12[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 鐢讳竴涓偣
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 鏌ユ壘鍒板搴旂偣闃靛瓧搴撶珛鍗抽��鍑猴紝闃叉澶氫釜姹夊瓧閲嶅鍙栨ā甯︽潵褰卞搷
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowChinese16x16: 鍦↙CD涓婃樉绀�16x16姹夊瓧
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀烘眽瀛楃殑宸︿笂瑙掑潗鏍�
*              	s - 瑕佹樉绀虹殑姹夊瓧锛屾瘡涓眽瀛楀崰涓や釜瀛楄妭
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 姹夊瓧瀛椾綋澶у皬锛屾敮鎸�16x16
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀�16x16姹夊瓧锛屽彲浠ラ�夋嫨鏄剧ず妯″紡銆�
************************************************************************
**/
void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j, m = 0;
	uint16_t k;
	uint16_t HZnum;		  // 姹夊瓧鏁扮洰
	uint16_t TypefaceNum; // 涓�涓瓧绗︽墍鍗犲瓧鑺傚ぇ灏�
	uint16_t x0 = x;
	TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
	HZnum = sizeof(tfont16) / sizeof(typFNT_GB16); // 缁熻姹夊瓧鏁扮洰
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 闈炲彔鍔犳柟寮�
					{
						if (tfont16[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
						m++;
						if (m % sizey == 0)
						{
							m = 0;
							break;
						}
					}
					else // 鍙犲姞鏂瑰紡
					{
						if (tfont16[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 鐢讳竴涓偣
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 鏌ユ壘鍒板搴旂偣闃靛瓧搴撶珛鍗抽��鍑猴紝闃叉澶氫釜姹夊瓧閲嶅鍙栨ā甯︽潵褰卞搷
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowChinese24x24: 鍦↙CD涓婃樉绀�24x24姹夊瓧
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀烘眽瀛楃殑宸︿笂瑙掑潗鏍�
*              	s - 瑕佹樉绀虹殑姹夊瓧锛屾瘡涓眽瀛楀崰涓や釜瀛楄妭
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 姹夊瓧瀛椾綋澶у皬锛屾敮鎸�24x24
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀�24x24姹夊瓧锛屽彲浠ラ�夋嫨鏄剧ず妯″紡銆�
************************************************************************
**/
void LCD_ShowChinese24x24(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j, m = 0;
	uint16_t k;
	uint16_t HZnum;		  // 姹夊瓧鏁扮洰
	uint16_t TypefaceNum; // 涓�涓瓧绗︽墍鍗犲瓧鑺傚ぇ灏�
	uint16_t x0 = x;
	TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
	HZnum = sizeof(tfont24) / sizeof(typFNT_GB24); // 缁熻姹夊瓧鏁扮洰
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 闈炲彔鍔犳柟寮�
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
						m++;
						if (m % sizey == 0)
						{
							m = 0;
							break;
						}
					}
					else // 鍙犲姞鏂瑰紡
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 鐢讳竴涓偣
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 鏌ユ壘鍒板搴旂偣闃靛瓧搴撶珛鍗抽��鍑猴紝闃叉澶氫釜姹夊瓧閲嶅鍙栨ā甯︽潵褰卞搷
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowChinese32x32: 鍦↙CD涓婃樉绀�32x32姹夊瓧
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀烘眽瀛楃殑宸︿笂瑙掑潗鏍�
*              	s - 瑕佹樉绀虹殑姹夊瓧锛屾瘡涓眽瀛楀崰涓や釜瀛楄妭
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 姹夊瓧瀛椾綋澶у皬锛屾敮鎸�32x32
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀�32x32姹夊瓧锛屽彲浠ラ�夋嫨鏄剧ず妯″紡銆�
************************************************************************
**/
void LCD_ShowChinese32x32(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j, m = 0;
	uint16_t k;
	uint16_t HZnum;		  // 姹夊瓧鏁扮洰
	uint16_t TypefaceNum; // 涓�涓瓧绗︽墍鍗犲瓧鑺傚ぇ灏�
	uint16_t x0 = x;
	TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
	HZnum = sizeof(tfont32) / sizeof(typFNT_GB32); // 缁熻姹夊瓧鏁扮洰
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 闈炲彔鍔犳柟寮�
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
						m++;
						if (m % sizey == 0)
						{
							m = 0;
							break;
						}
					}
					else // 鍙犲姞鏂瑰紡
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 鐢讳竴涓偣
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 鏌ユ壘鍒板搴旂偣闃靛瓧搴撶珛鍗抽��鍑猴紝闃叉澶氫釜姹夊瓧閲嶅鍙栨ā甯︽潵褰卞搷
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowChar: 鍦↙CD涓婃樉绀哄崟涓瓧绗�
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀哄瓧绗︾殑宸︿笂瑙掑潗鏍�
*              	num - 瑕佹樉绀虹殑瀛楃鐨凙SCII鐮佸��
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 瀛椾綋澶у皬锛屾敮鎸�12x6, 16x8, 24x12, 32x16
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀哄崟涓瓧绗︼紝鍙互閫夋嫨鏄剧ず妯″紡鍜屼笉鍚岀殑瀛椾綋澶у皬銆�
************************************************************************
**/
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t temp, sizex, t, m = 0;
	uint16_t i, TypefaceNum; // 涓�涓瓧绗︽墍鍗犲瓧鑺傚ぇ灏�
	uint16_t x0 = x;
	sizex = sizey / 2;
	TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
	num = num - ' ';									 // 寰楀埌鍋忕Щ鍚庣殑鍊�
	LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1); // 璁剧疆鍏夋爣浣嶇疆
	for (i = 0; i < TypefaceNum; i++)
	{
		if (sizey == 12)
			temp = ascii_1206[num][i]; // 璋冪敤6x12瀛椾綋
		else if (sizey == 16)
			temp = ascii_1608[num][i]; // 璋冪敤8x16瀛椾綋
		else if (sizey == 24)
			temp = ascii_2412[num][i]; // 璋冪敤12x24瀛椾綋
		else if (sizey == 32)
			temp = ascii_3216[num][i]; // 璋冪敤16x32瀛椾綋
		else
			return;
		for (t = 0; t < 8; t++)
		{
			if (!mode) // 闈炲彔鍔犳ā寮�
			{
				if (temp & (0x01 << t))
					LCD_WR_DATA(fc);
				else
					LCD_WR_DATA(bc);
				m++;
				if (m % sizex == 0)
				{
					m = 0;
					break;
				}
			}
			else // 鍙犲姞妯″紡
			{
				if (temp & (0x01 << t))
					LCD_DrawPoint(x, y, fc); // 鐢讳竴涓偣
				x++;
				if ((x - x0) == sizex)
				{
					x = x0;
					y++;
					break;
				}
			}
		}
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowString: 鍦↙CD涓婃樉绀哄瓧绗︿覆
* @param:      	x, y - 璧峰鍧愭爣锛屾樉绀哄瓧绗︿覆鐨勫乏涓婅鍧愭爣
*              	p - 瑕佹樉绀虹殑瀛楃涓诧紝浠�'\0'缁撳熬
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 瀛椾綋澶у皬锛屾敮鎸�12x6, 16x8, 24x12, 32x16
*              	mode - 鏄剧ず妯″紡锛�1琛ㄧず鍙嶈壊锛�0琛ㄧず姝ｅ父鏄剧ず
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀哄瓧绗︿覆锛屽彲浠ラ�夋嫨鏄剧ず妯″紡鍜屼笉鍚岀殑瀛椾綋澶у皬銆�
************************************************************************
**/
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	while (*p != '\0')
	{
		LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
		x += sizey / 2;
		p++;
	}
}
/**
************************************************************************
* @brief:      	mypow: 璁＄畻m鐨刵娆℃柟
* @param:      	m - 搴曟暟
*              	n - 鎸囨暟
* @retval:     	uint32_t - m鐨刵娆℃柟
* @details:    	璁＄畻m鐨刵娆℃柟锛岃繑鍥炵粨鏋溿��
************************************************************************
**/
uint32_t mypow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}
/**
************************************************************************
* @brief:      	LCD_ShowIntNum: 鍦↙CD涓婃樉绀烘暣鏁版暟瀛�
* @param:      	x - x鍧愭爣
*              	y - y鍧愭爣
*              	num - 瑕佹樉绀虹殑鏁存暟
*              	len - 鏁板瓧鏄剧ず鐨勪綅鏁�
*              	fc - 瀛椾綋棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 瀛椾綋澶у皬
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀烘暣鏁版暟瀛楋紝鏀寔璁剧疆鏄剧ず鐨勪綅鏁般�佸瓧浣撻鑹层�佽儗鏅鑹插拰瀛椾綋澶у皬銆�
************************************************************************
**/
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	uint8_t sizex = sizey / 2;
	for (t = 0; t < len; t++)
	{
		temp = (num / mypow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
				continue;
			}
			else
				enshow = 1;
		}
		LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowFloatNum: 鍦↙CD涓婃樉绀烘牸寮忓寲鐨勬诞鐐规暟锛屾敮鎸佽礋鏁�
* @param:      	x - x鍧愭爣
*              	y - y鍧愭爣
*              	num - 瑕佹樉绀虹殑娴偣鏁�
*              	len - 鏁存暟浣嶆暟
*              	decimal - 灏忔暟浣嶆暟
*              	fc - 瀛楃殑棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 瀛椾綋澶у皬
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀烘牸寮忓寲鐨勬诞鐐规暟锛屾敮鎸佽缃暣鏁颁綅鏁般�佸皬鏁颁綅鏁般�佸瓧浣撻鑹层�佽儗鏅鑹插拰瀛椾綋澶у皬銆�
************************************************************************
**/
void LCD_ShowFloatNum(uint16_t x, uint16_t y, float num, uint8_t len, uint8_t decimal, uint16_t fc, uint16_t bc, uint8_t sizey)
{
	int16_t num_int;
	uint8_t t, temp, sizex;
	sizex = sizey / 2;
	num_int = num * mypow(10, decimal);

	if (num < 0)
	{
		LCD_ShowChar(x, y, '-', fc, bc, sizey, 0);
		num_int = -num_int;
		x += sizex;
		len++;
	}
	else
	{
		LCD_ShowChar(x, y, ' ', fc, bc, sizey, 0);
		num_int = num_int;
		x += sizex;
		len++;
	}

	// 鍦ㄦ洿鏂版暟瀛楁椂鍒锋柊鏄剧ず鐨勪綅缃�
	LCD_Fill(x, y, x + len * sizex + decimal + 1, y + sizey + 1, bc);

	for (t = 0; t < len; t++)
	{
		if (t == (len - decimal))
		{
			LCD_ShowChar(x + (len - decimal) * sizex, y, '.', fc, bc, sizey, 0);
			t++;
			len += 1;
		}
		temp = ((num_int / mypow(10, len - t - 1)) % 10) + '0';
		LCD_ShowChar(x + t * sizex, y, temp, fc, bc, sizey, 0);
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowFloatNum1: 鍦↙CD涓婃樉绀烘牸寮忓寲鐨勬诞鐐规暟锛屼笉鏀寔璐熸暟
* @param:      	x - x鍧愭爣
*              	y - y鍧愭爣
*              	num - 瑕佹樉绀虹殑娴偣鏁�
*              	len - 鏁存暟浣嶆暟
*              	decimal - 灏忔暟浣嶆暟
*              	fc - 瀛楃殑棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 瀛椾綋澶у皬
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀烘牸寮忓寲鐨勬诞鐐规暟锛屾敮鎸佽缃暣鏁颁綅鏁般�佸皬鏁颁綅鏁般�佸瓧浣撻鑹层�佽儗鏅鑹插拰瀛椾綋澶у皬銆�
************************************************************************
**/
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint8_t decimal, uint16_t fc, uint16_t bc, uint8_t sizey)
{
	int16_t num_int;
	uint8_t t, temp, sizex;
	sizex = sizey / 2;
	num_int = num * mypow(10, decimal);

	num_int = num_int;
	x += sizex;
	len++;

	// 鍦ㄦ洿鏂版暟瀛楁椂鍒锋柊鏄剧ず鐨勪綅缃�
	LCD_Fill(x, y, x + len * sizex + decimal + 1, y + sizey + 1, bc);

	for (t = 0; t < len; t++)
	{
		if (t == (len - decimal))
		{
			LCD_ShowChar(x + (len - decimal) * sizex, y, '.', fc, bc, sizey, 0);
			t++;
			len += 1;
		}
		temp = ((num_int / mypow(10, len - t - 1)) % 10) + '0';
		LCD_ShowChar(x + t * sizex, y, temp, fc, bc, sizey, 0);
	}
}
/**
************************************************************************
* @brief:      	LCD_ShowFloatNum1: 鍦↙CD涓婃樉绀烘牸寮忓寲鐨勬诞鐐规暟锛屼笉鏀寔璐熸暟
* @param:      	x - x鍧愭爣
*              	y - y鍧愭爣
*              	num - 瑕佹樉绀虹殑娴偣鏁�
*              	len - 鏁存暟浣嶆暟
*              	decimal - 灏忔暟浣嶆暟
*              	fc - 瀛楃殑棰滆壊
*              	bc - 鑳屾櫙棰滆壊
*              	sizey - 瀛椾綋澶у皬
* @retval:     	void
* @details:    	鍦↙CD涓婃樉绀烘牸寮忓寲鐨勬诞鐐规暟锛屾敮鎸佽缃暣鏁颁綅鏁般�佸皬鏁颁綅鏁般�佸瓧浣撻鑹层�佽儗鏅鑹插拰瀛椾綋澶у皬銆�
************************************************************************
**/
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[])
{
	uint16_t i, j;
	uint32_t k = 0;
	LCD_Address_Set(x, y, x + length - 1, y + width - 1);
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < width; j++)
		{
			LCD_WR_DATA8(pic[k * 2]);
			LCD_WR_DATA8(pic[k * 2 + 1]);
			k++;
		}
	}
}
/**
************************************************************************
* @brief:      	LCD_Init: LCD鍒濆鍖栧嚱鏁�
* @param:      	void
* @details:    	鎵цLCD鐨勫垵濮嬪寲杩囩▼锛屽寘鎷浣嶃�佽儗鍏夋帶鍒躲�佸瘎瀛樺櫒閰嶇疆绛�
* @retval:     	void
************************************************************************
**/
void LCD_Init(void)
{
    LCD_RES_Clr();//¸´λ
    HAL_Delay(100);
    LCD_RES_Set();
    HAL_Delay(100);

    LCD_BLK_Set();//´򿪱³¹⍊  delay_ms(100);

    LCD_WR_REG(0x11);
    HAL_Delay(120);
    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
    else LCD_WR_DATA8(0xA0);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x35);

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x19);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x12);

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x0F);

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xD0);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x2B);
    LCD_WR_DATA8(0x3F);
    LCD_WR_DATA8(0x54);
    LCD_WR_DATA8(0x4C);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x0B);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x23);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0xD0);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x3F);
    LCD_WR_DATA8(0x44);
    LCD_WR_DATA8(0x51);
    LCD_WR_DATA8(0x2F);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x20);
    LCD_WR_DATA8(0x23);

    LCD_WR_REG(0x21);

    LCD_WR_REG(0x29);
}
