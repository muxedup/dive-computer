/**
 * @file alarm.h
 *
 * @brief Public declarations for the alarm module.
 */
#ifndef _ALARM_H
#define _ALARM_H
#include <stdint.h>
void alarm_task(uint32_t arg0, uint32_t arg1);
void speaker_config (void);

// PWM Duty Cycles
typedef enum { TONE_HI = 450, TONE_MED = 700, TONE_LO = 950 } pwm_t;

// Waveform Data Structure
typedef struct
{
    pwm_t       tone1;      // PWM prescalar for Tone 1.
    pwm_t       tone2;      // PWM prescalar for Tone 2.
    uint16_t    interval;   // Seconds to play each tone, unless chopped.
    uint8_t     b_chopped;  // Ignore interval, use on/off chop instead.
} wave_t;

#endif /* _ALARM_H */
