/*******************************************
 * File: hashTable.hpp                     *
 * Author: Sam Disbrow                     *
 * Date: 03/2025                           *
 * PURPOSE: hashTable header file          *
 *******************************************/

#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_

#include "Person.hpp"

#include <string>
#include <list>
#include <algorithm>

class hashTable
{
private:
  
  int _size;
  std::list<Person> *_array;
  int _chain;
public:
  hashTable(): _size(0), _array(nullptr), _chain(0){} // constructors, one blank, one with the desired hash table size
  hashTable(int size): _size(size), _array(new std::list<Person>[size]), _chain(0){}

  std::list<Person> *array() const {return _array;}//array getter and setter
  std::list<Person> *array() {return _array;}
  
  std::list<Person>& list(int index) {return _array[index];}//list setter (takes an int and returns the list at that index)
  
  int hashSize() const {return _size;} //size getter and setter
  int& hashSize() {return _size;}
  
  void insert(Person newVal);
  
  Person& find(std::string valToFind);
  
  int chain() const {return _chain;}//chain getter and setter
  int& chain() {return _chain;}
};

#endif
