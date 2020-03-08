/** ***************************************************************************
 * @file btree_nodes.cpp 
 * @brief static memory circular queue manager of binary tree nodes
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
 * @brief circular queue of pointrs to an array of binary tree structure nodes
 *        to avoid dynamic allocation memory issues in an embedded system. 
 *        Since the queue is sized at compilation there should be no issuse 
 *        with overflow. A circular queue is used in comm buffers and for 
 *        memory management for statically defined algorithms.
 * @version 
 * 03.07.120 intial DKH
 *****************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "embedded.h"
#include "btree_nodes.h"

/**
  @brief This implementation to store indecies for a array of
         data structures. This queue is the basis for managing the static 
         memory resources to avoid fragmentation due to frequent allocation
         and delalocation of algorithm elements.
         The 
*/

using namespace std;

// Define the static singleton pointer
BtreeNodes* BtreeNodes::inst_ = NULL;

BtreeNodes* BtreeNodes::getInstance() { // singleton entry point
    if (inst_ == NULL) {              // only allow one copy to instanciate
        inst_ = new BtreeNodes();
    }
    return(inst_);
}

/** ****************************************************************************
 * @name:  queueInit 
 * @brief Start the queue with values same as the indicies 
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
void BtreeNodes::queueInit() {
  int i;

  tailIndex = 0;
  headIndex = 0;

  for(i = 0; i < SIZE; ++i) { 
      queue[i]       = i;

      node[i].data   = 0;
      node[i].index  = i;
      node[i].left   = NULL;
      node[i].right  = NULL;
      node[i].parent = NULL;
  }
  num_elements = SIZE;
  isFull    = true; // queue starts full
}

/** ****************************************************************************
 * @name: enqueue 
 * @brief PUSH data into the queue, index of a element dealloated
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
void BtreeNodes::enqueue(int32_t index) {

  queue[headIndex] = index;
  if ( (headIndex == tailIndex) && (isFull == true) ){
    tailIndex = (tailIndex + 1) % SIZE; // push tail pointer
  } else if ( (headIndex + 1) % SIZE == tailIndex) { // look ahead
    if (isFull == false) {
      isFull = true;
    } 
  }
  headIndex = (headIndex + 1) % SIZE;

  ++num_elements;
}

/** ****************************************************************************
 * @name: dequeue 
 * @brief POP data off the queue, allocate a element with the popped index
 * @param N/A
 * @retval poppedIndex - returned valid array index
 ******************************************************************************/
int32_t BtreeNodes::dequeue() {
  int32_t poppedIndex = 0;

  --num_elements;
  if (tailIndex == headIndex) {
    if (isFull == true) {
      isFull = false;
    } else {
      return EMPTY; // empty queue
    }
  } 
  poppedIndex = queue[tailIndex];
  queue[tailIndex] = 0; // don't really need to do this
  tailIndex = (tailIndex + 1) % QUEUE_SIZE;
  return poppedIndex;
}

/** ****************************************************************************
 * @name: getNode 
 * @brief allocates a binary tree node element off the object
 * @param N/A
 * @retval address of the allocated node 
 ******************************************************************************/
BinTreeNode* BtreeNodes::getNode()
{
  return &node[dequeue()];
}

/** ****************************************************************************
 * @name: releaseNode 
 * @brief delalocate a binary tree node element 
 * @param [in] node address of the released node 
 * @retval 
 ******************************************************************************/
void BtreeNodes::releaseNode(BinTreeNode* node)
{ // clear everything except the index
  node->data   = 0;
  node->left   = NULL;
  node->right  = NULL;
  node->parent = NULL;
  // push the index back on the queue
  enqueue(node->index);
}


// ************************* Test Static Queues *******************************
// ************************* Test Static Queues *******************************
// ************************* Test Static Queues *******************************
#if UNIT_TEST

void unitTestBtreeNodes()
{
  int32_t testValue;
  int i;
  BtreeNodes* nodes;
  nodes = nodes->getInstance();

  cout << "queueInit() test\n";
  nodes->queueInit();
  cout << "Test init using dequeue()\n";
  for (i = 0;i<5;++i){
    testValue = nodes->dequeue();
    cout << "testValue is " << testValue << "\n";
  }
  cout << endl;
  cout << "Call dequeue() on a empty queue\n";
  testValue = nodes->dequeue();
  if (testValue == EMPTY) 
    cout << "queue empty\n";

  cout << "Reset the queues with indecies matching the payload\n";
  nodes->queueInit();

  cout << "Add two more to roll the queue\n";
  nodes->enqueue(i);
  nodes->enqueue(i+1);

  cout << "Print the complete over written queue\n";
  for (i = 0;i<5;++i){
    testValue = nodes->dequeue();
    cout << "Value is " << testValue << endl;
  }
  cout << endl;

  cout << "Try remove two more values from the empty queue\n";
  testValue = nodes->dequeue();
  if (testValue == EMPTY) 
    cout << "queue empty\n";
  testValue = nodes->dequeue();
  if (testValue == EMPTY) 
    cout << "queue empty\n";

  printf("Load two new values 9, 8\n");
  nodes->enqueue(9);
  nodes->enqueue(8);

  printf("Pop the values and print them\n");
  testValue = nodes->dequeue();
  printf("Value is %d\n",testValue);
  testValue = nodes->dequeue();
  printf("Value is %d\n",testValue);
}

#endif // UNIT_TEST