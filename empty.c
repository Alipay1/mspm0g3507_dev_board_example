/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"

//#include "graphics.h"
#include "lcd.h"

#include "stdio.h"

/* This results in approximately 0.5s of delay assuming 32MHz CPU_CLK */
#define DELAY (16000000)


volatile uint32_t uTick = 0;//滴答定时器中断计数

void SysTick_Handler(void)

{

  SysTick->CTRL &= ~(1 << 16); /*清除滴答定时器中断标志位*/

  uTick++;//滴答定时器中断计数

}

void delay_ms(uint32_t Delay)
{

  uint32_t tickstart = uTick;
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < UINT32_MAX)
  {
    wait += (uint32_t)(1);
  }

  while ((uTick - tickstart) < wait)
  {
  }

}

void MCAN_TX(void){
    DL_MCAN_TxBufElement txMsg;
    /* Initialize message to transmit. */
    /* Identifier Value. */
    txMsg.id = ((uint32_t)(0x4)) << 18U;
    /* Transmit data frame. */
    txMsg.rtr = 0U;
    /* 11-bit standard identifier. */
    txMsg.xtd = 0U;
    /* ESI bit in CAN FD format depends only on error passive flag. */
    txMsg.esi = 0U;
    /* Transmitting 4 bytes. */
    txMsg.dlc = 8U;
    /* CAN FD frames transmitted with bit rate switching. */
    txMsg.brs = 0U;
    /* Frame transmitted in CAN FD format. */
    txMsg.fdf = 0U;
    /* Store Tx events. */
    txMsg.efc = 1U;
    /* Message Marker. */
    txMsg.mm = 0xAAU;
    /* Data bytes. */
    txMsg.data[0] = 0x11;
    txMsg.data[1] = 0x22;
    txMsg.data[2] = 0x33;
    txMsg.data[3] = 0x44;
    txMsg.data[4] = 0x55;
    txMsg.data[5] = 0x66;
    txMsg.data[6] = 0x77;
    txMsg.data[7] = 0x88;


        /* Write Tx Message to the Message RAM. */
        DL_MCAN_writeMsgRam(MCAN0_INST, DL_MCAN_MEM_TYPE_BUF, 0U, &txMsg);

        /* Add request for transmission. */
        DL_MCAN_TXBufAddReq(MCAN0_INST, 0U);
}

char STR_BUF[64] = {0};

int main(void)
{
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();

    /* Default: LED1 and LED3 ON, LED2 OFF */
    DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_2_PIN);
    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
    LCD_Init();
    LCD_Init();
    LCD_Fill(0,0,LCD_W,LCD_H,0x0);

    while (1) {
        LCD_ShowString(10, 5,(uint8_t *)"[READY]", GREEN, BLACK, 32, 0);
        LCD_ShowString(10, 5+32,(uint8_t *)"Texas Instruments", RED, BLACK, 16, 0);
        LCD_ShowString(10, 5+32+16,(uint8_t *)"XMSM0G3507", BLUE, BLACK, 16, 0);
		snprintf(STR_BUF,64,"RunTime:%d",uTick / 1000);
        LCD_ShowString(10, 5+32+16+16,(uint8_t *)STR_BUF, YELLOW, BLACK, 16, 0);
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN | GPIO_LEDS_USER_LED_2_PIN);
        /*
         * Call togglePins API to flip the current value of LEDs 1-3. This
         * API causes the corresponding HW bits to be flipped by the GPIO HW
         * without need for additional R-M-W cycles by the processor.
         */
        delay_ms(1000);
    }
}
