/*
 * Functions.h
 *
 *  Created on: Nov 5, 2017
 *      Author: keith
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <memory>
#include <vector>
#include <time.h>
//for delays
#include <chrono>
#include <thread>
#include "Smalltalk.h"


//create a vector with appropriate numbers of Smalltalk_Brit,Smalltalk_American and ST_American_DonutEnthusiest
//objects using unique pointers.  Watches are given sequentially starting with first person in the vector until 
//all watches given or everyone has a watch (case where more watches than people)
//Since we are using c++11 returning this vector by value is fine since the 
//compiler will move the vector on return rather than recreate it (this means there is no copy penalty)
std::vector<std::unique_ptr<Smalltalk>> getPeople(int numBrit = 1,
		int numAmerican = 1, int numbAmericanDonutEnthusiest = 1,
		int numWatches = 0);

#endif /* FUNCTIONS_H_ */
