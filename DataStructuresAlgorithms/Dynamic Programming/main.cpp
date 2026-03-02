/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 05/2025                           *
 * PURPOSE: driver file for project 4      *
 *******************************************/

#include <string>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//Function "solve" takes a vector of 9-90 unsigned long ints representing the digits input as the score by the user, an int representing the number of innings left to solve for, and another int representing the number of digits not yet accounted for an outputs a vector of 9 unsigned long ints representing the combination of the digits provided which creates the highest total sum.
std::vector<unsigned long> solve(std::vector<unsigned long> list,int numInn,int numDig){
  std::vector<unsigned long> best; //stores the current best combination of ints
  std::vector<unsigned long> temp;//stores the working combination of ints
  static std::vector<unsigned long> array[9][90];//an array of the best outcomes already calculated by number of innings remaining, and number of digits remaining.
  int maxLen=min((numDig-numInn)+1,10);//the maximum number of digits that can be in the current integer
  int minLen=max(1, numDig-((numInn-1)*10));//the minimum number of digits that can be in the current integer
  int skip=list.size()-numDig;//the index at which the remaining digits to look at begin
  unsigned long val=0;//a working total for the current number
  unsigned long bestVal=0;//the current highest total
  
  for(int i=0;i<minLen;i++){//calculate the value of the current number using the minumum number of digits
      val+=list[i+skip]*pow(10,minLen-i-1);
  }
  best.insert(best.begin(),val);//this is the first number in the current best
  if(numInn>1){//if there is more than one inning remaining, we must solve the rest of the digits using recursion
    if(array[numInn-1][numDig-minLen].empty()){
      array[numInn-1][numDig-minLen]=solve(list,numInn-1,numDig-minLen);
    }
    for (unsigned long i : array[numInn-1][numDig-minLen]){
      best.push_back(i);
    }
    bestVal = 0;
    for (unsigned long i : best){
      bestVal+=i;
    }
  }else{//if this is the last inning, this is the only possible outcome so it should be returned
    return best;
  }
  
  
  for (int i=skip+minLen; i<=skip+maxLen; i++){//here, i represents the index of the first digit of the next subproblem
    val=0;
    temp.clear();
    for(int j=skip; j<i; j++){//runs through all of the digits which are a part of the curent number and makes them into an int
      val+=list[j] * std::pow(10,i-j-1);
    }
    if(array[numInn-1][list.size()-i].empty()){//solve for the remaining digits if you havent already
     array[numInn-1][list.size()-i] =solve(list,numInn-1,list.size()-i);
    }
    for (unsigned long j : array[numInn-1][list.size()-i]){
      temp.push_back(j);
    }
    temp.insert(temp.begin(),val);
    val=0;
    for(unsigned long j : temp){
      val+=j;
    }
    if(val>bestVal){//if the total using the current number of digits is better than the previous best, it is the new best
      bestVal=val;
      best.clear();
      for (unsigned long j : temp){
	best.push_back(j);
      }
    }
  }
  return best;
}


int main(){
  cout<<"enter a string of 9-90 digits with no spaces: ";
  string strDigits;
  cin>>strDigits;
  std::vector<unsigned long> digits;
  std::vector<unsigned long> scores;
  char holder;
  unsigned long total=0;
  for(unsigned long i=0;i<strDigits.length();i++){
    holder=strDigits[i];
    digits.push_back(atoi(&holder));
  }
  scores=solve(digits,9,digits.size());
  cout<<endl<<"Linescore: ";
  for(unsigned long i : scores){
    cout<<i<<" ";
    total+=i;
  }
  cout<<endl<<"Total score: "<<total<<endl;
}
