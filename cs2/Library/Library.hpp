#ifndef _LIBRARY_HPP_
#define _LIBRARY_HPP_

#include "Book.hpp"
//#include <iostream>
//#include <string>

class Library{
  private:
  Book* _books; 
  int _numBooks; //number of books in the library
  int _capacity; //number of books the library can currently hold
  
  public:
  
  //default constructor - an empty book array with space for 5 books
  Library():_books(new Book[5]),_numBooks(0),_capacity(5){};
  
  //a constructor to copy a library to a new library with double the size
  Library(const Library& old);
  
  //Library constructor from input stream
  Library(std::istream &is);
  
    //returns the number of different books in the library
  int size()const{return _numBooks;}

  //returns the number of empty slots in the library
  int emptySlots()const{return _capacity-_numBooks;}
  
  //returns the book in a given index of the _books array
  Book locateBook(int index)const{return _books[index];}
    
    //makes it APPEAR as though there are no books in the library
  void clear(){_numBooks=0;}
  
  //doubles the size of the array when out of space
  Library bigLibr(const Library& old);
  
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
