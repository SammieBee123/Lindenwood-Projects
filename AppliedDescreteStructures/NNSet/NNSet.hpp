/*******************************************************/
/* FILE:NNSet.hpp                                      */
/* AUTHER: S. Blythe, Sam Disbrow                      */
/* DATE: 8/2025                                        */
/* PURPOSE: Header file for NNSet class for CSC28500   */
/*******************************************************/

#ifndef _NNSET_HPP_
#define _NNSET_HPP_

#include <iostream>

#define DEFAULT_MAX 4000000000

class NNSet
{
private:
  // you'll have to add items here. *think HARD* about what to add!
  unsigned int* set;
  unsigned int max;
public:
  NNSet();
  NNSet(unsigned int biggestElementPossible);
  NNSet(const NNSet &other);

  NNSet& operator=(const NNSet &rhs); 
  
  bool add(unsigned int newElement);
  bool contains(unsigned int lookupElement) const;

  unsigned int cardinality() const; 


  NNSet operator+(const NNSet &otherSet) const;
  NNSet operator-(const NNSet &rhsSet) const;
  NNSet operator!() const;

  bool isEmpty() const;
  bool operator==(const NNSet &rhs) const; 
  void clear();

  friend std::ostream& operator<< (std::ostream &os, const NNSet &nns);

  // The following is not required, but implementing it correctly will
  // earn you 3 bonus points. 
  NNSet operator/(const NNSet &otherSet) const;

  // you may wish to add some more private methods below, but you
  // do not have to do so
private:
};

#endif
