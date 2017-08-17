//Startup task.
#include <alarmtask.h>
#include <stdint.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <xdc/runtime/Error.h>
#include <ti/drivers/PWM.h>
#include "bsp_led.h"
#include "alarm.h"

//#include "startuptask.h"

/***** Defines *****/
#define ALARM_TASK_STACK_SIZE 1024
#define ALARM_TASK_PRIORITY   2 //todo assign priority



/***** Variable declarations *****/
static Task_Params alarmTaskParams;
Task_Struct alarmTask;    /* not static so you can see in ROV */
static uint8_t alarmTaskStack[ALARM_TASK_STACK_SIZE];
uint32_t alarm_event;
Event_Handle g_alarm_event_handle;
PWM_Handle g_pwm_buzzer;
const wave_t *p_waveform;

static const wave_t alarm_low    = { TONE_LO,  TONE_MED, 2, 0};
static const wave_t alarm_medium = { TONE_MED, TONE_HI,  1, 0};
static const wave_t alarm_high   = { TONE_LO,  TONE_HI,  1, 1};

/***** Function definitions *****/
void alarmTask_init( void )
{
    Task_Params_init(&alarmTaskParams);
    alarmTaskParams.stackSize = ALARM_TASK_STACK_SIZE;
    alarmTaskParams.priority = ALARM_TASK_PRIORITY;
    alarmTaskParams.stack = &alarmTaskStack;

    Task_construct(&alarmTask, alarmTaskFunction, &alarmTaskParams, NULL);
}

void alarmTaskFunction(UArg arg0, UArg arg1)
{
        // Configure the speaker hardware.
    speaker_config();

//    Highest Priority: Insufficient air to safely ascend from current depth.
//    ii. Medium Priority: The current ascent rate is dangerous (> 15 m/min).
//    iii. Lowest Priority: The current depth exceeds the safe maximum (40 m).

    for(;;)
    {
        alarm_event = Event_pend(g_alarm_event_handle, 0, 0xFF, BIOS_WAIT_FOREVER);
        /*switch (alarm_event)
        {
        case ALARM_H:
        {
            // Select the correct waveform.
            p_waveform = &alarm_high;
        }
            break;
        case ALARM_M:
        {
            // Select the correct waveform.
            p_waveform = &alarm_medium;
        }
            break;
        case ALARM_L:
        {
            // Select the correct waveform.
            p_waveform = &alarm_low;
        }
            break;
        case ALARM_0:
        {
            PWM_setDuty(g_pwm_buzzer, 0);
        }
            break;
        default:
            break;
        }
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
            }*/
    }

}
