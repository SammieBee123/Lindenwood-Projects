/*******************************************
 * File: AVLTree.hpp                       *
 * Author: S. Blythe & Sam Disbrow         *
 * Date: 03/2025                           *
 * PURPOSE: AVL tree header file           *
 *******************************************/

#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

#include "AVLTreeNode.hpp"

#include <iostream>
#include <string>

class AVLTree
{
private:
  AVLTreeNode *_root;
  int _size;
public:
  //get and set methods for size and root
  int size() const {return _size;}
  int& size() {return _size;}
  AVLTreeNode* root() const {return _root; std::cout<<"no"<<std::endl;}
  
  AVLTree() : _root(nullptr), _size(0) {}
  int height();
  
  AVLTreeNode* find(std::string valToFind) const;
  void insert(Person newVal);
  void remove(std::string existingVal);

    std::ostream& print(std::ostream &os) const;
};

#endif
