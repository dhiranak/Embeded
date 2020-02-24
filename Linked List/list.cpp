/** ***************************************************************************
 * @file list.CPP static memory linked list 
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
 * @brief Static linked list to avoid dynamic allocation memory issues in an embedded
 *        system. Since the list is sized at compilation there should be no 
 *        issuse with overflow. The list is used to store things like tcp socket info 
 *        that gets allocated on connection and delalocated on disconnect or timeout.
 * @version 
 * 02.22.120 intial DKH
 *****************************************************************************/
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "static_queue.h"
#include "list.h"

ListNode listNodes[LIST_SIZE];
StaticQueue ndxQ;

/** ****************************************************************************
 * @name:  listInit 
 * @brief Start the list with a fake head
 * @param [in] pList pointer to the list info struct 
 * @param [in] destroy - pointer to a destructor function
 * @retval N/A
 ******************************************************************************/
void listInit(List *pList)
{
    pList->currentSize = 0;
    pList->head = NULL;
    pList->tail = NULL;
} // end of list_init()

/** ****************************************************************************
 * @name:  listNodeInit 
 * @brief set the indices in the node array
 * @param N/A
 * @retval N/A
 ******************************************************************************/
void listNodeInit()
{
  int i;
  for (i = 0; i < LIST_SIZE; ++i) {
    listNodes[i].index = i;
  }
}

/** ****************************************************************************
 * @name:  listDestroy 
 * @brief iterate through a list, remove nodes and deallocate memory
 * @param [in] pList pointer to the list info struct 
 * @retval N/A
 ******************************************************************************/
void listDestroy(List *pList)
{
    void *data;
    /// remove each element
    while(listSize(pList) > 0) {
        listRemNext(pList, pList->head, (void **)&data);
    }
} // end of listDestroy()

/** ****************************************************************************
 * @name:  listInsNext 
 * @brief Create and add a new node to the list after the input node and update 
 *        the info struct
 * @param [in] pList pointer to the list info struct 
 * @param [in] pNode pointer to a node
 * @param [in] pData pointer to the list info struct 
 * @retval N/A
 ******************************************************************************/
int listInsNext(List       *pList, 
                ListNode   *pNode, 
                const void *pData)
{
    ListNode *newNode;

    /// Allocate storage for the element, new_node = (ListNode *)malloc(sizeof(ListNode));
    newNode = &listNodes[dequeue(&ndxQ)];
    if ( newNode == NULL)
        return -1;
    /// Insert the element into the list
    newNode->data = (void*)pData;
    if (pNode == NULL) { /// start list
        // Handle insertion at the head of the list
        if (listSize(pList) == 0) {
            pList->tail = newNode;
            pList->head = newNode;
            newNode->next = NULL; ///< need to force NULL in this compiler
        } else { /// not at beginning
            return -1;
        }
    } else { /// handle insertion somewhere other than at the head
        if (pNode->next == NULL) { // insert a new TAIL element
            pList->tail->next = newNode; // current tail, point to new nodw
            pList->tail = newNode; // then change tail to the new node
            newNode->next = NULL;
        } else { /// insert the new element between the current one and the current next one
            newNode->next = pNode->next;
            pNode->next = newNode;
        }
    }
    /// adjust the size of the list to account for the inserted element
    ++pList->currentSize;
    return 0;
} // end of listInsNext()

/** ****************************************************************************
 * @name:  listRemNext 
 * @brief Removes the next node unless there is only one left then it removes 
 *        the current node.
 * @param [in] pList pointer to the list info struct 
 * @param [in] pNode pointer to a node
 * @param [in] pData pointer to the data that was in the node removed
 * @retval return 0 success, -1 fail
 ******************************************************************************/
