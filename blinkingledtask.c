//Startup task.
#include "blinkingledtask.h"
#include <stdint.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/gates/GateMutexPri.h>
#include <xdc/runtime/Error.h>
#include "bsp_led.h"

//#include "startuptask.h"

/***** Defines *****/
#define LED2_TASK_STACK_SIZE 1024
#define LED2_TASK_PRIORITY   2 //todo assign priority



/***** Variable declarations *****/
static Task_Params led2TaskParams;
Task_Struct led2Task;    /* not static so you can see in ROV */
static uint8_t led2TaskStack[LED2_TASK_STACK_SIZE];

/***** Function definitions *****/
void led2Task_init( void )
{
    Task_Params_init(&led2TaskParams);
    led2TaskParams.stackSize = LED2_TASK_STACK_SIZE;
    led2TaskParams.priority = LED2_TASK_PRIORITY;
    led2TaskParams.stack = &led2TaskStack;

    Task_construct(&led2Task, led2TaskFunction, &led2TaskParams, NULL);
}

void led2TaskFunction(UArg arg0, UArg arg1)
{
    //LED2/blue shall blink a continuous 3 Hz software health indicator.
    for(;;)
    {
        bsp_led_toggle(LED_2);
        Task_sleep( 1500 );
    }

}
