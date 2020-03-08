/** ***************************************************************************
 * @file binary_tree.h static memory binary tree structure
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
#pragma once


struct BinTreeNode {
  int index;
  int data;
  BinTreeNode *left;
  BinTreeNode *right;
  BinTreeNode *parent;
};

#include "btree_nodes.h"

class BinTree
{
public:

  BinTree();
  BinTree(int rootVal);
  ~BinTree();

  // Set and get root node
  void setRoot(BinTreeNode* node){ root = node; };
  BinTreeNode* getRoot(){ return root; };

  void enter_data(BinTreeNode *&new_node, const int& payload);
  int  traverse(BinTreeNode* node);

private:
  BinTreeNode* root;
};


