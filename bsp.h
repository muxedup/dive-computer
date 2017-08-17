/** \file bsp.h
*
* @brief BSP support functions.
*
*/
#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
extern  "C" {
#endif

typedef enum
{
  SW1,
  SW2
} board_sw_id_t;

extern void     bsp_init(void);
extern void     bsp_halt(char const *, int16_t const);
extern uint8_t  bsp_btn_read(board_sw_id_t sw);

#ifdef __cplusplus
}
#endif

#endif /* BSP_H_ */
