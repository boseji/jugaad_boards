/**
 * \brief Circular Queue Logic Implementation<br>
 *
 * \file cq.c
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
#include "cq.h"
/*-----------------------------------------------------------*/ 
///Function Control Codes
// NOT IMPLEMENTED
/*-----------------------------------------------------------*/ 
///Internal Function to Enable the Queue
static uint8_t cqueue_enable(cqueue_t *q)
{
	if(q->inuse) return CQ_STATUS_ERROR;
	q->inuse = 1;
	return CQ_STATUS_SUCCESS;
}
///Internal Function to Disable the Queue
static uint8_t cqueue_disable(cqueue_t *q)
{
	if(!(q->inuse)) return CQ_STATUS_ERROR;
	q->inuse = 0;
	return CQ_STATUS_SUCCESS;
}
///Function to Initialize the Queue
/// buffer - Array to store the data
/// size - size of the storage array
uint8_t cqueue_init(cqueue_t *q,uint8_t * buffer,uint16_t size)
{
	if(q->inuse) return CQ_STATUS_ERROR_QUEUE_ISENABLED;
	q->data = buffer;
	q->max = size;
	q->front = size -1;
	q->rear = size -1;
	return cqueue_enable(q);
}
///Function to Check if the Queue is Empty(Same for Full)
uint8_t cqueue_empty(cqueue_t *q)
{
	if(q->front == q->rear)
		return CQ_STATUS_SUCCESS;
	else
		return CQ_STATUS_ERROR;
}
///Function to Insert an element into the Queue
uint8_t cqueue_push(cqueue_t *q, uint8_t data)
{	
	if(q->inuse)
	{
		//ENTER_CRITICAL_SECTION
		cqueue_disable(q);
		//{
		if(q->rear == q->max-1)
			q->rear = 0;
		else
			q->rear++;
			
		if(cqueue_full(q)==CQ_STATUS_SUCCESS)//Check if Queue is Full
		{
			if(q->rear == 0)
				q->rear = q->max-1;
			else
				q->rear--;
			//}
			cqueue_enable(q);
			//EXIT_CRITICAL_SECTION
			return CQ_STATUS_ERROR_QUEUE_FULL;
		}
		q->data[q->rear] = data;
		//}
		cqueue_enable(q);
		//EXIT_CRITICAL_SECTION
		return CQ_STATUS_SUCCESS;
	}
	return CQ_STATUS_ERROR_QUEUE_NOTENABLED;
}
///Function to Delete an element from the Queue
uint8_t cqueue_pop(cqueue_t *q,uint8_t *data)
{
	if(q->inuse&1)
	{		
		if(cqueue_empty(q)!=CQ_STATUS_SUCCESS)
		{
			//ENTER_CRITICAL_SECTION
			cqueue_disable(q);
			//{
			if(q->front == q->max-1)
				q->front = 0;
			else
				q->front++;
			*data = q->data[q->front];
			//}
			cqueue_enable(q);
			//EXIT_CRITICAL_SECTION
			return CQ_STATUS_SUCCESS;
		}
		return CQ_STATUS_ERROR_QUEUE_EMPTY;
	}
	return CQ_STATUS_ERROR_QUEUE_NOTENABLED;
}
///Function to Copy the Data inside the Queue to another buffer
/// loc - Array where the queue Data needs to be copied
/// copysz - Size copied into the Destination
/// locsz - Total locations in the queue Array to be transfered
uint8_t cqueue_copydata(cqueue_t *q,
	uint8_t *loc,uint16_t *copysz,uint16_t locsz)
{
	uint16_t count,i;	
	if(cqueue_empty(q)==CQ_STATUS_SUCCESS)
	{
		return CQ_STATUS_ERROR_QUEUE_EMPTY;
	}
	//ENTER_CRITICAL_SECTION
	cqueue_disable(q);
	//{
	count = q->front;
	i=0;
	do
	{
		if(count == q->max -1)
			count=0;
		else
			count++;
		loc[i++]=q->data[count];
	} while((count != q->rear)&&(i<locsz));
	*copysz = i;
	//}
	cqueue_enable(q);
	//EXIT_CRITICAL_SECTION
	return CQ_STATUS_SUCCESS;	
}
///Function to Move the Data from Queue to another buffer
/// loc - Array where the queue Data needs to be moved
/// movesz - Size copied into the Destination
/// locsz - Total locations in the queue Array to be transfered
uint8_t cqueue_movedata(cqueue_t *q,
	uint8_t *loc,uint16_t *movesz,uint16_t locsz)
{
	uint16_t i;	
	if(cqueue_empty(q)==CQ_STATUS_SUCCESS)
	{
		return CQ_STATUS_ERROR_QUEUE_EMPTY;
	}
	//ENTER_CRITICAL_SECTION
	cqueue_disable(q);
	//{
	i=0;
	do
	{
		if(q->front == q->max-1)
			q->front = 0;
		else
			q->front++;
		loc[i++]=q->data[q->front];
	} while((cqueue_empty(q)!=CQ_STATUS_SUCCESS)&&(i<locsz));
	*movesz=i;
	//}
	cqueue_enable(q);
	//EXIT_CRITICAL_SECTION
	return CQ_STATUS_SUCCESS;	
}
///Function to Move the Data Into Queue from another buffer
/// loc - Array where the queue Data needs to be copied from
/// movesz - Size copied into the Queue
/// locsz - Total size to be copied into the queue
uint8_t cqueue_movetoqueue(cqueue_t *q,
	uint8_t *loc,uint16_t *movesz,uint16_t locsz)
{
	uint16_t i;		
	//ENTER_CRITICAL_SECTION
	cqueue_disable(q);
	//{
	i=0;
	do
	{
		if(q->rear == q->max-1)
			q->rear = 0;
		else
			q->rear++;
			
		if(cqueue_full(q)==CQ_STATUS_SUCCESS)//Check if Queue is Full
		{
			if(q->rear == 0)
				q->rear = q->max-1;
			else
				q->rear--;
			*movesz=i;
			//}
			cqueue_enable(q);
			//EXIT_CRITICAL_SECTION
			return CQ_STATUS_ERROR_QUEUE_FULL;
		}
		q->data[q->rear] = loc[i++];
	} while((i<locsz));
	*movesz=i;
	//}
	cqueue_enable(q);
	//EXIT_CRITICAL_SECTION
	return CQ_STATUS_SUCCESS;	
}
/*-----------------------------------------------------------*/ 
