//    FILE: NNSet.cpp
//  AUTHOR: Sam Disbrow
//    DATE: 9/2025
// PURPOSE: implementation of NNSet for Project 1
#include "NNSet.hpp"

#include <iostream>

using namespace std;


//Default constructor for NNSet, creates an empty NNset with max value of 4000000000
//in: none
//out: none
NNSet::NNSet()
{
  max = DEFAULT_MAX;
  set = new unsigned int[(DEFAULT_MAX/32)+1];//adding one to inculde 0 and max. basically rounds up if theres a remainder, and adds a whole extra slot if not which is necessary to ensure 0 and max are included
}

//max value constructor for NNSet, makes an empty set with amax value of biggest Element Possible
//in: unsigned int biggestElementPossible
//out: none
NNSet::NNSet(unsigned int biggestElementPossible)
{
  max = biggestElementPossible;
  set = new unsigned int[(max/32)+1];
}
//Copy constructor for NNSet
//in: NNset other (set to copy)
//out: none
NNSet::NNSet(const NNSet &other)
{
  max=other.max;
  set = new unsigned int[max/32+1];
  for (unsigned int i=0;i<=other.max/32;i++){//copy each unsigned int in the unsigned int array representing the sset
    set[i]=other.set[i];
  }
}

//= operator
//in: NNSet rhs (set to copy)
//out: NNset which is a copy (by value) of rhs
NNSet& NNSet::operator=(const NNSet& rhs)
{
  this->max=rhs.max;
  set = new unsigned int[this->max/32+1];
  for (unsigned int i=0;i<=rhs.max/32;i++){//copy each unsigned int in the array
    set[i]=rhs.set[i];
  }
  return *this;
}

//adds a value to the set
//in: unsiged int newElement (value to add)
//out: a bool representing if the value  was already present in the set
bool NNSet::add(unsigned int newElement)
{
  unsigned int arrLoc = newElement/32;
  unsigned int bitLoc = newElement%32;
  unsigned int mask=1;
  bool result;
  mask = mask << bitLoc;
  result = (this->set[arrLoc] & mask) >> bitLoc;
  this->set[arrLoc] = this->set[arrLoc] | mask;

  return !result;
}


//checks if a given value is in the set
//in: unsigned int lookup Element (value to check for)
//out: bool representing if the value was present
bool NNSet::contains(unsigned int lookupElement) const
{
  
  unsigned int arrLoc = lookupElement/32;
  unsigned int bitLoc = lookupElement%32;
  unsigned int mask=1;
  bool result;
  mask = mask << bitLoc;
  result = (set[arrLoc] & mask) >> bitLoc;
  return result;
}

//checks how many elements are in the given set
//in: none
//out: an unsigned int representing the number of elements in the set
unsigned int NNSet::cardinality() const
{
  unsigned int mask;
  unsigned int count =0;
  for(unsigned int i=0;i<=(this->max/32+1);i++){
    mask = 1<<(31);
     while (mask)
     { 
       if (mask & this->set[i]){
	 count ++;
       }
       
       mask = mask >> 1; 
     }
    
  }
  return count;
}

//overload + operator to return a new set with every value in either set given
//in:set to add
//out: a new set which is the union of the sets given
NNSet NNSet::operator+(const NNSet &otherSet) const
{
  unsigned int maxVal=this->max;
  if(otherSet.max>maxVal){
    maxVal=otherSet.max;
  }
  NNSet newSet(maxVal);
  for (unsigned int i=0;i<maxVal/32+1;i++){
    newSet.set[i]=this->set[i] | otherSet.set[i];
  }
  return newSet;
}

//Overloads - operator to return all items present in the left set, and not present in the right set
//in NNSets to subtract
//out difference between two sets
NNSet NNSet::operator-(const NNSet &rhsSet) const
{
  unsigned int maxVal=this->max;
  NNSet newSet(maxVal);
  unsigned int mask = 1 << 31;
  for (unsigned int i=0;i<maxVal/32+1;i++){
    newSet.set[i]=0;
    mask = 1<<31;
    while (mask)
    { 
      if ((mask & this->set[i])&& !(mask & rhsSet.set[i])){
        newSet.set[i]=newSet.set[i]|mask;
      }
      mask = mask >> 1;
    }
  }
  return newSet;
}

//overloads ! operator to return all items not present in the given set
//in:set to compliment
//out:complimented set
NNSet NNSet::operator!() const
{
  unsigned int maxVal=this->max;
  unsigned int extraVal=(32-this->max%32)-1;
  NNSet newSet(maxVal);
  for (unsigned int i=0;i<maxVal/32+1;i++){
    newSet.set[i]=~this->set[i];
  }
  unsigned int mask=-1;
  mask=mask>>extraVal;
  newSet.set[maxVal/32]=newSet.set[maxVal/32]&mask;
  return newSet;
}

//in:none
//out: bool representing if the set is empty
bool NNSet::isEmpty() const
{
  for (unsigned int i=0;i<this->max/32+1;i++){
    if(this->set[i]){
      return false;
    }
  }
  return true;
}

//checks if two sets contain the same values
//out bool representing if the two sets contain the same values
bool NNSet::operator==(const NNSet &rhs) const
{
  for (unsigned int i=0;i<this->max/32+1;i++){
    if(this->set[i]!=rhs.set[i]){
      return false;
    }
    cout<<i<<endl;
  }
  return true;
}

//clears the set
void NNSet::clear()
{
  for (unsigned int i=0;i<this->max/32+1;i++){
    this->set[i]=0;
  }
}

//overloads the << operator to print the numbers present in a set in brackets and with commas between
std::ostream& operator<< (std::ostream &os, const NNSet &nns)
{
  unsigned int mask;
  os<<"{ ";
  bool first=true;
  unsigned int pos;
  for (unsigned int i=0;i<nns.max/32+1;i++){
    mask = 1;
    pos=0;
    while (pos<32&&(i<nns.max/32||pos<=nns.max%32)){
      if (mask & nns.set[i]){
	if (!first)
	  os<<", ";
	else
	  first=false;
	os << pos+i*32;
      }
      mask = mask << 1;
      pos++;
    }   
  }
  os<<" }";
  return os;
 }

//returns the intersection of two sets
NNSet NNSet::operator/(const NNSet &otherSet) const
{
  unsigned int maxVal=this->max;
  if(otherSet.max>maxVal){
    maxVal=otherSet.max;
  }
  NNSet newSet(maxVal);
  for (unsigned int i=0;i<maxVal/32+1;i++){
    newSet.set[i]=this->set[i] & otherSet.set[i];
  }
  return newSet;
}

