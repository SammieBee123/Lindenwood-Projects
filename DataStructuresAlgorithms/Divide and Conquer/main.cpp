/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 04/2025                           *
 * PURPOSE: driver file for project 3      *
 *******************************************/

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <cmath>
using namespace std;

struct person{
  string name;
  double one;
  double two;
};

struct locator{//intended to be the return type for the divide function, consists of two people and the distance of their score, which will be based upon which method is chosen. This allows for both people to be returned and easy access to their distance without having to recalculate
  person a;
  person b;
  double distance;
};
//two functions for use in sorting which each take two people as input, compare their "one" and "two" values respectively, and return true only if a's value is less than b.
bool compareByOne(const person& a, const person& b){
  return a.one<b.one;
}
bool compareByTwo(const person& a, const person& b){
  return a.two<b.two;
}
//function which finds the distance between two people using the formula for when "b" is chosen as the method of comparison. Takes two people, and returns their "distance" from one another
double bDist(person a, person b){
  double dist = 0;
  dist = sqrt((pow((a.one-b.one),2.0))+(pow((a.two-b.two),2.0)));
  return dist;
}
//the main recursive divide and concor method, takes an array of people, the number of people in the array, and the method by which to compare them and finds the closest pair. First it checks if there are only two items in the array(base case) in which case it returns the distance between the two. It then splits the array in half, and recursively runs divide on each half. If there are 3 items in the array, it will only divide the right half, and then compare the first item across the line(secondary base case). After this, it checks that there are no closer pairs across the line, if there are, that becomes the new closest pair.
locator divide(const person personArray[], int count,int type){
  locator closestClients;
  person* left = new person[500000];
  person* right = new person[500000];
  if(count==2){//only 2 items, base case 1, only needs to compare the two, no need for recursion
    closestClients.a=personArray[0];
    closestClients.b=personArray[1];
    if(type==1){
      closestClients.distance=personArray[1].one-personArray[0].one;
    }else if(type==2){
      closestClients.distance=personArray[1].two-personArray[0].two;
    }else if(type==3){
      closestClients.distance=bDist(personArray[1],personArray[0]);
    }
    return closestClients;
  }
  
  for(int i=0;i<count/2;i++){//create a left and right array on either side of the "line"
    left[i] = personArray[i];
    right[i]=personArray[i+count/2];
  }
  if(count%2==1){//if the number of people is uneven, the extra goes into right
    right[count/2]=personArray[count-1];
  }
  
  if(!(count/2<2)){//as long as neither half contains less than two people
    if(divide(left, count/2, type).distance<divide(right,count/2+count%2, type).distance){//if the result from the left side is closer, make the left side's result closestClient
	closestClients = divide(left, count/2, type);
    } else{//otherwise it should be the right side
	closestClients = divide(right, count/2+count%2, type);
      }
    //below, we need to compare across the line for each type... if the distance across the "line" is smaller than the current smallest, this becomes the new pair
    if(type==1&&right[0].one-left[count/2-1].one<closestClients.distance){
      closestClients.a=right[0];
      closestClients.b=left[count/2-1];
      closestClients.distance=right[0].one-left[count/2-1].one;
    }else if(type==2&&right[0].two-left[count/2-1].two<closestClients.distance){
      closestClients.a=right[0];
      closestClients.b=left[count/2-1];
      closestClients.distance=right[0].one-left[count/2-1].two;
    }else if(type==3){//for type 3(b), we need to be more careful, so we create a new array to hold the people that are close enough to the line to potentially be closer together than the current closest pair
	person* centerArray = new person[count];
	int centerCount=0;
	for(int i=0;i<count;i++){
	  if(right[0].one-closestClients.distance<personArray[i].one&&personArray[i].one<right[0].one+closestClients.distance){
	    centerArray[centerCount]=personArray[i];
	    centerCount++;
	  }
	}
	sort(centerArray,centerArray+centerCount-1,compareByTwo);//sort the array by two
	for(int i=0;i<count;i++){
	  for(int j=1; j<12;j++){//for each person within the array,check it's distance against each item up to 11 positions away, and if any pair is closer than the current closest, it becomes the new closest pair
	    if(i+j<centerCount&&bDist(centerArray[i+j],centerArray[i])<closestClients.distance){
		closestClients.a=centerArray[i];
		closestClients.b=centerArray[i+j];
		closestClients.distance=bDist(closestClients.b,closestClients.a);
	      }
	  }
	}
      }
  }
  else{//if splitting the array in half would lead to one side having less than two items, only the right side needs to be compared, the left will only have one item
    if(type==1){//set closest clients to the pair across the line
      closestClients.a=right[0];
      closestClients.b=left[0];
      closestClients.distance=right[0].one-left[0].one;
      if(divide(right, 2, type).distance<closestClients.distance){//then check if the pair on the right is better, if so, it is now closest.
	closestClients = divide(right, 2, type);
      }
    }else if(type==2){
      closestClients.a=right[0];
      closestClients.b=left[0];
      closestClients.distance=right[0].two-left[0].two;
      if(divide(right, 2, type).distance<closestClients.distance){
	closestClients = divide(right, 2, type);
      }
    }else if(type==3){
      closestClients.a=right[0];
      closestClients.b=left[0];
      closestClients.distance=bDist(right[0],left[0]);

      if(divide(right, 2, type).distance<closestClients.distance){
	closestClients = divide(right, 2, type);
      }
    }
  }
  delete[] left;
  delete[] right;
  return closestClients;
}
int main(int argc, char *argv[]){
  ifstream ifile(argv[1]);
  if(!ifile)
    {
      cerr << "ERROR: Could not open file:\"" << argv[1] << "\"" <<endl;
      return -1;
    }
  
  person* personArray = new person[1000000];
  int count=0;
  while(ifile){
    ifile>>personArray[count].name>>personArray[count].one>>personArray[count].two;
    count++;
  }
  count--;
  if(*argv[2]=='b'){
      cout<<divide(personArray, count,3).a.name<<", "<<divide(personArray, count,3).b.name<<", "<<divide(personArray,count,3).distance<<endl;
  }else if(stoi(argv[2])==1){
    sort(personArray, personArray + count, compareByOne);
    cout<<divide(personArray, count,stoi(argv[2])).a.name<<", "<<divide(personArray, count,stoi(argv[2])).b.name<<", "<<divide(personArray,count,stoi(argv[2])).distance<<endl;
  }else if(stoi(argv[2])==2){
    sort(personArray, personArray + count, compareByTwo);
    cout<<divide(personArray, count,stoi(argv[2])).a.name<<", "<<divide(personArray, count,stoi(argv[2])).b.name<<", "<<divide(personArray,count,stoi(argv[2])).distance<<endl;
  }
  delete[] personArray;  

}
