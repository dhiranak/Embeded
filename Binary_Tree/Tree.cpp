// Tree.cpp : Defines the ENTRY POINT for the console application.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "binary_tree.h"
#include "btree_nodes.h"

using namespace std;

// sandbox version with prints to show the traversal
int testTraverse(BinTreeNode* node)
{
  static int total = 0;
  if (node != NULL) {
    cout << "Node data = " << node->data << endl;
    cout << "Trying left " << node->index << endl;

    if (node->left != NULL)
      testTraverse(node->left);
    cout << "Left weight = " << total << "\n";

    cout << "Trying right\n";
    if (node->right != NULL)
      testTraverse(node->right);
    cout << "Right weight = " << total << "\n";

    cout << "data = " << node->data << "\n";
    // only adds on the way out
    total += node->data;
  } else {
    cout << "found NULL\n";
    return 0;
  }
  return total;
}
//     20
//  10   30
//  5   15
// 3 7   17
int _tmain(int argc, _TCHAR* argv[])
{
  unitTestBtreeNodes(); // test the queue class

  BtreeNodes::getInstance()->queueInit();

  BinTree* tree = new BinTree(20);

  BinTreeNode* twoLeftNode        = BtreeNodes::getInstance()->getNode(); // 10
  BinTreeNode* twoRightNode       = BtreeNodes::getInstance()->getNode(); // 30
  BinTreeNode* threeLeftNode      = BtreeNodes::getInstance()->getNode(); // 5
  BinTreeNode* threeRightNode     = BtreeNodes::getInstance()->getNode(); // 15
  BinTreeNode* fourLeftNode       = BtreeNodes::getInstance()->getNode(); // 3
  BinTreeNode* fourRightNode      = BtreeNodes::getInstance()->getNode(); // 7
  BinTreeNode* fourRightRightNode = BtreeNodes::getInstance()->getNode(); // 17

  cout << "Starting Tree\n";
  // load the data in the nodes.
  twoLeftNode->data   = 10; twoRightNode->data   = 30;
  threeLeftNode->data = 5;  threeRightNode->data = 15;
  fourLeftNode->data  = 3;  fourRightNode->data  = 7; fourRightRightNode->data = 17;

  // connect everything together
  cout << "top node = " << tree->getRoot()->data << "\n";
  tree->getRoot()->left = twoLeftNode;
  tree->getRoot()->right = twoRightNode;

  twoLeftNode->left = threeLeftNode;
  twoLeftNode->right = threeRightNode;

  twoLeftNode->parent = tree->getRoot();
  twoRightNode->parent = tree->getRoot();

  threeLeftNode->left = fourLeftNode; 
  threeLeftNode->right = fourRightNode; 
  threeRightNode->right = fourRightRightNode; 

  threeLeftNode->parent = twoLeftNode; 
  threeRightNode->parent = twoLeftNode; 

  fourLeftNode->parent = threeLeftNode;
  fourRightNode->parent = threeLeftNode;
  fourRightRightNode->parent = threeRightNode;

  cout << "The testTraverse() weight is: " << testTraverse(tree->getRoot()) << "\n";
  cout << "The tree->traverse() weight is: " << tree->traverse(tree->getRoot()) << "\n";
  cout << "middle node = " << threeRightNode->data << "\n";
	return 0;
}

