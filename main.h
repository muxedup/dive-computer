/** \file main.h
*
* @brief Tone Generator Main Header File
*/

#ifndef _MAIN_H
#define _MAIN_H

// Relative Task Priorities (15 = highest; 0 = idle task)
#define  STARTUP_PRIO    (15)   // Highest priority, to launch others.
#define  ADC_PRIO        (10)   // Every 125 ms, in a timed loop.
#define  ALARM_PRIO      (8)    // Up to every 125 msec based on ADC sampling
#define  DISPLAY_PRIO    (7)    // Signaled via g_adc_mbox
#define  DIVE_CONTROLLER_PRIO       (7)
#define  TIMER_PRIO      (7)
#define  LED2_PRIO        (7)
#define  SPEAKER_PRIO        (7)
#define  BUTTON_PRIO        (7)

// Task Stack Sizes
#define STARTUP_TASK_STACK_SIZE     (1024)
#define ADC_TASK_STACK_SIZE         (1024)
#define ALARM_TASK_STACK_SIZE       (1024)
#define DISPLAY_TASK_STACK_SIZE     (1024)
#define DIVE_CONTROLLER_TASK_STACK_SIZE     (1024)
#define TIMER_TASK_STACK_SIZE     (1024)
#define LED2_TASK_STACK_SIZE     (1024)
#define SPEAKER_TASK_STACK_SIZE     (1024)
#define BUTTON_TASK_STACK_SIZE     (1024)

#define ADC_MSG_COUNT             10
#define DISPLAY_MSG_COUNT         20


//extern Mailbox_Handle g_adc_mbox;
//extern Mailbox_Handle g_display_mbox;
//extern Event_Handle g_event_handle;

#endif /* _MAIN_H */
