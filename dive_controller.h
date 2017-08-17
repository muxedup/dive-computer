/*
 * dive_controller_task.h
 *
 *  Created on: Aug 17, 2017
 *      Author: munanxu
 */

#ifndef DIVE_CONTROLLER_H_
#define DIVE_CONTROLLER_H_

#define MAX_O2_TANK_VOL_CL 200000
#define INC_O2_TANK_CL 500
#define START_O2_TANK_CL 5000
#define TIMER_TICK_INTERVAL 500
#define MAX_DEPTH_MM 40000
void dive_controller_task(uint32_t, uint32_t);

#endif /* DIVE_CONTROLLER_H_ */
