# Binary Tree

### Static memory Binary Tree

Static memory version of a simple binary tree with an integer payload. A queue of indices to pointers of an array of nodes is used to manage the pool of nodes. A post order traversal is included with a summing of the "weight" of the tree. A singleton pattern is used to insure that only one pool of nodes is accessed using the nodes class. 