//Startup task.
#include <stdint.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Event.h>
#include "timertask.h"

/***** Defines *****/
#define TIMER_TASK_STACK_SIZE 1024
#define TIMER_TASK_PRIORITY   1

extern Event_Handle g_event_handle;

/***** Variable declarations *****/
static Task_Params timerTaskParams;
Task_Struct timerTask;    /* not static so you can see in ROV */
static uint8_t timerTaskStack[TIMER_TASK_STACK_SIZE];

/***** Function definitions *****/
void timerTask_init( void )
{
    Task_Params_init(&timerTaskParams);
    timerTaskParams.stackSize = TIMER_TASK_STACK_SIZE;
    timerTaskParams.priority = TIMER_TASK_PRIORITY;
    timerTaskParams.stack = &timerTaskStack;

    Task_construct(&timerTask, timerTaskFunction, &timerTaskParams, NULL);
}

void timerTaskFunction(UArg arg0, UArg arg1)
{
    // Every 500 ms, send a timer event to the dive logic task.
    // Time : bit 0
    for(;;)
    {
        Event_post(g_event_handle, 0x00);
        Task_sleep(500);
    }

}
