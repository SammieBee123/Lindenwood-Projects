/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 12/2025                           *
 * PURPOSE: driver file for project 3      *
 *******************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

struct edge;//forward declaration

struct airport{//airport consists of its name, the cost to get to it(from the user selected starting point), an "edge" pointing to the flight taken to get to the airport in the cheapest path, a list of edges that are the outgoing flights, and a bool isDone, which represents if it's been "checked off" on the current runthrough
  std::string name;
  int cost;
  edge* prev;
  std::list<edge*> edgesOut;
  bool isDone = false;
};
struct edge{//edge consits of the airport it leaves, where it arrives, and its cost.
  airport& airportOut;
  airport& airportIn;
  int cost;
  
};



void findCosts(std::list<airport>& airportList, airport& stAirport){//Takes a list of airports in the system and the airport from which to start and finds the cheapest path to each other airport using deijkstras algorithm, updating each airport's prev, cost, and isDone along the way
  edge* cheapestOut=stAirport.edgesOut.front();
  stAirport.isDone=true;//findCosts is only run on an airport which is done
  
  if(stAirport.cost==-1){//if this is the actual starting point, cost is 0
    stAirport.cost=0;
  }
  for (auto edge : stAirport.edgesOut){//check all outgoing flights
    if(edge->airportIn.cost==-1||edge->airportIn.prev->cost>edge->cost+stAirport.cost){//if the airport the edge leads to has -1(representing infinity) cost or more cost than taking the outgoing flight, update its best path to be via outgoing flight
      edge->airportIn.prev=edge;
      edge->airportIn.cost=stAirport.cost+edge->cost;
    }
    if(cheapestOut->cost>edge->cost&&!edge->airportIn.isDone){//if the edge costs less than the current one and is not done, it is now cheapestOut, which will become the cheapest outgoing edge which is not yet done and will be done next.
      cheapestOut=edge;
    }
  }
  
  if(cheapestOut->airportIn.isDone){//should happen only if all are done
    return;
  }
  
  findCosts(airportList, cheapestOut->airportIn);//recursion call
}


int main(){
  std::string fileName;//the user chosen filename
  int numAirports;//the number of airports in the system as read from the file
  std::list <airport> airportsList;//a list of all of the airports in the system read from the file
  std::string temp;//a temporary string, most often used to hold airport names before passing them into their respective airports, also holds the name of the starting airport
  std::string dest;//temporarily holds the name of the destination airport for each edge as well as overall
  int cost;//holds the cost of each edge temporarily
  int numFlights;//total number of flights(edges) in the system read from file
  int userChoice;//if the user chose menu option 1 or 2
  std::string prevStart;//the previous starting point (allows the algorithm not to be run over again if startingpoint remains the same)
  airport stAirport;//the airport version of the starting place
  airport tempAirport;//the destination for each edge and final
  std::list<edge> path;//the best cost path from start to dest
  cout<<"What is the name of your input file? ";//read input
  cin>>fileName;
  std::ifstream istream(fileName);
  if(!istream.is_open()){
    cerr<<"Error: could not open file."<<endl;
    return 1;
  }
  istream>>numAirports;//parse input. first line is numAirports
  for (int i=0;i<numAirports;i++){//Next numAirports lines are airport names
    istream>>temp;
    airportsList.push_back({temp, -1, nullptr, {}});
  }
  istream>>numFlights;//next line is numFlights
  for (int i=0;i<numFlights;i++){//next numFlights lines are outgoing, and incoming airports, and cost
    istream>>temp;
    istream>>dest;
    istream>>cost;
    
    for (auto& airport : airportsList){//find the outgoing and destination airports from their names
      
      if(airport.name==temp){
      	for (auto& toPorts : airportsList){
	  if(toPorts.name==dest){
	    airport.edgesOut.push_back(new edge{airport, toPorts, cost});//add the given edge values to the departing airport's edgesOut list
	  }
	}
	
      }
    }
  }
  cout<<"1) Find the chearpest flight between two airports"<<endl<<"2) Quit"<<endl;//user makes their choice
  cin>>userChoice;
  while(userChoice!=2){//so long as the user hasnt chosen 2
    path.clear();//start with a clear path
    cout<<"Please enter the starting airport: ";
    cin>>temp;
    cout<<"Please enter the destination airport: ";
    cin>>dest;//read starting and destination airports
    
    if(prevStart!=temp){//if the starting airport is the same as it was the last time it was run, this part is skipped and values are maintained, else reset airport values to default and runing findCosts on the starting airport
      for (auto& airport : airportsList){
	airport.cost=-1;
	airport.prev=nullptr;
	airport.isDone=false;
	if(airport.name==temp){
	  stAirport = airport;
	}
      }
      findCosts(airportsList, stAirport);
    }
    
    for (auto& airport : airportsList){//find the destination airport from it's name
      if(airport.name==dest){
	cout<<"The cost of the minimum flight is $"<<airport.cost<<endl;
	tempAirport=airport;
	while(tempAirport.name!=temp){//while the next airport to look at isnt the start, add the flight to the front of the path
	  path.push_front(*tempAirport.prev);
	  tempAirport=tempAirport.prev->airportOut;
	  cout<<tempAirport.name<<" "<<temp<<endl;
	}
	for (auto& edge : path){//print path
	  cout<<edge.airportOut.name<<" to "<<edge.airportIn.name<<" $ "<<edge.cost<<endl;
	}
      }
    }

    
    cout<<"1) Find the chearpest flight between two airports"<<endl<<"2) Quit"<<endl;//give option again
    cin>>userChoice;
  }
  for(airport myAirport : airportsList){//free memory
    
    for(edge* myEdge: myAirport.edgesOut){
      delete myEdge;
    }
  }
  return 0;
}
