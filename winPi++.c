/*==================================================================================================
 *	winPi.c
 *	Author	:	Jared Frenzel and Jacob Miller
 *	Purpose	:	Approximate pi using multiple windows threads
 *	Created	:	October 2, 2015 */
//==================================================================================================

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <process.h>
#include <time.h>
#include "mathUtils.h"

#define NUMBER_OF_THREADS 		8.0
#define NUMBER_OF_ITERATIONS	10000.0
#define ITERATIONS_PER_THREAD 	(NUMBER_OF_ITERATIONS / NUMBER_OF_THREADS) * 1.0 

double piMethod(int iteration);
void calcOnInterval(void *pThread);


HANDLE hPiMutex;
HANDLE hPercentMutex;
HANDLE mainThreadHandle;
HANDLE hScreenMutex;

double pi;
double percentComplete;
int threadNo;


int main(int argC, char **argV) {
	
	//Init values and mutexes
	hPiMutex = CreateMutex(NULL, FALSE, NULL);
	hPercentMutex = CreateMutex(NULL, FALSE, NULL);
	mainThreadHandle = GetCurrentThread();
	threadNo = 0;
	double timeTaken = 0.0;
	percentComplete = 0.0;
	pi = 0.0;
	clock_t begin, end;
	
	
	
	//Get start time
	begin = clock();
	
	
	//Make all the threads
	int temp[(int)NUMBER_OF_THREADS];
	for (threadNo = 0; threadNo < NUMBER_OF_THREADS; threadNo++) {
		temp[threadNo] = threadNo;
		WaitForSingleObject(hScreenMutex,INFINITE);
		printf("\nMaking thread %d ...\n", threadNo);/////////////////////////////////////////
		ReleaseMutex(hScreenMutex);
		_beginthread(calcOnInterval, 0, &temp[threadNo]);
	}
	
	//Wait until the program is 100 percent complete
	do {
		WaitForSingleObject(hPercentMutex, INFINITE);
		WaitForSingleObject(hScreenMutex,INFINITE);
		printf("\b\b\b\b\b\b\b%%%.2f", percentComplete);
		ReleaseMutex(hScreenMutex);
		//printf("\nSuspending thread ...");
		ReleaseMutex(hPercentMutex);
		//printf("\nResuming thread ...");
		//SuspendThread(mainThreadHandle);
	} while (threadNo);
	
	
	//Get end time and calculate time taken
	end = clock();
	timeTaken = (end - begin) / 1000;
	
	//Print result
	WaitForSingleObject(hScreenMutex,INFINITE);
	printf("\nTime taken: %f seconds", timeTaken);
	printf("\nIterations: %.0f", NUMBER_OF_ITERATIONS);
	printf("\nThreads used: %.0f",NUMBER_OF_THREADS);
	printf("\nPi: %.16lf",pi);
	ReleaseMutex(hScreenMutex);
	
	int usrExit;
	printf("\nprint any key to exit...\n");
	scanf("%d",&usrExit);
	return 0;
}


void calcOnInterval(void *pThread) {
	int thread = *((int *)pThread);
	double localPi = 0;
	int localPercent = 0;
	
	WaitForSingleObject(hScreenMutex,INFINITE);
	printf("\nThread %d is running!\n",thread);////////////////////////////////////////////////
	ReleaseMutex(hScreenMutex);
	//Divide iterations evenly over all threads
	int i;
	for (i = thread * ITERATIONS_PER_THREAD; i < (thread + 1) * ITERATIONS_PER_THREAD; i++) {
		
		localPi += piMethod(i);
		
		
		//If the current local percentage has increased ...
		if ((int)(100*(i -  thread * ITERATIONS_PER_THREAD) / 
							(ITERATIONS_PER_THREAD-1)) >  localPercent) {
							
			//Wait for percent to become available, then remove the old percentage from the global
			WaitForSingleObject(hPercentMutex, INFINITE);
			percentComplete -= localPercent / NUMBER_OF_THREADS;
			
			
			//Set the local to the new value					
			localPercent = (int)(100*(i -  thread * ITERATIONS_PER_THREAD) / 
							(ITERATIONS_PER_THREAD-1));
						
			
			
			//If this is the last iteration get global pi, set, and release
			if (localPercent == 100) {
				WaitForSingleObject(hPiMutex, INFINITE);
				pi += localPi;
				ReleaseMutex(hPiMutex);
			}
			
			
			//Add the new local to the global then release the mutex
			percentComplete += localPercent / NUMBER_OF_THREADS;
			ResumeThread(mainThreadHandle);
			ReleaseMutex(hPercentMutex);
			
		}	
	}
	WaitForSingleObject(hScreenMutex,INFINITE);
	printf("\nClosing thread %d\n", thread);////////////////////////////////////////////////////
	ReleaseMutex(hScreenMutex);
	threadNo--;
	_endthread();
}


double piMethod(int iteration) {
	//This method calculates the sigma term for a given iteration number
	//It allows me to easily change the algorythm I am using
	double sigmaSegment = 0;
	sigmaSegment = (2*pow(-1,iteration)*pow(3,.5-iteration))/(2*iteration+1);
	return sigmaSegment;
}