int listRemNext(List     *pList, 
                ListNode *pNode, 
                void     **pData)
{
    ListNode *oldNode;

    /// No element passed in to remove
    if (listSize(pList) == 0)
        return -1;
    /// Remove the node from the list
    if (listSize(pList) == 1) { // at head
        oldNode = pNode;
        *pData = pList->head->data;
        pList->head = NULL;
        pList->tail = NULL;
    } else { /// removal from other than the head
        *pData = pNode->next->data;
        /// at least two elements, move the next pointer
        oldNode = pNode->next; /// point to the next element to remove
        if (listSize(pList) > 2) { /// more than 2 nodes
            pNode->next = pNode->next->next; /// move the nextpointer one further over the current next 
        } else {
            pNode->next = NULL; /// shrink the list one node
            pList->tail = pNode; /// manke tail same as head
        }
    }
    /// Free the storage allocated by the abstract datatype
    enqueue(&ndxQ, oldNode->index); // push free(old_node) the index back on the queue

    /// adjust the size of the list to account for the removed element
    --pList->currentSize;
    return 0;
} // end of listRemNext()

/** ****************************************************************************
 * @name:  listIterateToNode 
 * @brief Run through the list to the selected node return the data for 
 *        debugging to verify the node
 * @param [in] pList pointer to the list info struct 
 * @param [in] pNode pointer to a node to start from
 * @param [out] pData pointer to the data in the node found
 * @param [in] index of node to iterate to
 * @retval pointer to node found
 ******************************************************************************/
ListNode* listIterateToNode(List         *pList,
                            ListNode     *pNode,
                            void         **pData,
                            unsigned int index)
{
    static unsigned int nodeNumber;

    if (pList->head == pNode) { /// first time or head
        nodeNumber = 0;
    }
     if (nodeNumber != index) {
        nodeNumber++;
        return listIterateToNode(pList,
                                 pNode->next,
                                 pData,
                                 index);
     } else {
         *pData = pNode->data;
     }
    return pNode;
}

/** ****************************************************************************
 * @name:  listIterateToPayload 
 * @brief Run through the list until the input data matches the payload return 
 *        the pointer to the node matching the input payload 
 * @param [in] pNode pointer to a node to start from
 * @param [out] pData pointer to the data to match in the payload
 * @retval pointer to node found
 ******************************************************************************/
ListNode* listIterateToPayload(ListNode     *pNode,
                               void         **pData)
{
  if (pNode->next == NULL) {
    return NULL;
  }
  if (*pData != pNode->data) {
    return listIterateToPayload(pNode->next,
                                pData);
  }
  return pNode;
}

/** ****************************************************************************
 * @name:  listHasCycle 
 * @brief Run through the list until the end of the list or a cycle is found
 * @param [in] pSlowNode pointer incremented ONE node at a time
 * @param [in] pFastNode pointer incremented TWO nodes at a time
 * @retval pointer to node found or NULL
 ******************************************************************************/
ListNode* listHasCycle(ListNode   *pSlowNode,
                       ListNode   *pFastNode)
{
  if (pFastNode->next == NULL) {
    return NULL;
  }
  if (pSlowNode != pFastNode) {
    return listHasCycle(pSlowNode->next,
                        pFastNode->next->next);
  }
  return pSlowNode;
}

// ***************************** Test Linked List *****************************
// ***************************** Test Linked List *****************************
// ***************************** Test Linked List *****************************

