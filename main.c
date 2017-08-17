/**
 * @file main.c
 *
 * @brief Main entry point for the program.
 */

#include <stdint.h>
#include <stdio.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <xdc/runtime/Error.h>
#include "main.h"
#include "Board.h"
#include "bsp.h"
#include "bsp_led.h"
#include "common.h"
#include "alarm.h"
#include "protectedlcd.h"
#include "adc_dive.h"
#include "display_task.h"
#include "blinkingledtask.h"
#include "buttons_dive.h"
#include "dive_controller.h"
#include "timertask.h"
#include "display_task.h"
#include "alarmtask.h"
#include <time.h>

static void startup_task(uint32_t arg0, uint32_t arg1);

static Task_Handle g_startup_task_handle;

// Event Handle
Event_Handle g_event_handle;

// ADC mailbox and buffer
Mailbox_Handle g_adc_mbox;
//adc_mailbox_msg_t g_adc_buf[ADC_MSG_COUNT];

// Display mailbox and buffer
Mailbox_Handle g_display_mbox;
//display_mailbox_msg_t g_display_buf[DISPLAY_MSG_COUNT];


// static function declarations
static void startup_task(uint32_t, uint32_t);
/**
 *  Main entry point for the application.
 */
int main(void)
{
    Task_Params task_params;
    Error_Block eb;

    /* Call driver init functions */
    Board_initGeneral();

    // basic initialization of the BSP
    bsp_init();
    
    bsp_led_init();

    // Initialize the reentrant LCD drivers.
    protected_lcd_init();

    Board_initADC();
    // create the startup task
    Task_Params_init(&task_params);
    task_params.priority  = STARTUP_PRIO;
    task_params.stackSize = STARTUP_TASK_STACK_SIZE;
    Error_init(&eb);
    g_startup_task_handle = Task_create(startup_task, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (g_startup_task_handle != NULL));

    // enable interrupts and start the kernel
    BIOS_start();

    // should never get here!
    SYS_FAIL();

    return (0);
}

/**
 *  SYS/BIOS task. Creates all other tasks in the system.
 *
 *  @param[in] task_arg0 unused, argument from SYS/BIOS task create
 *  @param[in] task_arg1 unused, argument from SYS/BIOS task create
 */
/*lint -e{715} symbol not referenced */
static void startup_task(uint32_t arg0, uint32_t arg1)
{
    static Task_Params task_params;
    static Task_Handle task_handle;
    static Error_Block eb;
    static Mailbox_Params mbx_params_adc;
    static Mailbox_Struct mbx_struct_adc;
    static Mailbox_Params mbx_params_display;
    static Mailbox_Struct mbx_struct_display;

    // Create message queue for the ADC
    Mailbox_Params_init(&mbx_params_adc);
    Error_init(&eb);
    g_adc_mbox = Mailbox_create(sizeof(uint16_t*), ADC_MSG_COUNT, &mbx_params_adc, &eb);

    SYS_ASSERT(!Error_check(&eb) && g_adc_mbox != NULL);

    // Create message queue for the display
    Mailbox_Params_init(&mbx_params_display);
    g_display_mbox = Mailbox_create(sizeof(disp_msg_t*), DISPLAY_MSG_COUNT, &mbx_params_display, &eb);
    SYS_ASSERT(!Error_check(&eb) && g_display_mbox != NULL);

    // Create event for ADC/Button tasks
    Error_init(&eb);
    g_event_handle = Event_create(NULL, &eb);
    SYS_ASSERT(!Error_check(&eb));

    // Create the ADC task.
    Task_Params_init(&task_params);
    task_params.priority  = ADC_PRIO;
    task_params.stackSize = ADC_TASK_STACK_SIZE;
    task_handle = Task_create(adc_task, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    // Create the Alarm task.
    Task_Params_init(&task_params);
    task_params.priority  = ALARM_PRIO;
    task_params.stackSize = ALARM_TASK_STACK_SIZE;
    task_handle = Task_create(alarmTaskFunction, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    // Create the Display task.
    Task_Params_init(&task_params);
    task_params.priority  = DISPLAY_PRIO;
    task_params.stackSize = DISPLAY_TASK_STACK_SIZE;
    task_handle = Task_create(display_task, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    // Create the Dive Controller task.
    Task_Params_init(&task_params);
    task_params.priority = DIVE_CONTROLLER_PRIO;
    task_params.stackSize = DIVE_CONTROLLER_TASK_STACK_SIZE;
    task_handle = Task_create(dive_controller_task, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    // Create the Timer task.
    Task_Params_init(&task_params);
    task_params.priority = TIMER_PRIO;
    task_params.stackSize = TIMER_TASK_STACK_SIZE;
    task_handle = Task_create(timerTaskFunction, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    //Create the LED2 task.
    Task_Params_init(&task_params);
    task_params.priority = LED2_PRIO;
    task_params.stackSize = LED2_TASK_STACK_SIZE;
    task_handle = Task_create(led2TaskFunction, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    // Create the Button task.
    Task_Params_init(&task_params);
    task_params.priority = BUTTON_PRIO;
    task_params.stackSize = BUTTON_TASK_STACK_SIZE;
    task_handle = Task_create(button_task, &task_params, &eb);
    SYS_ASSERT(!Error_check(&eb) && (task_handle != NULL));

    // done with the startup task, can delete
    Task_delete(&g_startup_task_handle);
}


