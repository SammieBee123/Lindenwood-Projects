/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 11/2025                           *
 * PURPOSE: driver file for project 2      *
 *******************************************/

#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]){
  int numGames;//An int representing the number of games chosen by the player through user input
  int numDoor;//An int representing the door number the player chooses (or 3 for random) assigned through user input
  int numPrize;//An int which stores the door number which holds the prize on each trial, assigned randomly each trial
  int numStay = 0;//An int representing the number of times Staying would win
  int numSwitch = 0;//An int representing the number of times switching would win
  cout<<"How many games would you like to simulate? ";
  cin>>numGames;//user input for number of games
  cout<<"What door would you like to start with? (0-2, 3 for random)? ";
  cin>>numDoor;//user input for player's chosen door
  cout<<"Simulation for "<<numGames<<" games, with ";
  if(numDoor==3){
    cout<<"random initial door"<<endl;
  }else{
    cout<<"player choosing door number "<< numDoor<<endl;
  }
  srand((unsigned int) time(nullptr));//seed rand
  int playerChoice = numDoor;//an int representing the door chosen each game, stays the same as numDoor unless 3 was chosen, in which case it's random every time
  for(int i=1;i<=numGames;i++){
    if(numDoor == 3){
      playerChoice=rand()%3;//If the player chose to randomize the door, choose a new random door for each game
    }
    numPrize=rand()%3;//randamize a new prize door for each game
    cout<<"Trial: "<<i<<", prize behind: "<<numPrize
	<<", player chose: "<<playerChoice<<" ... ";
    if(numPrize==playerChoice){//If the player's initial choice is the prize door, staying wins
      cout<<"STAY wins!"<<endl;
      numStay++;
    }else{//If the player's initial choice is not the prize door, it is one empty door, and the other empty door is revealed, leaving only the prize door for them to switch to, thus switching wins
      cout<<"SWITCH wins!"<<endl;
      numSwitch++;
    }
  }
  cout<<"By always staying, you would have won "<<(double)numStay/numGames*100<<"% of the time"<<endl<<//the number of times staying would win/the number of games gives the probability of staying winning, multiply by 100 for percentage.
    "By always switching, you would have won "<<(double)numSwitch/numGames*100<<"% of the time"<<endl;//the number of times switching would win/the number of games gives the probability of switching winning, multiply by 100 for percentage.
}
