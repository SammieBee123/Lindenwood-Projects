/*******************************************
 * File: AVLTreeNode.cpp                   *
 * Author: S. Blythe & Sam Disbrow         *
 * Date: 03/2025                           *
 * PURPOSE: AVL tree node implementation   *
 *******************************************/

#include "AVLTreeNode.hpp"

int
AVLTreeNode::depth() const
{
    int numAncestors=0;
    AVLTreeNode *parentPtr = _parent;

    while(parentPtr!=nullptr)
    {
        numAncestors++;
        parentPtr = parentPtr->parent();
    }

    return numAncestors;
}

std::ostream&
AVLTreeNode::print(std::ostream &toStream) const
{
  toStream << _data.name();

    return toStream;
}

