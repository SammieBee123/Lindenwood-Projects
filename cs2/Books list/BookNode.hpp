#ifndef _BOOK_NODE_HPP
#define _NODE_HPP

#include <iostream>
#include <string>
#include "Book.hpp"
using namespace std;

class BookNode{
  private:
    Book *_data; //the book this node represents
    BookNode *_next; //pointer to the next node
    
  public:
    BookNode() : _data(nullptr), _next(nullptr) {}//default constructor
    BookNode(const Book &val) : _data(new Book(val)), _next(nullptr){}//constructor with book input
    //accessors
    Book*  data() const {return _data;}
    BookNode* next() const {return _next;}
   
    //modifiers
    Book* & data() {return _data;}
    BookNode* & next() {return _next;}
    
    ostream& print(ostream &os) const;
    
};

ostream& operator<<(ostream &os, const BookNode &n);
#endif
