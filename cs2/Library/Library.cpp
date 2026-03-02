#include "Library.hpp"
#include "Book.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Library constructor from input stream checked
Library::Library(std::istream &is){
  _capacity = 5;
  _numBooks = 0;
  _books = new Book[_capacity];
  is >> *this;
}
//a constructor to copy a library to a new library with double the size --checked
Library::Library(const Library& old){
  int size = old.size();
  _books=new Book[size*2];
  _numBooks=size;
  _capacity=size*2;
  for (int i=0;i<size;i++){
    _books[i]=old.locateBook(i);
  }
}
//doubles the size of the array when out of space - checked
Library Library::bigLibr(const Library& old){
  Library libr(old);
  return libr;
}
//Returns a pointer to the book if present, NULL if not - checked
Book* Library::find(const Book &b){
    for(int i=0;i<_numBooks;i++){
      if (_books[i] == b){
        return &_books[i];
      }
    }
    return NULL;
}
//Finds a book, adds one to the number of times its been checked out, and returns a pointer, NULL if no book present - checked
const Book* Library::checkOut(const Book &b){
  Book* checkedOut=find(b);
  if(checkedOut != NULL) {
    checkedOut->operator++();
  }
  return checkedOut;
}

//sets one library equal to another - checked
Library& Library::operator=(const Library &libr){
  clear();
  *this += libr;
  return *this;
}
//adds a book to the end of a library - checked asside from biglbr
Library& Library::operator+=(const Book &b){
if(find(b)==nullptr){
  if(emptySlots()<1){
    Library old = *this;
    Library newLibr (old);
    _books=old._books;
    _numBooks=old._numBooks;
    _capacity=old._capacity;
  }
  _books[_numBooks]=b;
  _numBooks++;
}
  return *this;
}

//adds one library to the end of the other, including copies - checked asside from biglbr
Library& Library::operator+=(const Library &libr){
int size = libr.size();
  for(int i=0;i<size;i++){ // while theres still more books
    if(emptySlots()<1){ // if theres no space, make space
        Library old = *this;
        Library newLibr (old);
        _books=old._books;
        _numBooks=old._numBooks;
        _capacity=old._capacity;
    } // ends if from ln 75
    if(find(libr.locateBook(i))==nullptr){//if it isn't a copy
    _books[_numBooks]=libr.locateBook(i);//add the book at the second libr's next slot to first lbrs opening
    _numBooks++;//increase numbooks and repeat
    }//ends if from 82
  }//ends for loop from ln 74
  return *this;
}//ends method
//Operator overloaded to remove a book -- checked
Library& Library::operator-=(const Book &b){
  int indexB = -1;
  int size = this->size();
  for (int i=0;i<size;i++){
    if (_books[i]==b){
      indexB=i;
      _numBooks--;
    }
  }
  if(indexB > -1){
  for (int i=indexB;i<size-1;i++){
    _books[i]=_books[i+1];
  }
  }
  return *this;
}
//Operator overloaded to add two libraries together -- checked
Library Library::operator+(const Library &libr){
int librSize = libr.size();

Library result = libr;
result += *this;
return result;
/*Library output;
  for(int i=0;i<librSize;i++){
      if(emptySlots()<1){
        Library old = output;
        Library newLibr (old);
        _books=old._books;
        _numBooks=old._numBooks;
        _capacity=old._capacity;
    }
  if(output.find(libr.locateBook(i))==nullptr){
    Book* bookPtr = output.find(libr.locateBook(i));
    output._books[_numBooks]=*bookPtr;
    output._numBooks++;
  }
  }
  int opSize = this->size();
  for(int i=0;i<opSize;i++){
      if(emptySlots()<1){
        Library old = output;
        Library newLibr (old);
        _books=old._books;
        _numBooks=old._numBooks;
        _capacity=old._capacity;
    }
  if(output.find(this->locateBook(i))==nullptr){
    Book* bookPtr = output.find(this->locateBook(i));
    output._books[_numBooks]=*bookPtr;
    output._numBooks++;
  }
  }
  return output;*/
}
//istream to take a library from input -- 
std::istream& Library::read(std::istream &is){
Book next;
is >> next;
  while (is){ 
    *this+=(next);
    is >> next;
  }
  return(is);
}

//osteam to output a library - checked
std::ostream& Library::print(std::ostream &os)const{
  for(int i=0;i<_numBooks;i++){
      os << _books[i] << endl;
  }
  return os;
}

//operator overloaded to function for library - checked
std::ostream& operator<<(std::ostream &os, Library const &libr){
  return libr.print(os);
}

//operator overloaded to function for library
std::istream& operator>>(std::istream &is, Library& libr){
  return libr.read(is);
}
