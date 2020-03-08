/** ***************************************************************************
 * @file btree_nodes.h static memory generic circular queue class
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
 *        issues with overflow. The queue is used in comm buffers and for 
 *        memory management for statically defined algorithms.
 * @version 
 * 02.17.120 intial DKH
 *****************************************************************************/
#ifndef _BTREE_NODES_H
#define _BTREE_NODES_H

#include <stdint.h>
#include "binary_tree.h"

#define UNIT_TEST 1
#define QUEUE_SIZE 8 // small number for test


/** ****************************************************************************
 * @name: CircQueue 
 * @brief Singleton circular queue class to only allow one manager of memory for
 *        a circular queue of pointers to a static array of data structures
 ******************************************************************************/
class BtreeNodes {
  public:
    // Singleton entry point for clients
	  static BtreeNodes* getInstance();
    void              queueInit();
    void              enqueue(int32_t index);
    int32_t           dequeue();
    BinTreeNode*      getNode();
    void              releaseNode(BinTreeNode* node);

  private:
    static BtreeNodes* inst_;     // the one, single instance
    BtreeNodes():SIZE(QUEUE_SIZE){}; // private constructor
	  BtreeNodes(const BtreeNodes&); // protection
    BtreeNodes& operator=(const BtreeNodes&);
    
    BinTreeNode node[QUEUE_SIZE]; // array of nodes structures being managed
    uint32_t    queue[QUEUE_SIZE]; // this is the circular buffer
    uint32_t    headIndex;
    uint32_t    tailIndex;
    const int   SIZE;
    bool        isFull;
    /// this is for debugging. The queue should never overwrite data since the size is
    /// the number of algorithm elements
    uint32_t    num_elements;
};

#if UNIT_TEST
void unitTestBtreeNodes();
#endif

#endif // btree_nodes.h