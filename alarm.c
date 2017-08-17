/** \file alarm.c
*
* @brief Alarm Manager and buzzer/speaker output
*/
#include <stdint.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <xdc/runtime/Error.h>
#include <ti/drivers/PWM.h>
#include "main.h"
#include "Board.h"
#include "bsp.h"
#include "alarm.h"
#include "common.h"

static const wave_t alarm_low    = { TONE_LO,  TONE_MED, 2, 0};
static const wave_t alarm_medium = { TONE_MED, TONE_HI,  1, 0};
static const wave_t alarm_high   = { TONE_LO,  TONE_HI,  1, 1};

// Speaker Task Items
static PWM_Handle g_pwm_buzzer = NULL;

/*!
*
* @brief Configure a timer to drive the speaker via PWM.
*/
void speaker_config (void)
{
    PWM_Params params;

    /* Call driver init functions. */
    PWM_init();

    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = 0;
    params.periodUnits = PWM_PERIOD_US; // Specified in microseconds
    params.periodValue = 1000;        // 1000 Hz is our period which happens to be 1000 usec
    g_pwm_buzzer = PWM_open(Board_PWMBuzzer, &params);
    /* Board_PWM0 did not open */
    SYS_ASSERT(g_pwm_buzzer != NULL);

    PWM_start(g_pwm_buzzer);
}

/**
 *  SYS/BIOS task. Handles writing to the speaker.
 *
 *  @param[in] task_arg0 unused, argument from SYS/BIOS task create
 *  @param[in] task_arg1 unused, argument from SYS/BIOS task create
 */
/*lint -e{715} symbol not referenced */
void speaker_task(uint32_t arg0, uint32_t arg1)
{
    wave_t const *  p_waveform = (wave_t const *) arg0;
    SYS_ASSERT(p_waveform != NULL);
    if (p_waveform->b_chopped)
    {
        // Create a chopped sound.
        for (;;)
        {
            // Play Tone 1.
            PWM_setDuty(g_pwm_buzzer, (uint32_t)p_waveform->tone1);
            Task_sleep(125);
            PWM_setDuty(g_pwm_buzzer, 0);
            Task_sleep(125);
            PWM_setDuty(g_pwm_buzzer, (uint32_t)p_waveform->tone1);
            Task_sleep(125);
            PWM_setDuty(g_pwm_buzzer, 0);
            Task_sleep(125);

            // Play Tone 2.
            PWM_setDuty(g_pwm_buzzer, (uint32_t)p_waveform->tone2);
            Task_sleep(125);
            PWM_setDuty(g_pwm_buzzer, 0);
            Task_sleep(125);
            PWM_setDuty(g_pwm_buzzer, (uint32_t)p_waveform->tone2);
            Task_sleep(125);
            PWM_setDuty(g_pwm_buzzer, 0);
            Task_sleep(125);
        }
    }
    else
    {
        // No chopping.
        for (;;)
        {
            // Play Tone 1.
            PWM_setDuty(g_pwm_buzzer, (uint32_t)p_waveform->tone1);
            Task_sleep(p_waveform->interval);
            PWM_setDuty(g_pwm_buzzer, 0);

            // Play Tone 2.
            PWM_setDuty(g_pwm_buzzer, (uint32_t)p_waveform->tone2);
            Task_sleep(p_waveform->interval);
            PWM_setDuty(g_pwm_buzzer, 0);
        }
    }
}