void unitTestLinkedList()
{
    List   myList; // list information
    char   myStringData[] = "Some usless text";
    float  myFloatData;
    int    returnStatus;
    void   *returnData;
    float  floatArray[LIST_SIZE];
    unsigned int i; 
    ListNode *myNode; // pointer to a single node
    float *ptrFloatData;

    myFloatData = 3.14158f;

    printf("Entered linkedListTest()\n");
    listNodeInit();
    queueInit(&ndxQ); // preload - push the indies onto the queue
    listInit(&myList); 

    returnStatus = listInsNext(&myList, NULL, (void *)myStringData);
    printf("Head address: 0x%x\n", listHead(&myList) );
    printf("Tail address: 0x%x\n", listTail(&myList) );
    printf("Head data: %s\n", (char*)listData(myList.head)); 
    printf("List size: %d\n", myList.currentSize); 

    returnStatus = listInsNext(&myList, myList.head, (void *)(&myFloatData));
    printf("Head address: 0x%x\n", listHead(&myList) );
    printf("Head data: %s\n", (char*)listData(myList.head)); 
    printf("Tail address: 0x%x\n", myList.tail );
    printf("List size: %d\n", listSize(&myList) );
    printf("Tail data: %f\n", *(float*)listData(myList.tail) ); 

    printf("Is head : %d\n", listIsHead(&myList, myList.head) );
    printf("Is tail : %d\n", listIsTail(myList.tail) );
    // Should remove tail
    listRemNext(&myList, 
                myList.head, 
                &returnData);
    printf("returned Data: %f\n", *(float*)returnData );
    printf("head data: %s\n", (char*)myList.head->data );

    listRemNext(&myList, 
                myList.head, 
                &returnData);
    printf("returned Data: %f\n", *(float*)returnData );
    printf("head address: 0x%x\n", myList.head );
    // list should be empty after this

    // start a new list, 5 nodes with no cycle
    floatArray[0] = 0.0f; // payload array has 5 items
    returnStatus = listInsNext(&myList, myList.head, (void *)&floatArray[0]);
    for (i = 1; i < 5; i++ ) {
        floatArray[i] = (float)i;
        // this adds to the end of the list so the nodes data come out in descending order
        returnStatus = listInsNext(&myList, myList.tail, (void *)(&floatArray[i]));
    }
    printf("head data: %f\n", *(float*)myList.head->data );
    printf("tail data: %f\n", *(float*)myList.tail->data );

    printf("node[1] data: %f\n", *(float*)myList.head->next->data );
    printf("node[2] data: %f\n", *(float*)myList.head->next->next->data );
    printf("node[3] data: %f\n", *(float*)myList.head->next->next->next->data );
    printf("node[4] data: %f\n", *(float*)myList.head->next->next->next->next->data );

    myList.head->index = 0;
    myList.head->next->index = 1;
    myList.head->next->next->index = 2;
    myList.head->next->next->next->index = 3;
    myList.head->next->next->next->next->index = 4;


    // return the node found 
    myNode = listIterateToNode(&myList,
                               myList.head,
                               (void**)&ptrFloatData,
                               2); // node index to iterate to
    printf("node[2] data: %f\n", *(float*)myNode->data );
    printf("head data: %f\n", *(float*)myList.head->data );
    printf("tail data: %f\n", *(float*)myList.tail->data );

    *ptrFloatData = 3.0f;
    myNode = listIterateToPayload(myList.head,
                                  (void**)&ptrFloatData);

    printf("node[3] data: %f\n", *(float*)myNode->data );
    // myNode points to the node with the payload [3]
    *ptrFloatData = 0.0f;
    myNode = listIterateToPayload(myList.tail,
                                     (void**)&ptrFloatData);
    printf("My node address: 0x%x\n", myNode );

    ListNode* pSlowNode = myList.head;
    ListNode* pFastNode = myList.head->next->next;
    myNode = listHasCycle(pSlowNode, pFastNode);
    if (myNode == NULL) {
      printf("No cycle\n");
    }
    printf("My node address: 0x%x\n", myNode );
    // Create a cycle from node 5 to node 3
    myList.head->next->next->next->next =  myList.head->next->next;
    pSlowNode = myList.head;
    pFastNode = myList.head->next->next;
    myNode = listHasCycle(pSlowNode, pFastNode);
    if (myNode == NULL) {
      printf("No cycle\n");
    } else {
      printf("cycle found\n");
      printf("cycle index %d\n", myNode->index);
    }

    listDestroy(&myList);
    printf("Lists destroyed and cleaned up\nEnd linked list tests\n");
}
