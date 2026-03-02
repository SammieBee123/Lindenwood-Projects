/***************************************************************/
/*  FILE: freeList.cpp                                         */
/*  AUTHOR: Sam Disbrow                                        */
/*  DATE: 4/2025                                               */
/*  PURPOSE: Implementation of data allocation methods         */
/***************************************************************/

#include "freeList.hpp"

#include <string>
#include <iostream>
bool compareByLoc(const freeList::data& a, const freeList::data& b){//a simple bool which takes two "data"s and returns true if the first is smaller.
  return a.location<b.location;
}
freeList::freeList(int size,std::list<freeList::data> list,  std::list<freeList::data> varList){//freeList constructor, and creates a "free" data to beign the freelist.
  this->_size=size;
  this->_list=list;
  this->_varList=varList;
  freeList::data free;
  free.size=size;
  free.location=0;
  this->list().push_front(free);
}
void freeList::freeMethod(std::string varName){//free's the var with the stated varName by removing it from the varList and adding it to the freelist.
  for(auto it = this->_varList.begin(); it!= this->_varList.end();it++){
    if(it->name==varName){
      this->_list.push_back(*it);
      this->_list.sort(compareByLoc);
      it=(*it).refList->erase(it);
    }
  }
}
int loc(int amount, std::list<freeList::data>& freeList){//finds the first location in freeList which will fit amount and returns it as an int
  for(auto it = freeList.begin(); it!= freeList.end();it++){
     if(it->size>=amount){
      if(it->size==amount){
	freeList.erase(it);
      }else{
	it->size-=amount;
	it->location+=amount;
      }
      return it->location-amount;
    }
  }
  throw std::runtime_error("not enough space!");
  return -1;
}
void freeList::alloc(std::string varName, int amount, std::list <freeList::data>& refList){//allocates a variable in freeList with size amount and name varName
  for(auto it = this->_varList.begin(); it!= this->_varList.end();it++){
    if((*it).name==varName){
      it=this->_varList.erase(it);
    }
  }
  
  freeList::data variable;
  variable.name=varName;
  variable.size=amount;
  variable.location=loc(amount, _list);
  refList.push_front(variable);
  variable.refList=&refList;
  std::cout<<variable.refList->size()<<std::endl;
  this->_varList.push_back(variable);
}
void freeList::dump(){//prints all free and var
  std::cout<<"variables: "<<std::endl;
  for(auto it = this->_varList.begin(); it!=this->_varList.end();it++){
    std::cout<<(*it).name<<":"<<(*it).location<<"("<<(*it).size<<") ["<<(*it).refList->size()<<"]"<<std::endl;
  }
  std::cout<<"free list: "<<std::endl;
  for(auto it = this->_list.begin(); it!=this->_list.end();it++){
  std::cout<<":"<<(*it).location<<"("<<(*it).size<<") ["<<0<<"]"<<std::endl;
  }
  std::cout<<std::endl<<"=============================="<<std::endl<<std::endl;
}
void freeList::compress(){//combines all adjoining free blocks
   for(auto it = this->_list.begin(); it!= this->_list.end();it++){
     while((*it).size+(*it).location==(*std::next(it)).location){
       (*it).size+=(*std::next(it)).size;
       std::next(it)=this->_list.erase(std::next(it));
     }
   }
}
void freeList::equate(std::string newVar, std::string existingVar){//sets a new var equal to a prior one
  freeList::data varNew;
  varNew.name=newVar;
  for(auto it = this->_varList.begin(); it!= this->_varList.end();it++){
    if((*it).name==existingVar){
      varNew.location=(*it).location;
      varNew.size=(*it).size;
      varNew.refList=(*it).refList;
      //(*it).refList->push_back(varNew);
      
    }
  }
  this->_varList.push_back(varNew);
}
