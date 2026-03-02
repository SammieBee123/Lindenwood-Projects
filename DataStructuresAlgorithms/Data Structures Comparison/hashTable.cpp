/*******************************************
 * File: hashTable.cpp                     *
 * Author: Sam Disbrow                     *
 * Date: 03/2025                           *
 * PURPOSE: hashTable implementation       *
 *******************************************/

#include <iostream>
#include "hashTable.hpp"

using namespace std;

void
hashTable::insert(Person newVal){//takes a person as input, finds the correct spot in the hash table for them based on their name, and adds them to that list.
  int strVal=0;
  int index;
  int listSize;
  for(int i=0; i<(int)newVal.name().length(); i++){
    strVal +=  newVal.name()[i];
  }
  index = (strVal % this->hashSize());
  _array[index].push_back(newVal);
  listSize=this->list(index).size();
  _chain=max(this->chain(), listSize);
}

Person& hashTable::find(std::string valToFind)//takes a string as input, outputs the person who's name matches
{
  int strVal = 0;
  for(int i=0; i<(int)valToFind.length(); i++)
  {
    strVal +=  valToFind[i];
  }
  int index = strVal % this->hashSize();
  for(std::list<Person>::iterator it = _array[index].begin(); it != _array[index].end(); it++)
    {
      if ((*it).name() == valToFind)
	{
	  return *it;
	}
    }
  cerr<<"this person was not found!"<<endl;
  return *(new Person("0","0"));
}
