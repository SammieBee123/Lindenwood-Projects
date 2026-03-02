/*
 * FILE: main.cpp
 * Author: Sam Disbrow
 * DATE: 11/11/2024 
 */
#include "AirportAnimator.hpp"

#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <sys/sem.h>

#define NUM_SEMS 3
#define SIG_NUM_COMMANDS 3
#define WAIT_NUM_COMMANDS 1

using namespace std;
int totalTourGoal;
int totalTours;
int semID;

pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;

void* planeThread(void *arg)
{
  int semctlResult = semctl(semID, 1, GETVAL);
  struct sembuf passWaitCommand[WAIT_NUM_COMMANDS];
  
  passWaitCommand[0].sem_num=0; //numPass
  passWaitCommand[0].sem_op= -1; //decrease by one, wait if needed
  passWaitCommand[0].sem_flg=0; //default flags
  
  struct sembuf passSigCommand[WAIT_NUM_COMMANDS];
  
  passSigCommand[0].sem_num=0; //numPass
  passSigCommand[0].sem_op= +1; //increase by one, wait if needed
  passSigCommand[0].sem_flg=0; //default flags
  
  struct sembuf tourWaitCommand[WAIT_NUM_COMMANDS];
  
  tourWaitCommand[0].sem_num=1; //numTours (remaining)
  tourWaitCommand[0].sem_op= -1; //decrease by one, wait if needed -- need to make sure not to try to do this if 0!
  tourWaitCommand[0].sem_flg=0; //default flags
  
  struct sembuf runSigCommand[WAIT_NUM_COMMANDS];
  
  runSigCommand[0].sem_num=2; //runway
  runSigCommand[0].sem_op= +1; //increase by one, wait if needed
  runSigCommand[0].sem_flg=0; //default flags
  
  struct sembuf runWaitCommand[WAIT_NUM_COMMANDS];
  
  runWaitCommand[0].sem_num=2; //runway
  runWaitCommand[0].sem_op= -1; //decrease by one, wait if needed
  runWaitCommand[0].sem_flg=0; //default flags
  
  int planeNum = *((int *)arg)-1;
  int passWaitresult;
  int passSigresult;
  int tourWaitresult;
  int runSigresult;
  int runWaitresult;

  while(semctlResult>10){
    for (int passNum = 1; passNum<11; passNum++) //board 10 passengers
    {
      passWaitresult = semop(semID, passWaitCommand, WAIT_NUM_COMMANDS); //passnum minus one, wait if necessary
      if (passWaitresult == -1) //if semop fails
      {
        cout << "semop failed" << endl;
        return arg;
      }
      AirportAnimator::updatePassengers(planeNum,3); AirportAnimator::updatePassengers(planeNum,passNum); //update passenger number in airport animator
      sleep(rand()%3);
    }
    AirportAnimator::updateStatus(planeNum, "TAXI");
    AirportAnimator::taxiOut(planeNum);
  
    runWaitresult = semop(semID, runWaitCommand, WAIT_NUM_COMMANDS); //take runway
      if (runWaitresult == -1) //if semop fails
      {
        cout << "semop failed" << endl;
        return arg;
      }
      
    AirportAnimator::updateStatus(planeNum, "TKOFF");
    AirportAnimator::takeoff(planeNum);
    runSigresult = semop(semID, runSigCommand, WAIT_NUM_COMMANDS); //"give back" runway
      if (runSigresult == -1) //if semop fails
      {
        cout << "semop failed" << endl;
        return arg;
      }
    AirportAnimator::updateStatus(planeNum,"TOUR");
    sleep(5+rand()%41);
  
    AirportAnimator::updateStatus(planeNum,"LNDRQ");
    runWaitresult = semop(semID, runWaitCommand, WAIT_NUM_COMMANDS); //take runway
      if (runWaitresult == -1) //if semop fails
      {
        cout << "semop failed" << endl;
        return arg;
      }

    AirportAnimator::updateStatus(planeNum,"LAND");
    AirportAnimator::land(planeNum);
    runSigresult = semop(semID, runSigCommand, WAIT_NUM_COMMANDS); //"give back" runway
      if (runSigresult == -1) //if semop fails
      {
        cout << "semop failed" << endl;
        return arg;
      }

    AirportAnimator::updateStatus(planeNum, "TAXI");
    AirportAnimator::taxiIn(planeNum);

    AirportAnimator::updateStatus(planeNum, "DEPLN");
  
    for (int passNum = 10; passNum >-1; passNum--) //board 10 passengers
    {
      passSigresult = semop(semID, passSigCommand, WAIT_NUM_COMMANDS); //passnum minus one.
      if (passSigresult == -1) //if semop fails
      {
        cout << "semop failed" << endl;
        return arg;
      }
      AirportAnimator::updatePassengers(planeNum,passNum); //update passenger number in airport animator
      sleep(1);
    }
    tourWaitresult = semop(semID, tourWaitCommand, WAIT_NUM_COMMANDS);
    semctlResult = semctl(semID, 1, GETVAL);
    AirportAnimator::updateTours(totalTourGoal-(semctlResult-10));
  }
  return arg;
}

