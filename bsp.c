/** \file bsp.c
*
* @brief BSP support functions.
*
*/
#include <stdint.h>
#include <ti/drivers/GPIO.h>
#include "Board.h"
#include "bsp.h"
#include "bsp_led.h"

// if a system assert fails, flash the red led
#define LED_FAST_FLASH_PAUSE ((uint32_t) 0xfffff)

// static function declarations
static void     safe_mode(void);
static void     led_blocking_wait(void);
static uint32_t bsp_master_int_disable(void);

/**
 * Initialize the BSP module. Must be called during system initialization.
 */
void bsp_init(void)
{
    // initialize the GPIO for user controller LEDs
    Board_initGPIO();   // For LED's and buttons

    // let the BSP LED Driver initialize. This just ensures the LED's are off
    bsp_led_init();
}

/**
 * Read switch input
 *
 * @param[in] sw - the switch input to read

 */
uint8_t  bsp_btn_read(board_sw_id_t sw)
{
    uint8_t pressed = 1;
    if(sw == SW1)
    {
        pressed = !GPIO_read(BOOSTERPACK_GPIO_SW1);
    }
    else if(sw == SW2)
    {
        pressed = !GPIO_read(BOOSTERPACK_GPIO_SW2);
    }
    return pressed;
}

/**
 * Disable processor interrupts.
 */
static uint32_t bsp_master_int_disable (void)
{
    //
    // Read PRIMASK and disable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
            "    cpsid   i\n"
            "    bx      lr\n");

    //
    // The following keeps the compiler happy, because it wants to see a
    // return value from this function.  It will generate code to return
    // a zero.  However, the real return is the "bx lr" above, so the
    // return(0) is never executed and the function returns with the value
    // you expect in R0.
    //
    return(0);
}

/**
 * An unrecoverable error has occurred. This function is called when an
 * assert has failed.
 *
 * @param[in] file_name - file name where the assert failed
 * @param[in] line_num - line number of the failed assert
 */
//lint -e{715} unused arguments
void bsp_halt (char const *file_name, int16_t const line_num)
{
    //! @todo if possible, log the filename and line number

    safe_mode();
}

/**
 * We have encountered a serious system error. Take the appropriate action to
 * get the system into a safe state.
 */
static void safe_mode (void)
{
    // we are here forever!
    (void) bsp_master_int_disable();

    for(;;)
    {
        // flash the red led
        bsp_led_toggle(LED_1);
        led_blocking_wait();
    }
}

/**
 * Blocking call used to flash an LED.
 */
static void led_blocking_wait (void)
{
    volatile uint32_t loop = LED_FAST_FLASH_PAUSE;

    while (loop-- > 0)
    {
    };
}
