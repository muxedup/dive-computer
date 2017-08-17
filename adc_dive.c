/*
 * adc_dive.c
 *
 *  Created on: Aug 17, 2017
 *      Author: a0227225
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// RTOS header files
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <xdc/runtime/Error.h>
#include <ti/drivers/ADC.h>

/* Example/Board Header files */
#include "main.h"
#include "Board.h"
#include "bsp.h"
#include "bsp_led.h"
#include "common.h"
#include "adc_dive.h"

extern Mailbox_Handle g_adc_mbox;
extern Event_Handle g_event_handle;

void adc_task (unsigned int task_arg0, unsigned int task_arg1){
    int_fast16_t res;
    uint16_t adcValue;
    ADC_Handle adc;
    ADC_Params params;
    ADC_Params_init(&params);
    adc = ADC_open(Board_ADC_JOYSTICK_Y, &params);
    if (adc == NULL) {
       ADC_close(adc);
    }
    for(;;){
    res = ADC_convert(adc, &adcValue);
    if (res == ADC_STATUS_SUCCESS) {
        Mailbox_post(g_adc_mbox, &adcValue, BIOS_WAIT_FOREVER);
        Event_post(g_event_handle, 0x08);
    }
    }

}
