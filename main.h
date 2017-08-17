/** \file main.h
*
* @brief Tone Generator Main Header File
*/

#ifndef _MAIN_H
#define _MAIN_H

// Relative Task Priorities (15 = highest; 0 = idle task)
#define  STARTUP_PRIO    (15)   // Highest priority, to launch others.
#define  ADC_PRIO        (9)   // Every 125 ms, in a timed loop.
#define  ALARM_PRIO      (8)    // Up to every 125 msec based on ADC sampling
#define  DISPLAY_PRIO    (8)    // Signaled via g_adc_mbox
#define  DIVE_CONTROLLER_PRIO       (8)
#define  TIMER_PRIO      (8)
#define  LED2_PRIO        (7)
#define  SPEAKER_PRIO        (8)
#define  BUTTON_PRIO        (10)

// Task Stack Sizes
#define STARTUP_TASK_STACK_SIZE     (2048)
#define ADC_TASK_STACK_SIZE         (2048)
#define ALARM_TASK_STACK_SIZE       (2048)
#define DISPLAY_TASK_STACK_SIZE     (4096)
#define DIVE_CONTROLLER_TASK_STACK_SIZE     (4096)
#define TIMER_TASK_STACK_SIZE     (1024)
#define LED2_TASK_STACK_SIZE     (1024)
#define SPEAKER_TASK_STACK_SIZE     (2048)
#define BUTTON_TASK_STACK_SIZE     (2048)

#define ADC_MSG_COUNT             10
#define DISPLAY_MSG_COUNT         20


//extern Mailbox_Handle g_adc_mbox;
//extern Mailbox_Handle g_display_mbox;
//extern Event_Handle g_event_handle;

#endif /* _MAIN_H */
