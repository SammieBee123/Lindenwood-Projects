/***************************************************************/
/*  FILE: freeList.hpp                                         */
/*  AUTHOR: Sam Disbrow                                        */
/*  DATE: 3/2025                                               */
/*  PURPOSE: header file for free list                         */
/***************************************************************/

#ifndef _FREE_LIST_HPP_
#define _FREE_LIST_HPP_

#include <list>
#include <string>

class freeList
{
public:
  struct data{
    std::string name;
    int size;
    int location;
    std::list<data>* refList;
  };
private:
  
  int _size;
  std::list<data> _list;
  std::list<data> _varList;

public:
  freeList(int size, std::list<data> list, std::list<data> varList);
  
  std::list<data> list() const {return _list;}
  std::list<data>& list() {return _list;}

  std::list<data> varList() const {return _varList;}
  std::list<data>& varList() {return _varList;}
    
  void freeMethod(std::string varName);
  void dump();
  void compress();
  void alloc(std::string varName, int amount,std::list <data>& refLis) ;
  void equate(std::string newVar, std::string existingVar);
  
};

#endif
