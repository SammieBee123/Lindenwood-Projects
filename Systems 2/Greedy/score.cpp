#include "score.hpp"
#include <iostream>

using namespace std;

void score::bestScore(){
  int size = this->_digits.size();
  int len;
  int temp;
  int best = 0;
  int besti;
  if(size<10){
    for(int i=0;i<size;i++){
      this->_scores.push_back(this->digits()[i]);
      cout<<this->_digits[i]<<endl;
      this->_total+=this->digits()[i];
    }
    return;
  }
  len=size-9;
  if(len>=10){
    len=10;
  }
  best=0;
  for(int i=0;i<size-len;i++){
    temp = 0;
    for(int j=0; j<=len; j++){
      temp+=(this->_digits[i+j] * pow(10,len-j));
    }
    if(temp>best){
      best=temp;
      besti=i;
    }
  }
  this->_scores.push_back(best);
  cout<<best<<endl;
  this->_digits.erase(this->_digits.begin() + besti, this->_digits.begin() + besti + len + 1);
  this->_total += best;
  this->bestScore();
}
