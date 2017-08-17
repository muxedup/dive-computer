/*
 * display_task.c
 *
 *  Created on: Aug 17, 2017
 *      Author: a0226755
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/drivers/ADC.h>
#include "main.h"
#include "Board.h"
#include "bsp.h"
#include "alarm.h"
#include "adc_dive.h"
#include "protectedlcd.h"
#include "common.h"
#include "display_task.h"
#include <String.h>
/**
 *  SYS/BIOS task. Displays to the LCD.
 *
 *  @param[in] task_arg0 unused, argument from SYS/BIOS task create
 *  @param[in] task_arg1 unused, argument from SYS/BIOS task create
 */
/*lint -e{715} symbol not referenced */
Mailbox_Handle g_display_mbox;
void display_task(uint32_t arg0, uint32_t arg1)
{
    // Draw the initial display.
    protected_lcd_display(LCD_LINE0, "DARMIN 3000");
    disp_msg_t*   msg;
    char buf[LCD_CHARS_PER_LINE+1];
    String units;
    int ret;

    int32_t depth_converted;
    for(;;)
    {
        // Pend on the message queue...
        // Wait for message from Dive Controller Task
        Mailbox_pend(g_display_mbox, &msg, BIOS_WAIT_FOREVER);

        if (msg->unit_is_meters) {
            units = "M";
            depth_converted = msg->depth_mm/1000;
        }
        else {
            units = "FT";
            depth_converted = (msg->depth_mm*13/4000);
            msg->dive_rate_mm = msg->dive_rate_mm*13/4;
        }

        memset(buf, '\0',LCD_CHARS_PER_LINE+1);

        ret = snprintf(buf, LCD_CHARS_PER_LINE, "DEPTH: %d %s", depth_converted, units);
        SYS_ASSERT(ret >= 0);
        protected_lcd_display(LCD_LINE2, buf);

        memset(buf, '\0',LCD_CHARS_PER_LINE+1);

        ret = snprintf(buf, LCD_CHARS_PER_LINE, "RATE: %d %s/min", msg->dive_rate_mm, units);
        SYS_ASSERT(ret >= 0);
        protected_lcd_display(LCD_LINE3, buf);

        memset(buf, '\0',LCD_CHARS_PER_LINE+1);

        ret = snprintf(buf, LCD_CHARS_PER_LINE, "AIR: %d L", msg->oxygen_cl/100);
        SYS_ASSERT(ret >= 0);
        protected_lcd_display(LCD_LINE4, buf);

        memset(buf, '\0',LCD_CHARS_PER_LINE+1);

        ret = snprintf(buf, LCD_CHARS_PER_LINE, "EDT: %d:%d:%d",msg->dive_time_elapsed_ms/(1000*60*60), (msg->dive_time_elapsed_ms%(1000*60*60))/(1000*60), ((msg->dive_time_elapsed_ms%(1000*60*60))%(1000*60))/1000);
        SYS_ASSERT(ret >= 0);
        protected_lcd_display(LCD_LINE5, buf);

        memset(buf, '\0',LCD_CHARS_PER_LINE+1);

        ret = snprintf(buf, LCD_CHARS_PER_LINE, "Alarm: %d", msg->alarm_status);
        SYS_ASSERT(ret >= 0);
        protected_lcd_display(LCD_LINE7, buf);

        memset(buf, '\0',LCD_CHARS_PER_LINE+1);

    }
}
