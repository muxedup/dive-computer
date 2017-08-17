/** \file protectedlcd.h
*
* @brief Reentrant LCD driver.
*
*/

#ifndef _PROTECTEDLCD_H
#define _PROTECTEDLCD_H

void protected_lcd_init(void);
void protected_lcd_display(uint8_t position, char const *data);
void protected_lcd_clear(void);

#endif  /* _PROTECTEDLCD_H */
