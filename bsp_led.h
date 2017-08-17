/** \file bsp_led.h
*
* @brief LED Driver
*/
#ifndef  __BSP_LED_H_
#define  __BSP_LED_H_



#ifdef __cplusplus
extern  "C" {
#endif

// Enumeration for LEDs
// STATUS_LED
// HEARTBEAT_LED
typedef enum
{
  LED_1,
  LED_2
} board_led_id_t;

// LED API
extern void  bsp_led_init  (void);
extern void  bsp_led_on    (board_led_id_t  led);
extern void  bsp_led_off   (board_led_id_t  led);
extern void  bsp_led_toggle(board_led_id_t  led);

#ifdef __cplusplus
}
#endif

#endif

