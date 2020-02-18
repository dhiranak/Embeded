/** ***************************************************************************
 * @file static_queue.cpp static memory generic circular queue 
 * @author Douglas Hiranaka
 * @date   Februarry, 2020
 * @section LICENSE
 * @Copyright 2020 Douglas Hiranaka
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *
 * @brief circular queue to avoid dynamic allocation memory issues in an embedded
 *        system. Since the queue is sized at compilation there should be no 
 *        issuse with overflow. A circular queue is used in comm buffers and for 
 *        memory management for statically defined algorithms.
 * @version 
 * 02.17.120 intial DKH
 *****************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include "embedded.h"
#include "static_queue.h"

/**
  @brief This implementation to store indecies for a array of
         data structures. This queue is the basis for managing the static 
         memory resources to avoid fragmentation due to frequent allocation
         and delalocation of algorithm elements.
         The 
*/

uint32_t queue[QUEUE_SIZE] = {}; // this is the circular buffer
uint32_t headIndex = 0;
uint32_t tailIndex = 0;
/// this is for debugging. The queue should never overwrite data since the size is
/// the number of algorithm elements
uint32_t num_elements = 0;

StaticQueue tstQ;

/** ****************************************************************************
 * @name:  queueInit 
 * @brief Start the queue with values same as the indicies 
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
void queueInit() {
  int i;

  tstQ.ptrQueue  = queue;
  tstQ.size      = QUEUE_SIZE;
  tstQ.tailIndex = 0;
  tstQ.headIndex = 0;

  for(i = 0; i<QUEUE_SIZE; ++i) { 
      tstQ.ptrQueue[i] = i;
  }
    tstQ.isFull    = true; // queue starts full
}

/** ****************************************************************************
 * @name: enqueue 
 * @brief push data into the queue, index of a element dealloated
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
void enqueue(StaticQueue* pQueue, 
             int32_t      index) {

  pQueue->ptrQueue[pQueue->headIndex] = index;
  if ( (pQueue->headIndex == pQueue->tailIndex) && (pQueue->isFull == true) ){
    pQueue->tailIndex = (pQueue->tailIndex + 1) % pQueue->size; // push tail pointer
  } else if ( (pQueue->headIndex + 1) % pQueue->size == pQueue->tailIndex) { // look ahead
    if (pQueue->isFull == 0) {
      pQueue->isFull = true;
    } 
  }
  pQueue->headIndex = (pQueue->headIndex + 1) % pQueue->size;

  ++num_elements;
}

/** ****************************************************************************
 * @name: dequeue 
 * @brief pop data off the queue, allocate a element with the popped index
 * @param N/A
 * @retval poppedIndex - returned valid array index
 ******************************************************************************/
int32_t dequeue(StaticQueue* pQueue) {
  int32_t poppedIndex = 0;

  --num_elements;
  if (pQueue->tailIndex == pQueue->headIndex) {
    if (pQueue->isFull == true) {
      pQueue->isFull = false;
    } else {
      return EMPTY; // empty queue
    }
  } 
  poppedIndex = pQueue->ptrQueue[pQueue->tailIndex];
  pQueue->ptrQueue[pQueue->tailIndex] = 0; // don't really need to do this
  pQueue->tailIndex = (pQueue->tailIndex + 1) % QUEUE_SIZE;
  return poppedIndex;
}

// ************************* Test Static Queues *******************************
// ************************* Test Static Queues *******************************
// ************************* Test Static Queues *******************************
#if UNIT_TEST
void unitTestStaticQueue()
{
  int32_t testValue;
  int i;

  printf("queueInit() test\n");
  queueInit();
  printf("Test init using dequeue()\n");
  for (i = 0;i<5;++i){
    testValue = dequeue(&tstQ);
    printf("testValue is %d\n",testValue);
  }
  printf("\n");
  printf("Call dequeue() on a empty queue\n");
  testValue = dequeue(&tstQ);
  if (testValue == EMPTY) 
    printf("queue empty\n");
  printf("clear the test queue\n");
  for(i = 0; i<QUEUE_SIZE; ++i) { 
      tstQ.ptrQueue[i] = 0;
  }
  printf("Load the queues with indecies matching the payload\n");
  for (i = 0;i<5;++i){
    enqueue(&tstQ, i);
  }
  printf("Add two more to roll the queue\n");
  enqueue(&tstQ, i);
  enqueue(&tstQ, i+1);

  printf("Print the complete over written queue\n");
  for (i = 0;i<5;++i){
    testValue = dequeue(&tstQ);
    printf("Value is %d\n",testValue);
  }
  printf("\n");

  printf("Try remove two more values from the empty queue\n");
  testValue = dequeue(&tstQ);
  if (testValue == EMPTY) 
    printf("queue empty\n");
  testValue = dequeue(&tstQ);
  if (testValue == EMPTY) 
    printf("queue empty\n");

  printf("Load two new values 9, 8\n");
  enqueue(&tstQ, 9);
  enqueue(&tstQ, 8);

  printf("Pop the values and print them\n");
  testValue = dequeue(&tstQ);
  printf("Value is %d\n",testValue);
  testValue = dequeue(&tstQ);
  printf("Value is %d\n",testValue);
}

#endif // UNIT_TEST