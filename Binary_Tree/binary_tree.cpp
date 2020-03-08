/** ***************************************************************************
 * @file binary_tree.cpp static memory binary tree structure
 * @author Douglas Hiranaka
 * @date   March, 2020
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
 * @brief Basic static memory binary tree class containing nodes of class 
 *        BinTreeNode. BinTree contains a pointer to a root node 'root' and 
 *        methods to set and get the root node. Each BinTreeNode contains 
 *        a pointer to its parent and left and right branches, and a 'data'
 *        payload. 
 * @version 
 * 03.04.120 intial DKH
 *****************************************************************************/

#pragma once // like typedef protection to only include header once

#include "Binary_tree.h"
#include <stdlib.h>

/** ****************************************************************************
 * @name:  BinTree 
 * @brief default constructor
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
BinTree::BinTree(){
  root = BtreeNodes::getInstance()->getNode();
}

/** ****************************************************************************
 * @name:  BinTree 
 * @brief load root constructor
 * @param [in] root value to load into the root node 
 * @retval N/A
 ******************************************************************************/
BinTree::BinTree(int rootVal){
  root = BtreeNodes::getInstance()->getNode();
  root->data = rootVal;
}

/** ****************************************************************************
 * @name:  ~BinTree 
 * @brief default destructor - clean up root node
 * @param [in]  
 * @retval N/A
 ******************************************************************************/
BinTree::~BinTree(){
  BtreeNodes::getInstance()->releaseNode(root);
}

/** ****************************************************************************
 * @name:  enter_data 
 * @brief standard method to ener data into a node
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
void BinTree::enter_data(BinTreeNode *&new_node, 
                        const int& payload)
{
  // see if we have reached the end
  if (new_node == NULL) {
    new_node = BtreeNodes::getInstance()->getNode();
  }

  if (new_node->data == payload)
    return;

  if (new_node->data < payload)
    enter_data(new_node->right, payload);
  else
    enter_data(new_node->left, payload);
} // end of enter_one()

/** ****************************************************************************
 * @name:  traverse 
 * @brief standard depth first traversal returning a weight (sum) of all the
 *        payload values
 * @param [in] index 
 * @retval N/A
 ******************************************************************************/
int BinTree::traverse(BinTreeNode* node)
{
  static int total = 0;
  if (node != NULL) {
    if (node->left != NULL)
      traverse(node->left);

    if (node->right != NULL)
      traverse(node->right);

    // only adds on the way out
    total += node->data;
  } else {
    return 0;
  }
  return total;
}