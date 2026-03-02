#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <vector>
#include <cmath>

class score{
private:
  std::vector<int> _digits;
  std::vector<int> _scores;
  int _total;
public:
  
  score(std::vector<int>& digits, std::vector<int>& scores):_digits(digits), _scores(scores), _total(0){}
  
  std::vector<int> digits() const {return _digits;}
  std::vector<int>& digits() {return _digits;}

  std::vector<int> scores() const {return _scores;}
  std::vector<int>& scores() {return _scores;}

  int total() const {return _total;}
  int& total() {return _total;}

  void bestScore();

  
};
 #endif
