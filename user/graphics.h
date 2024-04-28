//#pragma once
//
//// #include "FreeRTOS.h"
//// #include "task.h"
//// #include "main.h"
//// #include "cmsis_os.h"
//
//#include "stdio.h"
//#include "stdint.h"
//#include "string.h"
//#include "stdarg.h"
//
//#include "ti_msp_dl_config.h"
//
///**
// * SPI2_CS      CS      PB12
// * SPI2_CLK     SCK     PB13
// * SPI2_MOSI    SDA     PB15
// * SPI2_MISO    RST     PB14
// * I2C2_SDA     DC      PF0
// */
//
//typedef float fp32;
//
//extern const unsigned char ASCII_12_32[][96];
//extern const unsigned char ASCII_8_16[][16];
//extern const unsigned char JetBrainMono[][16];
//
//#define USE_MONITOR 1
//
//#define BSP_LCD_SPI_HANDLE hspi3
//
//#define USE_HORIZONTAL 3
//
//#define L1 70
//#define L2 70
//
//#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
//#define LCD_W L1
//#define LCD_H L2
//
//#else
//#define LCD_W L2
//#define LCD_H L1
//#endif
//
//#if USE_HORIZONTAL == 0
//
//#define LCD_X_BIAS 52
//#define LCD_Y_BIAS 40
//
//#elif USE_HORIZONTAL == 1
//
//#define LCD_X_BIAS 53
//#define LCD_Y_BIAS 40
//
//#elif USE_HORIZONTAL == 2
//
//#define LCD_X_BIAS 40
//#define LCD_Y_BIAS 53
//
//#elif USE_HORIZONTAL == 3
//
//#define LCD_X_BIAS 40
//#define LCD_Y_BIAS 52
//
//#else
//#error "!!!UNKONWN USE_HORIZONTAL!!!"
//#endif
//
//#define TotalPixel (LCD_W * LCD_H)
//#define SizeOfGram (2 * TotalPixel)
//
//#define lcd_delay_ms(ms) delay_cycles(x * 32000)
//#define HAL_Delay(x) delay_cycles(x * 32000)
//
//#define LCD_Backlight_OFF DL_GPIO_clearPins(GPIO_SPI__PORT, GPIO_SPI__PIN_0_PIN) // BLK
//#define LCD_Backlight_ON DL_GPIO_setPins(GPIO_SPI__PORT, GPIO_SPI__PIN_0_PIN)
//
//#define LCD_DC_Command DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_LCD_DC_PIN) // DC
//#define LCD_DC_Data DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_LCD_DC_PIN)
//
//#define LCD_RES_Clr() DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_LCD_RES_PIN) // RES
//#define LCD_RES_Set() DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_LCD_RES_PIN)
//
//#define LCD_DC_Clr() DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_LCD_DC_PIN) // DC
//#define LCD_DC_Set() DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_LCD_DC_PIN)
//
////#define LCD_CS_Clr()  DL_GPIO_clearPins(GPIO_SPI_0_CS0_PORT, GPIO_SPI_0_CS0_PIN) // CS
////#define LCD_CS_Set()  DL_GPIO_setPins(GPIO_SPI_0_CS0_PORT, GPIO_SPI_0_CS0_PIN)
//#define LCD_CS_Clr()  ; // CS
//#define LCD_CS_Set()  ;
//
//#define LCD_BLK_Clr() DL_GPIO_clearPins(GPIO_SPI__PORT, GPIO_SPI__PIN_0_PIN) // BLK
//#define LCD_BLK_Set() DL_GPIO_setPins(GPIO_SPI__PORT, GPIO_SPI__PIN_0_PIN)
//
//#define TransColor888to565(Color)                \
//    (uint16_t)                                   \
//    {                                            \
//        ((uint16_t)((Color & 0x00F80000) >> 8) | \
//         (uint16_t)((Color & 0x0000FC00) >> 5) | \
//         (uint16_t)((Color & 0x000000F8) >> 3))  \
//    }
//
//void bsp_lcd_tx_state_idle(void);
//void bsp_lcd_set_region(uint16_t x, uint16_t x2, uint16_t y, uint16_t y2);
//void bsp_lcd_fill(uint16_t color);
//void bsp_lcd_transmit_buffer(void);
//void bsp_lcd_fill_region(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t color);
//void bsp_lcd_draw_point(uint32_t x, uint32_t y, uint16_t color);
//void bsp_lcd_draw_line(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2, uint16_t color);
//void bsp_lcd_draw_from_img(uint32_t x, uint32_t y, const uint8_t *IMG, uint8_t IMG_W, uint8_t IMG_H, uint16_t color);
//void bsp_lcd_draw_from_img_bgc(uint32_t x, uint32_t y, const uint8_t *IMG, uint8_t IMG_W, uint8_t IMG_H, uint16_t color, uint16_t BGcolor);
//void bsp_lcd_printf(uint32_t x, uint32_t y, uint32_t font_num, uint16_t color, char *fmt, ...);
//void bsp_lcd_printf_bgc(uint32_t x, uint32_t y, uint32_t font_num, uint16_t color, uint16_t BGcolor, char *fmt, ...);
//
//void bsp_lcd_draw_pic(uint16_t *pic, uint32_t W, uint32_t H);
//void bsp_lcd_fast_circle(uint32_t x, uint32_t y, uint32_t r, uint32_t color);
//void bsp_lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint32_t color);
//void bsp_lcd_ocs(int32_t data);
//void bsp_lcd_init(void);
//
//#define LCD_WHITE 0xFFFFFF
//#define LCD_BLACK 0x000000
//
//#define LCD_BLUE 0x0000FF
//#define LCD_GREEN 0x00FF00
//#define LCD_RED 0xFF0000
//#define LCD_CYAN 0x00FFFF
//#define LCD_MAGENTA 0xFF00FF
//#define LCD_YELLOW 0xFFFF00
//#define LCD_GREY 0x2C2C2C
//
//#define LIGHT_BLUE 0x8080FF
//#define LIGHT_GREEN 0x80FF80
//#define LIGHT_RED 0xFF8080
//#define LIGHT_CYAN 0x80FFFF
//#define LIGHT_MAGENTA 0xFF80FF
//#define LIGHT_YELLOW 0xFFFF80
//#define LIGHT_GREY 0xA3A3A3
//
//#define DARK_BLUE 0x000080
//#define DARK_GREEN 0x008000
//#define DARK_RED 0x800000
//#define DARK_CYAN 0x008080
//#define DARK_MAGENTA 0x800080
//#define DARK_YELLOW 0x808000
//#define DARK_GREY 0x404040
