/** ***************************************************************************
 * @file list.h static memory linked list 
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
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdlib.h>

#define LIST_SIZE 5 ///< This can be any size

/// linked list data structure 
typedef struct ListNode_ {
    void             *data;
    struct ListNode_ *next;
    int              index;
} ListNode;

typedef struct List_ {
    int      currentSize;
    ListNode *head;
    ListNode *tail;
} List;

void listInit(List *list);
void listDestroy(List *list);
int  listInsNext(List *list, ListNode *node, const void *data);
int  listRemNext(List *list, ListNode *node, void **data);
ListNode* listIterateToNode(List *list, ListNode *node, void **data, unsigned int index);
ListNode* listIterateToPayload(ListNode *pNode,void **pData);

#define listSize(list) ((list)->currentSize)
#define listHead(list) ((list)->head)
#define listTail(list) ((list)->tail)

#define listIsHead(list, node) (node == (list)->head ? 1 : 0)
#define listIsTail(node) ((node)->next == NULL ? 1 : 0)

#define listData(node) ((node)->data)
#define listNext(node) ((node)->next)

void unitTestLinkedList(void);

#endif /* _LINKED_LIST_H */