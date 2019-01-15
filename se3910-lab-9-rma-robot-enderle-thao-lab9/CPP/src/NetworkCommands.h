 /**
 * @file
 * @author  Walter Schilling (schilling@msoe.edu)
 * @version 1.0
 *
 * @section LICENSE This is a piece of a template solution to the lab.
 *
 *
 * @section DESCRIPTION
 *
 * This file defines the values that are sent over the network to for the given commands.
 */

#ifndef NETWORKCOMMANDS_H_
#define NETWORKCOMMANDS_H_

/**
 * This segment defines the destination queues and devices for the given messages.
 */
#define MOTOR_CONTROL_DESTINATION (0x00000001)
#define NAV_CONTROL_DESTINATION   (0x00000002)
#define CAMERA_CONTROL_DESTINATION (0x00000003)

/**
 * This command indicates that the rest of the word being sent over the network is consumed by the speed setting.
 */
#define SPEEDDIRECTIONBITMAP  0x40000000

/**
 * These are definitions related to the control of the robot via the network.
 */
#define MOTORDIRECTIONBITMAP  0x20000000


/**
 * This definition indicates that there is a message related to collision management to be processed.
 */
#define COLLISIONBITMAP       0x10000000

#define COLLISION_SENSED      0x0000A5A5
#define COLLISION_CLEARED     0x00005A5A




/**
 * This indicates the value that is or'ed with the MOTORDIRECTIONBITMAP to indicate that the direction of the robot is to be forward.
 */
#define  FORWARD  0x00000001
/**
 * This indicates the value that is or'ed with the MOTORDIRECTIONBITMAP to indicate that the direction of the robot is to be backward.
 */
#define  BACKWARD  0x00000002
/**
 * This indicates the value that is or'ed with the MOTORDIRECTIONBITMAP to indicate that the direction of the robot is to be left.
 */
#define  LEFT  0x00000004
/**
 * This indicates the value that is or'ed with the MOTORDIRECTIONBITMAP to indicate that the direction of the robot is to be right.
 */
#define  RIGHT  0x00000008
/**
 * This indicates the value that is or'ed with the MOTORDIRECTIONBITMAP to indicate that the robot is to stop.
 */
#define  STOP  0x00000010

/**
 * This definition is a combination of all motor directions, and can be used as a generic mask when commands are sent.
 */
#define MOTORDIRECTIONS (FORWARD | BACKWARD | LEFT | RIGHT| STOP)

/**
 * This definition defined the network message that will start the white calibration on the robot.
 */
#define START_WHITE_CALIBRATION (0x00000001)

/**
 * This definition defined the network message that will start the black calibration on the robot.
 */
#define START_BLACK_CALIBRATION (0x00000002)

/**
 * This definition defined the network message that will start the robot line following.
 */
#define START_LINE_FOLLOWING (0x00000004)

/**
 * This definition defined the network message that will stop the robot line following.
 */
#define STOP_LINE_FOLLOWING (0x00000008)


#define ELEVATION_FLAG      (0x20000000)
#define  AZMUTH_FLAG        (0x40000000)

/**
 * This definition will cause the diagnostic report to be issued on the robot.
 */
#define DIAGNOSTIC_REPORT_REQUEST (0x00000001)

/**
 * This will cause the battery voltage to display.
 */
#define DIAGNOSTIC_BATTERY_VOLTAGE_DISPLAY_REQUEST (0x00000010)
/**
 * This will reset the diagnostic status of the robot.
 */
#define DIAGNOSTIC_RESET_REQUEST  (0x08000000)

#endif /* NETWORKCOMMANDS_H_ */
