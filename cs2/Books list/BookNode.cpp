#include "BookNode.hpp"
#include "Book.hpp"
#include <iostream>
#include <string>

ostream& BookNode::print(ostream &os) const{
  if(_data == nullptr){
  os << "There is nothing here!";
  }else{
  os << *_data;
  }
  return os;
}

ostream& operator<<(ostream &os, const BookNode &n){
  return n.print(os);
}
//BookNode& BookNode::operator=(const BookNode &libr){
  //BkNode.data()=data();
  //BkNode.next()=next();
//}


