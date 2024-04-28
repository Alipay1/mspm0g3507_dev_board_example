//#include "graphics.h"
//#include "fonts.h"
//
//#include "stdbool.h"
//
//#ifdef USE_MONITOR
//
//static bool IS_LCD_IN_TX_STATE = false;
//
//void bsp_lcd_tx_state_idle(void) { IS_LCD_IN_TX_STATE = false; }
//
//void SPI_Controller_transmitData(uint8_t *data, uint32_t dataLength,uint8_t dorc)
//{
//    int i = 0;
//    for (i = 0; i < dataLength; i++) {
//        while (DL_SPI_isBusy(SPI_0_INST))
//            ;
//        if(dorc){
//            LCD_DC_Data;
//        }else{
//            LCD_DC_Command;
//        }
//        DL_SPI_transmitData8(SPI_0_INST, data[i]);
//    }
//}
//
//static uint16_t framebuffer[TotalPixel+64];
//// uint16_t framebuffer[240 * 320 * 1 + 512];
//
//static void LCD_WriteCommand(uint8_t cmd)
//{
////    LCD_DC_Command;
////    LCD_DC_Command;
////    LCD_DC_Command;
////    LCD_DC_Command;
////    HAL_SPI_Transmit(&BSP_LCD_SPI_HANDLE, &cmd, 1, 1000);
//    // HAL_SPI_Transmit_DMA(&BSP_LCD_SPI_HANDLE, &cmd, 1);
//    SPI_Controller_transmitData(&cmd,1,0);
//}
//
//static void LCD_WriteByte(uint8_t data)
//{
////    LCD_DC_Data;
////    LCD_DC_Data;
////    LCD_DC_Data;
////    LCD_DC_Data;
////    HAL_SPI_Transmit(&BSP_LCD_SPI_HANDLE, &data, 1, 1000);
//    // HAL_SPI_Transmit_DMA(&BSP_LCD_SPI_HANDLE, &data, 1);
//    SPI_Controller_transmitData(&data,1,1);
//}
//
//static void LCD_WriteHalfWord(uint16_t data)
//{
//    uint8_t data_byte[2];
//    data_byte[0] = data >> 8;
//    data_byte[1] = data;
//    LCD_DC_Data;
////    HAL_SPI_Transmit(&BSP_LCD_SPI_HANDLE, data_byte, 2, 1000);
//    // HAL_SPI_Transmit_DMA(&BSP_LCD_SPI_HANDLE, data_byte, 2);
//    SPI_Controller_transmitData((uint8_t *)&data_byte,2,1);
//}
//
//void bsp_lcd_set_region(uint16_t x, uint16_t x2, uint16_t y, uint16_t y2)
//{
//    LCD_WriteCommand(0x2A);
//    LCD_WriteHalfWord(x + LCD_X_BIAS);
//    LCD_WriteHalfWord(x2 + LCD_X_BIAS);
//    LCD_WriteCommand(0x2B);
//    LCD_WriteHalfWord(y + LCD_Y_BIAS);
//    LCD_WriteHalfWord(y2 + LCD_Y_BIAS);
//    LCD_WriteCommand(0x2C);
//}
//
//void bsp_lcd_fill(uint16_t color)
//{
//    for (uint32_t i = 0; i < LCD_W * LCD_H * 1;)
//    {
//        framebuffer[i] = color;
//        i++;
//    }
//}
//
//void bsp_lcd_transmit_buffer(void)
//{
//    uint32_t i = 0;
//    bsp_lcd_set_region(0, LCD_W - 1, 0, LCD_H - 1);
//    LCD_DC_Data;
//    // HAL_SPI_Transmit(&hspi3, (uint8_t *)framebuffer, SizeOfGram, 1000);
//
////    while (IS_LCD_IN_TX_STATE)
////        ;
//
////    HAL_SPI_Transmit_DMA(&hspi3, (uint8_t *)framebuffer, SizeOfGram);
//
//    // extern DMA_HandleTypeDef hdma_spi3_tx;
//    // while (HAL_DMA_GetState(&hdma_spi3_tx) == HAL_DMA_STATE_BUSY)
//    //     ;
//
//
//    SPI_Controller_transmitData( (uint8_t *)framebuffer,SizeOfGram,1);
//}
//
//void bsp_lcd_fill_region(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t color)
//{
//    uint32_t i;
//    uint32_t tempx = 1 * x1;
//    uint32_t tempy = 0;
//    uint32_t base_bias = 1 * LCD_W * y1 + 1 * x1;
//    uint32_t iTotalPixel = (x2 - x1) * (y2 - y1);
//    for (i = 0; i < iTotalPixel;)
//    {
//        framebuffer[base_bias + tempx] = color;
//        tempx += 1;
//        if (tempx >= 1 * x2)
//        {
//            tempx = 1 * x1;
//            tempy++;
//            base_bias += (LCD_W * 1);
//        }
//        i++;
//    }
//    // LCD_Upgrade_Gram();
//}
//
//// void bsp_lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
//// {
////     LCD_SetRegion(x, x + 1, y, y + 1);
////     LCD_WriteHalfWord(color);
//// }
//
//void bsp_lcd_draw_point(uint32_t x, uint32_t y, uint16_t color)
//{
//    if(x >= LCD_W ||y >= LCD_H ){return;}
//    framebuffer[x * 1 + y * (LCD_W) * 1] = color;
//}
//
//// glib搴撲腑鐨勭敾绾垮嚱鏁帮紝鍙互鐢绘枩绾匡紝绾夸袱绔垎鍒槸(x1, y1)鍜�(x2, y2)
//void bsp_lcd_draw_line(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2, uint16_t color)
//{
//    int dx, dy, e;
//    dx = x2 - x1;
//    dy = y2 - y1;
//
//    if (dx >= 0)
//    {
//        if (dy >= 0) // dy>=0
//        {
//            if (dx >= dy) // 1/8 octant
//            {
//                e = dy - dx / 2;
//                while (x1 <= x2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        y1 += 1;
//                        e -= dx;
//                    }
//                    x1 += 1;
//                    e += dy;
//                }
//            }
//            else // 2/8 octant
//            {
//                e = dx - dy / 2;
//                while (y1 <= y2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        x1 += 1;
//                        e -= dy;
//                    }
//                    y1 += 1;
//                    e += dx;
//                }
//            }
//        }
//        else // dy<0
//        {
//            dy = -dy;     // dy=abs(dy)
//            if (dx >= dy) // 8/8 octant
//            {
//                e = dy - dx / 2;
//                while (x1 <= x2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        y1 -= 1;
//                        e -= dx;
//                    }
//                    x1 += 1;
//                    e += dy;
//                }
//            }
//            else // 7/8 octant
//            {
//                e = dx - dy / 2;
//                while (y1 >= y2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        x1 += 1;
//                        e -= dy;
//                    }
//                    y1 -= 1;
//                    e += dx;
//                }
//            }
//        }
//    }
//    else // dx<0
//    {
//        dx = -dx;    // dx=abs(dx)
//        if (dy >= 0) // dy>=0
//        {
//            if (dx >= dy) // 4/8 octant
//            {
//                e = dy - dx / 2;
//                while (x1 >= x2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        y1 += 1;
//                        e -= dx;
//                    }
//                    x1 -= 1;
//                    e += dy;
//                }
//            }
//            else // 3/8 octant
//            {
//                e = dx - dy / 2;
//                while (y1 <= y2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        x1 -= 1;
//                        e -= dy;
//                    }
//                    y1 += 1;
//                    e += dx;
//                }
//            }
//        }
//        else // dy<0
//        {
//            dy = -dy;     // dy=abs(dy)
//            if (dx >= dy) // 5/8 octant
//            {
//                e = dy - dx / 2;
//                while (x1 >= x2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        y1 -= 1;
//                        e -= dx;
//                    }
//                    x1 -= 1;
//                    e += dy;
//                }
//            }
//            else // 6/8 octant
//            {
//                e = dx - dy / 2;
//                while (y1 >= y2)
//                {
//                    bsp_lcd_draw_point(x1, y1, color);
//                    if (e > 0)
//                    {
//                        x1 -= 1;
//                        e -= dy;
//                    }
//                    y1 -= 1;
//                    e += dx;
//                }
//            }
//        }
//    }
//}
//
//void bsp_lcd_draw_from_img(uint32_t x, uint32_t y, const uint8_t *IMG, uint8_t IMG_W, uint8_t IMG_H, uint16_t color)
//{
//    uint32_t TotalCounter = 0;
//    uint32_t BitCounter = 0;
//    uint32_t Buffer = 0;
//    uint32_t tempx = x;
//    uint32_t tempy = y;
//
//    IMG_W += IMG_W % 8;
//
//    IMG_H += IMG_H % 8;
//
//    for (TotalCounter = 0; TotalCounter < IMG_W * IMG_H / 8;)
//    {
//        Buffer = *(IMG + TotalCounter);
//        for (BitCounter = 0; BitCounter < 8;)
//        {
//            if (Buffer & 0x01)
//            {
//                bsp_lcd_draw_point(tempx, tempy, color);
//            }
//
//            tempx++;
//            if (tempx >= x + IMG_W)
//            {
//                tempx = x;
//                tempy++;
//            }
//            Buffer >>= 1;
//            BitCounter++;
//        }
//
//        TotalCounter++;
//    }
//}
//
//void bsp_lcd_draw_from_img_bgc(uint32_t x, uint32_t y, const uint8_t *IMG, uint8_t IMG_W, uint8_t IMG_H, uint16_t color, uint16_t BGcolor)
//{
//
//    uint32_t TotalCounter = 0;
//    uint32_t BitCounter = 0;
//    uint32_t Buffer = 0;
//    uint32_t tempx = x;
//    uint32_t tempy = y;
//
//    IMG_W += IMG_W % 8;
//
//    IMG_H += IMG_H % 8;
//
//    for (TotalCounter = 0; TotalCounter < IMG_W * IMG_H / 8;)
//    {
//        Buffer = *(IMG + TotalCounter);
//        for (BitCounter = 0; BitCounter < 8;)
//        {
//            if (Buffer & 0x01)
//            {
//                bsp_lcd_draw_point(tempx, tempy, color);
//            }
//            else
//            {
//                bsp_lcd_draw_point(tempx, tempy, BGcolor);
//            }
//
//            tempx++;
//            if (tempx >= x + IMG_W)
//            {
//                tempx = x;
//                tempy++;
//            }
//            Buffer >>= 1;
//            BitCounter++;
//        }
//
//        TotalCounter++;
//    }
//}
//
//void bsp_lcd_printf(uint32_t x, uint32_t y, uint32_t font_num, uint16_t color, char *fmt, ...)
//{
//    uint32_t temp = 0;
//
//    uint32_t tempx = x;
//    uint32_t tempy = y;
//    uint32_t font_width;
//    uint32_t font_height;
//    uint32_t font_unit_size;
//    uint8_t buf[100];
//
//    unsigned char *pfont = NULL;
//    uint16_t len = strlen((const char *)fmt);
//    if (len > 100)
//    {
//        return;
//    }
//    va_list ap;
//    va_start(ap, fmt);
//    vsprintf((char *)buf, fmt, ap);
//    va_end(ap);
//    switch (font_num)
//    {
//    default:
//    case 1:
//        /* code */
//        pfont = (unsigned char *)ASCII_8_16;
//        font_width = 8;
//        font_height = 16;
//        font_unit_size = 16;
//        break;
//    case 2:
//        /* code */
//        pfont = (unsigned char *)ASCII_12_32;
//        font_width = 12;
//        font_height = 32;
//        font_unit_size = 96;
//        break;
//    case 3:
//        pfont = (unsigned char *)JetBrainMono;
//        font_width = 8;
//        font_height = 16;
//        font_unit_size = 16;
//        break;
//    }
//    for (temp = 0; temp < len;)
//    {
//        if (tempx >= LCD_W - font_width)
//        {
//            tempx = x;
//            tempy += font_height;
//        }
//        if (buf[temp] == '\r' | buf[temp] == '\n')
//        {
//            temp++;
//            tempx = x;
//            tempy += font_height;
//        }
//        if (buf[temp] == '\0')
//        {
//            break;
//        }
//        bsp_lcd_draw_from_img(tempx, tempy, pfont + ((buf[temp] - 32) * (font_unit_size)), font_width, font_height, color);
//        tempx += font_width;
//
//        temp++;
//    }
//}
//
//void bsp_lcd_printf_bgc(uint32_t x, uint32_t y, uint32_t font_num, uint16_t color, uint16_t BGcolor, char *fmt, ...)
//{
//    uint32_t temp = 0;
//
//    uint32_t tempx = x;
//    uint32_t tempy = y;
//    uint32_t font_width;
//    uint32_t font_height;
//    uint32_t font_unit_size;
//
//    //    uint32_t xnum;
//    //    uint32_t ynum;
//    uint8_t buf[200];
//
//    unsigned char *pfont = NULL;
//    uint16_t len = strlen((const char *)fmt);
//    if (len > 200)
//    {
//        return;
//    }
//    va_list ap;
//    va_start(ap, fmt);
//    vsprintf((char *)buf, fmt, ap);
//    va_end(ap);
//    switch (font_num)
//    {
//    default:
//    case 1:
//        /* code */
//        pfont = (unsigned char *)ASCII_8_16;
//        font_width = 8;
//        font_height = 16;
//        font_unit_size = 16;
//        break;
//    case 2:
//        /* code */
//        pfont = (unsigned char *)ASCII_12_32;
//        font_width = 12;
//        font_height = 32;
//        font_unit_size = 96;
//        break;
//    case 3:
//        pfont = (unsigned char *)JetBrainMono;
//        font_width = 8;
//        font_height = 16;
//        font_unit_size = 16;
//        break;
//    }
//
//    //    xnum = (LCD_W - x) / font_width;
//    //    ynum = 1 + len / xnum;
//    for (temp = 0; temp < len;)
//    {
//        if (tempx >= LCD_W - font_width)
//        {
//            tempx = x;
//            tempy += font_height;
//        }
//        if (buf[temp] == '\r' | buf[temp] == '\n')
//        {
//            temp++;
//            tempx = x;
//            tempy += font_height;
//        }
//        if (buf[temp] == '\0')
//        {
//            break;
//        }
//        bsp_lcd_draw_from_img_bgc(tempx, tempy, pfont + ((buf[temp] - 32) * (font_unit_size)), font_width, font_height, color, BGcolor);
//        tempx += font_width;
//
//        temp++;
//    }
//}
//
//void bsp_lcd_draw_pic(uint16_t *pic, uint32_t W, uint32_t H)
//{
//    uint32_t i = 0;
//    for (i = 0; i < W * H * 1;)
//    {
//        framebuffer[i] = pic[i];
//        i++;
//    }
//}
//
//static void LCD_CirclePlot(uint32_t x, uint32_t y, uint32_t xi, uint32_t yi, uint16_t color)
//{
//    bsp_lcd_draw_point(x + xi, y + yi, color);
//    bsp_lcd_draw_point(x + yi, y + xi, color);
//    bsp_lcd_draw_point(x - xi, y + yi, color);
//    bsp_lcd_draw_point(x - yi, y + xi, color);
//    bsp_lcd_draw_point(x - xi, y - yi, color);
//    bsp_lcd_draw_point(x - yi, y - xi, color);
//    bsp_lcd_draw_point(x + xi, y - yi, color);
//    bsp_lcd_draw_point(x + yi, y - xi, color);
//}
//
//void bsp_lcd_fast_circle(uint32_t x, uint32_t y, uint32_t r, uint32_t color)
//{
//    uint16_t Tcolor = TransColor888to565(color);
//
//    int xi;
//    int yi;
//    int di;
//    if ((int32_t)(x - r) < 0 || x + r > LCD_W || (int32_t)(y - r) < 0 || y + r > LCD_H)
//    {
//        return;
//    }
//    di = 0 - (r >> 1);
//    xi = 0;
//    yi = r;
//    while (yi >= xi)
//    {
//        LCD_CirclePlot(x, y, xi, yi, Tcolor);
//        xi++;
//        if (di < 0)
//        {
//            di += xi;
//        }
//        else
//        {
//            yi--;
//            di += xi - yi;
//        }
//    }
//}
//
//void bsp_lcd_fill_circle(uint16_t x0, uint16_t y0, uint16_t r, uint32_t color)
//{
//    uint16_t Tcolor = TransColor888to565(color);
//    int x, y;
//    int deltax, deltay;
//    int d;
//    int xi;
//    x = 0;
//    y = r;
//    deltax = 3;
//    deltay = 2 - r - r;
//    d = 1 - r;
//
//    bsp_lcd_draw_point(x + x0, y + y0, Tcolor);
//    bsp_lcd_draw_point(x + x0, -y + y0, Tcolor);
//    for (xi = -r + x0; xi <= r + x0; xi++)
//        bsp_lcd_draw_point(xi, y0, Tcolor); // 姘村钩绾垮～鍏�
//    while (x < y)
//    {
//        if (d < 0)
//        {
//            d += deltax;
//            deltax += 2;
//            x++;
//        }
//        else
//        {
//            d += (deltax + deltay);
//            deltax += 2;
//            deltay += 2;
//            x++;
//            y--;
//        }
//        for (xi = -x + x0; xi <= x + x0; xi++)
//        {
//            bsp_lcd_draw_point(xi, -y + y0, Tcolor);
//            bsp_lcd_draw_point(xi, y + y0, Tcolor); // 鎵弿绾垮～鍏�
//        }
//        for (xi = -y + x0; xi <= y + x0; xi++)
//        {
//            bsp_lcd_draw_point(xi, -x + y0, Tcolor);
//            bsp_lcd_draw_point(xi, x + y0, Tcolor); // 鎵弿绾垮～鍏呭叾閲�
//        }
//    }
//}
//
//static int32_t ocs_data[LCD_W];
//static uint32_t schedule;
//static int32_t ocs_max, ocs_min;
//static fp32 ocs_propotion = 1.0f;
//void bsp_lcd_ocs(int32_t data)
//{
//    if (data < LCD_H / 2 || data > -LCD_H / 2)
//    {
//        ocs_data[schedule] = data;
//    }
//    else if (data > LCD_H / 2)
//    {
//        ocs_data[schedule] = LCD_H / 2;
//    }
//    else if (data < -LCD_H / 2)
//    {
//        ocs_data[schedule] = -LCD_H / 2;
//    }
//    for (uint32_t i = 0; i < LCD_W;)
//    {
//        //        // bsp_lcd_draw_point(i, ocs_data[i] + 80, 0x0000);
//        //        if (data >= LCD_H / 2)
//        //        {
//        //            ocs_max = data;
//        //            ocs_propotion = LCD_H / (ocs_max - ocs_min);
//        //        }
//        //        else if (data <= -LCD_H / 2)
//        //        {
//        //            ocs_min = data;
//        //            ocs_propotion = LCD_H / (ocs_max - ocs_min);
//        //        }
//
//        if (i == 0)
//        {
//            bsp_lcd_draw_point(i, ocs_propotion * ocs_data[i] + LCD_H / 2, 0x0000);
//            i++;
//            continue;
//        }
//        if (i < schedule)
//        {
//            bsp_lcd_draw_line(i - 1, i, (uint32_t)(ocs_propotion * ocs_data[i - 1] + LCD_H / 2), (uint32_t)(ocs_propotion * ocs_data[i] + LCD_H / 2), 0x0000);
//        }
//        i++;
//    }
//
//    schedule++;
//    if (schedule >= LCD_W)
//    {
//        schedule = 0;
//        // BSP_LTDC_Clear(BSP_LTDC_COLOR_RED);
//        // memset(ocs_data, 0, LCD_W);
//    }
//}
//
//void bsp_lcd_init(void)
//{
//
//    LCD_CS_Clr();
//
//    LCD_RES_Clr(); // 澶嶄綅
//    HAL_Delay(10);
//    LCD_RES_Set();
//    HAL_Delay(10);
//
//    LCD_Backlight_ON; // 鎵撳紑鑳屽厜
//    HAL_Delay(120);
//
//    LCD_WriteCommand(0x11);
//    LCD_WriteCommand(0x11);
//    LCD_WriteCommand(0x11);
//
//    LCD_WriteCommand(0x36);
//    if (USE_HORIZONTAL == 0)
//        LCD_WriteByte(0x00);
//    else if (USE_HORIZONTAL == 1)
//        LCD_WriteByte(0xC0);
//    else if (USE_HORIZONTAL == 2)
//        LCD_WriteByte(0x70);
//    else
//        LCD_WriteByte(0xA0);
//
//    LCD_WriteCommand(0x3A);
//    LCD_WriteByte(0x05);
//
//    LCD_WriteCommand(0xB2);
//    LCD_WriteByte(0x0C);
//    LCD_WriteByte(0x0C);
//    LCD_WriteByte(0x00);
//    LCD_WriteByte(0x33);
//    LCD_WriteByte(0x33);
//
//    LCD_WriteCommand(0xB7);
//    LCD_WriteByte(0x35);
//
//    LCD_WriteCommand(0xBB);
//    LCD_WriteByte(0x19);
//
//    LCD_WriteCommand(0xC0);
//    LCD_WriteByte(0x2C);
//
//    LCD_WriteCommand(0xC2);
//    LCD_WriteByte(0x01);
//
//    LCD_WriteCommand(0xC3);
//    LCD_WriteByte(0x12);
//
//    LCD_WriteCommand(0xC4);
//    LCD_WriteByte(0x20);
//
//    LCD_WriteCommand(0xC6);
//    LCD_WriteByte(0x0F);
//
//    LCD_WriteCommand(0xD0);
//    LCD_WriteByte(0xA4);
//    LCD_WriteByte(0xA1);
//
//    LCD_WriteCommand(0xE0);
//    LCD_WriteByte(0xD0);
//    LCD_WriteByte(0x04);
//    LCD_WriteByte(0x0D);
//    LCD_WriteByte(0x11);
//    LCD_WriteByte(0x13);
//    LCD_WriteByte(0x2B);
//    LCD_WriteByte(0x3F);
//    LCD_WriteByte(0x54);
//    LCD_WriteByte(0x4C);
//    LCD_WriteByte(0x18);
//    LCD_WriteByte(0x0D);
//    LCD_WriteByte(0x0B);
//    LCD_WriteByte(0x1F);
//    LCD_WriteByte(0x23);
//
//    LCD_WriteCommand(0xE1);
//    LCD_WriteByte(0xD0);
//    LCD_WriteByte(0x04);
//    LCD_WriteByte(0x0C);
//    LCD_WriteByte(0x11);
//    LCD_WriteByte(0x13);
//    LCD_WriteByte(0x2C);
//    LCD_WriteByte(0x3F);
//    LCD_WriteByte(0x44);
//    LCD_WriteByte(0x51);
//    LCD_WriteByte(0x2F);
//    LCD_WriteByte(0x1F);
//    LCD_WriteByte(0x1F);
//    LCD_WriteByte(0x20);
//    LCD_WriteByte(0x23);
//
//    LCD_WriteCommand(0x21);
//
//    LCD_WriteCommand(0x29);
//}
//
//#endif
