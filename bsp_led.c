
/** \file bsp_led.c
*
* @brief LED Driver
*/

#include <ti/sysbios/BIOS.h>
#include "Board.h"
#include "bsp_led.h"
#include "common.h"

typedef struct
{
    board_led_id_t              led_name;
    MSP_EXP432P401R_GPIOName    gpio_name;
} led_mapping_t;

static const led_mapping_t g_led_mapping[] =
{
    {LED_1, Board_GPIO_LED0},
    {LED_2, Board_GPIO_LED3}
};

/*!
* @brief Initialize the board's LEDs
*/
void bsp_led_init()
{
    bsp_led_off(LED_1);
    bsp_led_off(LED_2);
}

/*!
* @brief Turn on specified LED
* @param[in] Led  The LED number to be manipulated.
*/
void bsp_led_on(board_led_id_t Led)
{
    const led_mapping_t *p_led = g_led_mapping;

    for(uint32_t i = 0; i < COUNT_OF(g_led_mapping); ++i, ++p_led)
    {
        if(Led == p_led->led_name)
        {
            GPIO_write(p_led->gpio_name, Board_LED_ON);
            break;
        }
    }
}

/*!
* @brief Turn off specified LED
* @param[in] Led  The LED number to be manipulated.
*/
void bsp_led_off(board_led_id_t Led)
{
    const led_mapping_t *p_led = g_led_mapping;

    for(uint32_t i = 0; i < COUNT_OF(g_led_mapping); ++i, ++p_led)
    {
        if(Led == p_led->led_name)
        {
            GPIO_write(p_led->gpio_name, Board_LED_OFF);
            break;
        }
    }
}
/*!
* @brief Toggle specified LED
* @param[in] Led  The LED number to be manipulated.
*/
void bsp_led_toggle(board_led_id_t Led)
{
    const led_mapping_t *p_led = g_led_mapping;

    for(uint32_t i = 0; i < COUNT_OF(g_led_mapping); ++i, ++p_led)
    {
        if(Led == p_led->led_name)
        {
            GPIO_toggle(p_led->gpio_name);
            break;
        }
    }
}

