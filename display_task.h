/*
 * display_task.h
 *
 *  Created on: Aug 17, 2017
 *      Author: a0226755
 */

#ifndef DISPLAY_TASK_H_
#define DISPLAY_TASK_H_

typedef struct
{
    bool unit_is_meters;
    int32_t depth_mm;       //depth in mm
    int32_t dive_rate_mm;    //dive rate in meters/m
    int32_t dive_time_elapsed_ms;    //elapsed dive time in milliseconds
    uint32_t oxygen_cl;      //oxygen left in centiliters
    uint8_t alarm_status;
} disp_msg_t;

#endif /* DISPLAY_TASK_H_ */
