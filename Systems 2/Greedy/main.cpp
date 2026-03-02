#include "score.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main(){
  cout<<"enter a string of 9-9,999,999,999 digits with no spaces: ";
  string strDigits;
  cin>>strDigits;
  std::vector<int> digits;
  std::vector<int> scores;
  char holder;
  for(int i=0;i<static_cast<int>(strDigits.length());i++){
    holder=strDigits[i];
    digits.push_back(atoi(&holder));
  }
  score myScore(digits, scores);
  myScore.bestScore();
  cout<<"total score: "<<myScore.total()<<endl;
  cout<<"Linescore:";
  for (int i=0;i<static_cast<int>(myScore.scores().size());i++){
    cout<<" "<<myScore.scores()[i];
  }
}
