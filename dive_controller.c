
#include <stdint.h>
#include <assert.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/ADC.h>
#include "main.h"
#include "bsp.h"
#include "Board.h"
#include "dive_controller.h"
#include "display_task.h"
#include "scuba.h"
#include "alarm.h"
#include "alarmtask.h"

extern Event_Handle g_event_handle;
extern Event_Handle g_alarm_event_handle;
extern Mailbox_Handle g_display_mbox;
extern Mailbox_Handle g_adc_mbox;

void dive_controller_task(uint32_t arg0, uint32_t arg1) {
    int32_t depth_mm = 0;
    int32_t dive_rate_mm = 0; // meters per minute
    int32_t gas_rate_cl = 0;
    uint32_t oxygen_cl = START_O2_TANK_CL;
    uint32_t oxygen_to_surf_cl = 0;
    int32_t dive_time_elapsed_ms = 0;

    uint16_t adc_value = 475;
    int32_t dive_time_remaining_s = 0;
    uint32_t eventReg = 0;

    uint8_t alarm_status, prev_alarm_status;
    disp_msg_t update_msg;
    disp_msg_t* p_update_msg;
    p_update_msg = &update_msg;

    unsigned char dummy_counter = 0;
    unsigned char unitsState = 0;
    //char dispString[20];
    prev_alarm_status = ALARM_0;

    for(;;) {
        //Task_sleep(1000);
        eventReg = Event_pend(g_event_handle, 0x0000,0x000F, BIOS_WAIT_FOREVER);
        // Handle new event
        switch(eventReg) {
        case 0x0001: // Timer elapsed update dive parameters
            depth_mm += depth_change_in_mm(dive_rate_mm);
            if (depth_mm > 0) {
                dive_time_elapsed_ms = 0;
            }
            if(dive_time_elapsed_ms > 0) {
                oxygen_cl -= gas_rate_in_cl(depth_mm);
                oxygen_to_surf_cl = gas_to_surface_in_cl(depth_mm);

                dive_time_elapsed_ms += TIMER_TICK_INTERVAL;
            }
            break;
        case 0x0002: // button 1 press
            unitsState = (unitsState > 0 ? 0 : 1);
            break;
        case 0x0004: // button 2 press
            if (depth_mm == 0) {
                oxygen_cl += INC_O2_TANK_CL;
            }
            break;
        case 0x0008: // adc event
            Mailbox_pend(g_adc_mbox, &adc_value, 10);
            dive_rate_mm = adc_to_rate(adc_value);
            break;
        default:
            break;
        }

        // set alerts

        if (oxygen_to_surf_cl > oxygen_cl) {
            // High alert
            alarm_status = ALARM_H;

        } else if (dive_rate_mm > 15) {
            // Medium alert
            alarm_status = ALARM_M;
        } else if (depth_mm < MAX_DEPTH_MM) {
            // low alert
            alarm_status = ALARM_L;
        } else {
            alarm_status = ALARM_0;
        }
        // Post event update if necessary
        if (alarm_status != prev_alarm_status) {
            Event_post(g_alarm_event_handle, alarm_status);
            alarm_status = prev_alarm_status;
        }
        // update display

        update_msg.unit_is_meters = 1;
        update_msg.depth_mm = dummy_counter++;
        update_msg.dive_rate_mm = dive_rate_mm;
        update_msg.dive_time_elapsed_ms = dive_time_elapsed_ms;
        update_msg.oxygen_cl = oxygen_cl;
        update_msg.alarm_status = alarm_status;

        Mailbox_post(g_display_mbox, &p_update_msg, 10);

        Task_sleep(50);
    }



}
