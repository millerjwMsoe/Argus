/*
 * TaskRates.h
 *
 *  This file defines task rates for the various tasks within the system.
 */

#ifndef TASKRATES_H_
#define TASKRATES_H_

#define PWM_TASK_RATE (1) // found
#define PWM_TASK_PRIORITY (0) // in SWPW

#define AD_TASK_RATE (5) // in navi
#define AD_TASK_PRIORITY (1) // in navi

#define CAMERA_CAPTURE_TASK_PRIORITY (0)


#define HORN_TASK_RATE (25) // found 
#define HORN_TASK_PRIORITY (2) // in horn 

#define NAV_TASK_RATE (1) // found
#define NAV_TASK_PRIORITY (0) // in navi

#define COLLISION_SENSING_TASK_RATE (75) // found
#define COLLISION_SENSING_TASK_PRIORITY (3) // collision

#define CTM_TASK_PERIOD (100) // found
#define CTM_TASK_PRIORITY (4)

#define CAMERA_CONTROLLER_TASK (125) // main
#define CAMERA_CONTROLLER_TASK_PRIORITY (5)


#endif /* TASKRATES_H_ */
