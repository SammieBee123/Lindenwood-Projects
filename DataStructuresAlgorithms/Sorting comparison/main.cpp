/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 01/2025                            *
 * PURPOSE: driver file for project 1      *
 *******************************************/

#include <iostream>
#include <fstream>
#include <list>

using namespace std;


string* bubble(string array[], int length){ // A function for bubble sort, taking input of a string array which represents the unsorted value, and length, the length of the array and outputs a string array which represents the sorted values
  std::string temp;
  bool swap = true;
  while(swap){ //keep going until you made it through without making any swaps
    swap=false; //you havent made any swaps this run - it just started
    for(int i=0; i<length-1; i++){ //itterate through the array
      if(array[i]>array[i+1]){ // if a value is larger than the one after it, swap them
      temp=array[i];
      array[i]=array[i+1];
      array[i+1]=temp;
      swap=true; // you made a swap, so make sure to repeat the while when youre done
    }
    }
  }
  return array;
}
string* merge(string S1[], string S2[], int length){//a function to merge two string arrays using the method used by mergesort
  string* array = new string[length]; //makes a new array which can hold both inputs
  int i=0;
  int j=0;
  int k=0;
  while(i<length/2 && j<length/2+length%2){//while neither array has reached it's end
    if(S1[i]<S2[j]){//if the first value of the first array, i, is smaller, adds it to the final array
      array[k]=S1[i];
      k++;
      i++;
    }
    else{
      array[k]=S2[j];//if the first value of the second array, j, is smaller, adds it to the final array
      k++;
      j++;
    }
  }
  while(i<length/2){//clears out i if it's not empty
    array[k]=S1[i];
    i++;
    k++;
  }
  while(j<length/2+length%2){//clears out j if its not empty
    array[k]=S2[j];
    k++;
    j++;
  }
  return array;
}

string* mergeSort(string array[], int length){//implements merge sort taking input of a string array, representing the unsorted array, and int representing the length of the array and outputs a sorted array
  if(length==1){ //if there's only one item in the array, it's sorted
    return array;
  }
  string* S1 = new string[length/2];//make an array for each half of the original array
  string* S2 = new string[length/2+length%2];

  for(int i=0;i<length/2;i++){//fill the arrays with their respective values
    S1[i]=array[i];
    S2[i]=array[i + length/2];
  }
  if(length%2==1){//if it's odd, S2 needs an extra value
    S2[length/2]=array[length-1];
  }
  S1 = mergeSort(S1, length/2); //do it all again for each half
  S2 = mergeSort(S2, length/2+length%2);
  return merge(S1,S2,length); //once you're done, you have to combine your smaller arrays into bigger ones and return it
}
std::list<string> combine(list<string> L, list<string> E, list<string> G){ //combines thre string lists in order of inputs and returns the final list
  L.splice(L.end(),E);
  L.splice(L.end(),G);
  return L;
}
list<string> quick(list<string> myList, int length){//takes an unsorted list of strings and it's length, then outputs a list of strings using quicksort
  if(length==1||length==0){//if the list is empty or only has one item, its sorted!
    return myList;
  }
  int pivot = rand() % length;//find a random number between 0 and length-1
  auto iterator = myList.begin();//makes an iterator to run through the list
  advance(iterator, pivot); //goes to the value at index "pivot"
  string pivotVal=*iterator; //that value is pivotVal
  list<string> L;
  list<string> G;
  list<string> E;
  string first;
  for(int i=0;i<length;i++){//iterate through the list
    first = myList.front();//save the first value and remove it from the list
    myList.pop_front();
    if(first<pivotVal){//add it to it's respective list based on how it compares to pivotVal
      L.push_front(first);
    }
    else if(first>pivotVal){
      G.push_front(first);
    }
    else{
      E.push_front(first);
    }
  }
  L = quick(L, L.size());//do it again for each list
  G = quick(G, G.size());
  return combine(L, E, G);//once all lists are down to 1 or 0 values, they should be combined
}

