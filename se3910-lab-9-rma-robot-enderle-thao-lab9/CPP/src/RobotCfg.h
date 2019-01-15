/**
 * @file
 * @author  Walter Schilling (schilling@msoe.edu)
 * @version 1.0
 *
 * @section LICENSE This is a piece of a template solution to the lab.
 *
 *
 * @section DESCRIPTION
 *      This file allows us to easily configure the robot for different IO setups. 
 */

#ifndef ROBOTCFG_H_
#define ROBOTCFG_H_

#define ALPHABOT2

/**
 * The following definitions are for the ALPHABOT.
 */
#ifdef ALPHABOT
#define AIN1 (12)
#define AIN2 (13)
#define ENA (6)
#define ENB (26)
#define BIN1 (21)
#define BIN2 (20)
#define DL (16)
#define DR (19)
#define IOCLK (25)
#define ADDR (24)
#define DOUT (23)
#define CHIPSEL (5)
#define BUZZER (4)


#endif

/**
 * The following definitions are for the ALPHABOT2.
 */
#ifdef ALPHABOT2
#define AIN1 (12)
#define AIN2 (13)
#define ENA (6)
#define ENB (26)
#define BIN1 (20)
#define BIN2 (21)
#define DL (16)
#define DR (19)
#define BUZZER (4)
#define IOCLK (25)
#define ADDR (24)
#define DOUT (23)
#define CHIPSEL (5)

#endif
#endif /* ROBOTCFG_H_ */
