#include "Library.hpp"
#include "Book.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Library constructor from IS
Library::Library(std::istream &is){
  _numBooks = 0;
  is >> *this;
}
//Returns a pointer to the book if present, NULL if not
Book* Library::find(const Book &b){
  if(this->size()>0){
    BookNode *last=_head;
    if(*(last->data()) == b){
      return last->data();
    }
    while(last->next()!=nullptr){
      last = last->next();
      if(*(last->data()) == b){
        return last->data();
      }
    }
  }
  return nullptr;
}
  
//Finds a book, adds one to the number of times its been checked out, and returns a pointer, NULL if no book present
const Book* Library::checkOut(const Book &b){
  if(find(b)!=nullptr){
    Book* checkedOut;
    if(this->size()>0){
      BookNode *last=_head;
      if(*(last->data()) == b){
        checkedOut = last->data();
      }
    while(last->next()!=nullptr){
      last = last->next();
      if(*(last->data()) == b){
        checkedOut = last->data();
      }
    }
  }
    ++ *checkedOut;
    return checkedOut;
  }else{
  return nullptr;
  }
}

  //operator overloading to set one library equal to another, add a book and whole library to a library, subtract a book from a library, and combine two libraries
Library& Library::operator=(const Library &libr){
  clear();
  *this += libr;
  return *this;
}
Library& Library::operator+=(const Book &b){
  if(find(b) == nullptr){
    BookNode* myNode = new BookNode(b);
    myNode->next()=_head;
    _head=myNode;
    _numBooks++;
    BookNode* last = _head;
    if(_numBooks==1){
      _head->next()=nullptr;
    }else{
      while (last->next() != nullptr){
        last=last->next();
      }
      last->next()=nullptr;
    }
  }
return *this;
}
Library& Library::operator+=(const Library &libr){
  BookNode* last = libr.head();
  while(last != nullptr){
    if(find(*(last->data()))==nullptr){
      *this+=*(last->data());
    }
    last=last->next();
  }
  return *this;
}
Library& Library::operator-=(const Book &b){
  if(find(b)!=nullptr){
    BookNode *last = _head;
    while(last != nullptr){
      if((*last->data()) == b){
        *last=*(last->next());
        _numBooks--;
        return *this;
      }
      last=last->next();
    }
  }
  return *this;
}
Library Library::operator+(const Library &libr){
  Library result = libr;
  result += *this;
  return result;
}
  
std::istream &Library::read(std::istream &is){
  Book next;
  is >> next;
  while (is){ 
    //cout << next << endl;
    (*this)+=next;
    is >> next;
  }
  return(is);
}
std::ostream &Library::print(std::ostream &os)const{
  if(_numBooks>0){
    BookNode *last = _head;
    os << *last << endl;
    while(last->next() != nullptr){
      last = last->next();
      os << *last << endl;
    }
  }else{
  os << "this library is empty! try adding some books to read!" << endl;
  }
  return os;
}

std::istream& operator>>(std::istream &is, Library& libr){
  return libr.read(is);
}

std::ostream& operator<<(std::ostream &os, const Library &libr){
  return libr.print(os);
}
