//Red-black tree that supports insertion and printing out a visual of the tree.
#include <iostream>
#pragma once

struct Node{
  int value;
  Node* left, *right, *parent;
  bool black;
  Node(int newValue, bool newBlack = false) : left(0), right(0), parent(0){
    value = newValue;
    black = newBlack;
  }
  Node() : left(0), right(0), parent(0){//Sentinel node constructor
    value = 0;
    black = true;
  }
  bool isSentinel(){
  /*
   *Currently we don't deal with 0, i. e., we don't expect it in the input
   *(we only should be given integers 1-999). Therefore we may use a node's
   *0-value to identify it as sentinel; though we may also check whether
   *its left and right pointers are both null.
   */
    return left == 0 && right == 0;
  }
  bool isRed(){
    return !black;
  }
  void paintBlack(){
    black = true;
  }
  void paintRed(){
    black = false;
  }
  void makeSentinel(){
    deleteSubtrees();
    left = 0;
    right = 0;
    paintBlack();
    value = 0;
  }
  void addSentinelLeafs(){
    setLeft(new Node());
    setRight(new Node());
  }
  Node* grandparent(){
    return parent == 0 ? 0 : parent->parent;
  }
  Node* uncle(){
    Node* gp = grandparent();
    if(gp == 0){
      return 0;
    }
    return gp->left == parent ? gp->right : gp->left;
  }
  void setLeft(Node* node){
    left = node;
    if(node!=0){
      node->parent = this;
    }
  }
  void setRight(Node* node){
    right = node;
    if(node!=0){
      node->parent = this;
    }
  }
  bool isLeftChild(){
    //Parent shouldn't be null if calling this.
    return parent->left == this;
  }
  bool isRightChild(){
    return parent->right == this;
  }
  void deleteSubtrees(){
    if(left!=0){
      left->deleteSubtrees();
    }
    if(right!=0){
      right->deleteSubtrees();
    }
    delete left;
    delete right;
  }
  ~Node(){}
};

class RedBlackTree{
  public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(int num);
    bool isInTree(int num);
    bool remove(int num);
    bool isEmpty();
    void print();
  private:
    Node* root;
    Node* insertInitial(Node * node, int num);
    void preserveTreeProperties(Node * inserted);
    int getNumLevels(Node* root, int level);
    void populateArray(int *& array, int index, Node* node);
    Node* find(Node * node, int num);
    void removeSingleNode(Node* toRemove);
    void leftRotation(Node* formerChild);
    void rightRotation(Node* formerChild);
    Node** parentPtrTo(Node* child);
};