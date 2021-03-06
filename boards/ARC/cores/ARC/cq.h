/**
 * \brief Circular Queue Logic Header File<br>
 *
 * \file cq.h
 *
 * \author Abhijit Bose( info@adharlabs.in )
 *        A.D.H.A.R Labs (http://adharlabs.in)
 *		      http://m8051.blogspot.com
 *
 * \version 0.0 - First Creation - 01,JULY,2012<br>
 *          0.1 - Modifications to Fit into Arduino ARC <br>
 *
 * \par License		: Creative Commons Attribution-ShareAlike 3.0
 *						Unported License.
 * Software License Agreement<br>
 * http://creativecommons.org/licenses/by-sa/3.0/legalcode
 *
 * DISCLAIMER:
 * THIS SOFTWARE IS PROVIDED IN AN &quot;AS IS&quot; CONDITION. <br>
 * NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING,<br>
 * BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY <br>
 * AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.<br>
 * AUTHOR SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,<br>
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */
/*-----------------------------------------------------------*/
#ifndef __CQUEUE_H__
#define __CQUEUE_H__
/*-----------------------------------------------------------*/
#include<stdint.h>
/*-----------------------------------------------------------*/
///Status Codes
#define CQ_STATUS_SUCCESS 					0
#define CQ_STATUS_ERROR   					1
#define CQ_STATUS_ERROR_QUEUE_EMPTY 		2
#define CQ_STATUS_ERROR_QUEUE_FULL 		3
#define CQ_STATUS_ERROR_QUEUE_NOTENABLED	4
#define CQ_STATUS_ERROR_QUEUE_ISENABLED	5
/*-----------------------------------------------------------*/
///Data Type Definition for the QUEUE
typedef struct {
	uint8_t * data; 	//To store the Actual Data
	uint16_t max;   	//Maximum Size of the array
	uint16_t front,rear;//Pointer for the queue
	uint16_t inuse;//For protected Queue Handling
}cqueue_t;
/*-----------------------------------------------------------*/
extern uint8_t cqueue_init(cqueue_t *q,uint8_t * buffer,uint16_t size);
#define cqueue_full cqueue_empty
extern uint8_t cqueue_empty(cqueue_t *q);
extern uint8_t cqueue_push(cqueue_t *q, uint8_t data);
extern uint8_t cqueue_pop(cqueue_t *q,uint8_t *data);
/* //API Disabled
extern uint8_t cqueue_copydata(cqueue_t *q,
	uint8_t *loc,uint16_t *copysz,uint16_t locsz);
extern uint8_t cqueue_movedata(cqueue_t *q,
	uint8_t *loc,uint16_t *movesz,uint16_t locsz);
extern uint8_t cqueue_movetoqueue(cqueue_t *q,
	uint8_t *loc,uint16_t *movesz,uint16_t locsz);
*/
/*-----------------------------------------------------------*/
#endif
/*-----------------------------------------------------------*/