int main(int argc, char *argv[])
{

  totalTourGoal=atoi(argv[2]);
  int myKeyVal = 01;
  
  semID = semget(myKeyVal, NUM_SEMS, IPC_CREAT|IPC_EXCL|0666);  //make a set with 2 semaphores
  if (semID == -1)
  {
    cout << "semget failed with error number: " << errno << endl;
    return 2;
  }
  struct sembuf sigCommand[SIG_NUM_COMMANDS];
  sigCommand[0].sem_num=0; //passengers
  sigCommand[0].sem_op= +atoi(argv[1]); //add the first command line argument
  sigCommand[0].sem_flg=0; //default flags

  sigCommand[1].sem_num=1; //tours
  sigCommand[1].sem_op= +(atoi(argv[2]))+10; //add the second command line argument
  sigCommand[1].sem_flg=0; //default flags
  
  sigCommand[2].sem_num=2; //runway
  sigCommand[2].sem_op= +1; //add 1
  sigCommand[2].sem_flg=0; //default flags
  
  int semresult = semop(semID, sigCommand, SIG_NUM_COMMANDS); //sets number of tours remaining and number of passengers currently in the airport
  if (semresult == -1)
  {
    cout << "semop failed" << endl;
    return 3;
  }
  int id1=1;
  int id2=2;
  int id3=3;
  int id4=4;
  int id5=5;
  int id6=6;
  int id7=7;
  int id8=8;
  
  AirportAnimator::init();
  
  int errcode=pthread_create(&thread1, NULL, planeThread, (void *) &id1);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
  
  errcode=pthread_create(&thread2, NULL, planeThread, (void *) &id2);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
    
  errcode=pthread_create(&thread3, NULL, planeThread, (void *) &id3);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
    
  errcode=pthread_create(&thread4, NULL, planeThread, (void *) &id4);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
    
  errcode=pthread_create(&thread5, NULL, planeThread, (void *) &id5);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
    
  errcode=pthread_create(&thread6, NULL, planeThread, (void *) &id6);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
    
  errcode=pthread_create(&thread7, NULL, planeThread, (void *) &id7);
  if (errcode == -1)
    cerr << "thread create failed" << endl;
    
  errcode=pthread_create(&thread8, NULL, planeThread, (void *) &id8);
  if (errcode == -1)
    cerr << "thread create failed" << endl;

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);
  pthread_join(thread5, NULL);
  pthread_join(thread6, NULL);
  pthread_join(thread7, NULL);
  pthread_join(thread8, NULL);
  
  AirportAnimator::end();
  semctl(semID,0,IPC_RMID);
  semctl(semID,1,IPC_RMID);
  semctl(semID,2,IPC_RMID);
  return 0;
}

