#ifndef _LIBRARY_HPP_
#define _LIBRARY_HPP_

#include "Book.hpp"
#include "BookNode.hpp"

class Library{
  private: 
  BookNode* _head; //the head of the linked list
  int _numBooks; //number of books in the library
  
  public:
  
  //default constructor - No books
  Library():_numBooks(0), _head(nullptr){};
  
  
  //Library constructor from input stream
  Library(std::istream &is);
  
    //returns the number of different books in the library
  int size()const{return _numBooks;}
  
  //returns the book in a given spot of the library
  //Book locateBook(int index)const;
  
  //returns _head
  BookNode* head()const {return _head;}
  
  //set _head
  BookNode* & head() {return _head;}
    
  //makes it APPEAR as though there are no books in the library
  void clear(){_numBooks=0;}
  
  BookNode locateBook(int i);
    //Returns a pointer to the book if present, NULL if not
  Book* find(const Book &b);

  //Finds a book, adds one to the number of times its been checked out, and returns a pointer, NULL if no book present
  const Book* checkOut(const Book &b);

  //operator overloading to set one library equal to another, add a book and whole library to a library, subtract a book from a library, and combine two libraries
  Library& operator=(const Library &libr);
  Library& operator+=(const Book &b);
  Library& operator+=(const Library &libr);
  Library& operator-=(const Book &b);
  Library operator+(const Library &libr);
  
  std::istream &read(std::istream &is);
  std::ostream &print(std::ostream &os)const;
};

std::istream& operator>>(std::istream &is, Library& libr);

std::ostream& operator<<(std::ostream &os, const Library &libr);


#endif
