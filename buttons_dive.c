/** \file pushbutton.c
*
* @brief Button Debouncer
*
*/

#include <assert.h>
#include <stdint.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include "main.h"
#include "bsp.h"
#include "Board.h"
//#include "pushbutton.h"
#include "buttons_dive.h"

extern Event_Handle g_event_handle;

void button_task(uint32_t arg0, uint32_t arg1)
{
    // State variables for debouncing SW1.
    uint8_t b_sw1_curr = 0;
    uint8_t b_sw1_prev = 0;
    uint8_t b_sw1_retriggered = 1;

    // State variables for debouncing SW2.
    uint8_t b_sw2_curr = 0;
    uint8_t b_sw2_prev = 0;


    (void)arg0;    // NOTE: Silence compiler warning about unused param.
    (void)arg1;

    for (;;)
    {
        // Delay for 50 ms. We are sampling approximately every 50msec
        Task_sleep(50);

        // Read the current state of the buttons.

        // Test button sw2.
        b_sw2_curr = bsp_btn_read(SW2);

        // Execute sw2 debouncing state machine.
        if ((1 == b_sw2_curr) && (1 == b_sw2_prev))
        {
            Event_post(g_event_handle, 0x04);
        }

        // Save current sw2 state for next cycle.
        b_sw2_prev = b_sw2_curr;

        // Test button sw1.
        b_sw1_curr = bsp_btn_read(SW1);

        // Execute sw1 debouncing state machine.
        if ((1 == b_sw1_curr) && (1 == b_sw1_prev))
        {
            if (b_sw1_retriggered)
            {
                Event_post(g_event_handle, 0x02);

                // Do not allow repeats while held down.
                b_sw1_retriggered = 0;
            }
        }
        else
        {
            // Button released; reset trigger.
            b_sw1_retriggered = 1;
        }
        // Save current sw1 state for next cycle.
        b_sw1_prev = b_sw1_curr;
    }
}