string* heap(string myArray[],int length){//takes a string array of unsorted value and an it of it's length and returns a sorted string array using heapsort
  string* heap = new string[length+1];
  int k;
  string temp;
  bool swap=true;
  for(int i=1;i<length+1;i++){//builds a heap
    heap[i]=myArray[i-1];
    k=i;//k represents the index of the most recently added value, initially I, but k changes where i shouldn't.
    while(heap[k]<heap[k/2] && k>1){//upheap by switching k with it's parent until it is either the root or it is larger than it's parent.
      temp=heap[k];
      heap[k]=heap[k/2];
      heap[k/2]=temp;
      k=k/2;
    }
  }
  for(int i=1;i<length+1;i++){//adds the root to the output array, removes it from the heap, then downheaps
    myArray[i-1]=heap[1];
    heap[1]=heap[length-i+1];//puts the last item at the root
    k=1;//k, the index of the item that needs to be downheaped, which always starts as the root
    while(swap){
      swap=false;
      if(heap[2*k]<heap[2*k+1]){//if left child is smaller than right child
	if(heap[2*k]<heap[k]&&2*k<=length-i){//if left child is smaller than k, swap them, and a swap has been made,   so the while must be run again
	temp=heap[k];
	heap[k]=heap[2*k];
	heap[2*k]=temp;
	k=2*k;
	swap=true;
      }
    }
      else{//if right child is smaller, do the same thing with right child
      if(heap[2*k+1]<heap[k]&&2*k+1<=length-i){
        temp=heap[k];
	heap[k]=heap[2*k+1];
	heap[2*k+1]=temp;
	k=2*k+1;
	swap=true;
      }
    }
    }
    swap=true;
  }
  return myArray;
}

void print(list<string> sortedList){//prints a sorted list with each element on its own line
  string first;
  int length = sortedList.size();
  for(int i=0;i<length;i++){
    first=sortedList.front();
    sortedList.pop_front();
    cout<<first<<endl;
  }
}
void printArr(string sortedArr[], int length){//prints a sorted array with each element on it's own line
  for(int i=0;i<length;i++){
      cout<<sortedArr[i]<<endl;
  }
}
int main(int argc, char *argv[]){
  if(argc!=3&&argc!=4){//make sure the correct numbwe of args was passed
    cerr << "USAGE: " << argv[0] << " <file> <sorting method> [-print]" << endl;
    return -1;
  }

  ifstream ifile(argv[1]);
  if(!ifile){//make sure the file opens
     cerr << "ERROR: Could not open file:\"" << argv[1] << "\"" <<endl;
      return -1;
  }
  std::string length;
  std::getline(ifile,length);//sets length equal to the first value in the file
  std::list<string> unsortedList;
  string* unsortedArray = new string[stoi(length)];
  string temp;
  streampos position = ifile.tellg();//save the current position
  for(int i=0; i<stoi(length); i++){//make a list out of the unsorted elements
    std::getline(ifile, temp);
    unsortedList.push_back(temp);
  }
  ifile.seekg(position);//go back to before making the list
  for(int i=0; i<stoi(length);i++){//also make an array
    getline(ifile, unsortedArray[i]);
  }
  if(argc==4){//if theres a 4th argument (-print), print
    if(string(argv[2])=="bubble"){//if the 3rd arg is bubble, print bubble sort
      printArr(bubble(unsortedArray, stoi(length)),stoi(length));
    }
    else if(string(argv[2])=="merge") {//if the 3rd arg is merge, print merge sort
      printArr(mergeSort(unsortedArray, stoi(length)), stoi(length));
    }
    else if(string(argv[2])=="heap") {//if the 3rd arg is heap, print heap sort
      printArr(heap(unsortedArray, stoi(length)), stoi(length));
    }
    else if(string(argv[2])=="quick"){//if the 3rd arg is quick, print quick sort
      print(quick(unsortedList, stoi(length)));
    }
    else if(string(argv[2])=="sys"){//if the 3rd arg is sys, print sys sort
      unsortedList.sort();
      print(unsortedList);
    }
    else{//if none of the above were the 3rd argument, an invalid 3rd argument was passed
      cerr << "USAGE: " << argv[0] << " <file> <sorting method> [-print]" << endl;
      return -1;
    }
  }
  else {//if there isnt a 4th argument, dont print
    if(string(argv[2])=="bubble"){//if the 3rd argument is bubble, run bubble sort
      bubble(unsortedArray, stoi(length));
    }
    else if(string(argv[2])=="merge") {//if the 3rd argument is merge, run merge sort
      mergeSort(unsortedArray, stoi(length));
    }
    else if(string(argv[2])=="heap") {//if the 3rd argument is heap, run heap sort
      heap(unsortedArray, stoi(length));
    }
    else if(string(argv[2])=="quick"){//if the 3rd argument is quick, run quick sort
      quick(unsortedList, stoi(length));
    }
    else if(string(argv[2])=="sys"){//if the 3rd argument is sys, run sys sort
      unsortedList.sort();
    }
  }
  return 0;
}
