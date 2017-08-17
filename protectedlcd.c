/** \file protectedlcd.c
*
* @brief Reentrant LCD driver.
*
*/
#include <assert.h>
#include <stdint.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/gates/GateMutexPri.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "Board.h"
#include "bsp.h"
#include "common.h"
#include "protectedlcd.h"

// Private mutex
static GateMutexPri_Handle  g_lcd_mutex;

// Graphic library context
static Graphics_Context g_context;

/*!
* @brief Initialize the reentrant LCD driver.
*/
void protected_lcd_init(void)
{
    GateMutexPri_Params mutex_params;

    // Create the mutex that protects the hardware from race conditions.
    /* Obtain instance handle */
    GateMutexPri_Params_init(&mutex_params);
    g_lcd_mutex = GateMutexPri_create(&mutex_params, NULL);
    SYS_ASSERT(g_lcd_mutex != NULL);

    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_context, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_context, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_context, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_context, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_context);

}

/*!
* @brief Display data on the LCD, safely.
* @param[in] Position and data.
*/
void protected_lcd_display(uint8_t position, char const *data)
{
    int key;

    // Try to acquire the mutex.
    key = GateMutexPri_enter(g_lcd_mutex);

    // Safely inside the critical section.

    // Call the non-reentrant driver.
    Graphics_drawString(&g_context,
                            (int8_t *)data,
                            AUTO_STRING_LENGTH,
                            10,
                            position*10 + 10,
                            OPAQUE_TEXT);

    // Release the mutex.
    GateMutexPri_leave(g_lcd_mutex, key);
}

/*!
* @brief Display data on the LCD, safely.
* @param[in] Position and data.
*/
void protected_lcd_clear(void)
{
    int key;

    // Try to acquire the mutex.
    key = GateMutexPri_enter(g_lcd_mutex);

    // Safely inside the critical section.

    // Call the non-reentrant driver.
    Graphics_clearDisplay(&g_context);

    // Release the mutex.
    GateMutexPri_leave(g_lcd_mutex, key);
}
