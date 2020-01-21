/*
 * Functions.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: keith
 */

#include "./includes/Functions.h"
#include "./includes/Smalltalk_American.h"
#include "./includes/ST_American_DonutEnthusiest.h"
#include "./includes/Smalltalk_Brit.h"
#include "./includes/Watch.h"
#include "./includes/constants.h"

#include <vector>
#include <iostream>

using namespace std;

//create a vector with appropriate numbers of Smalltalk_Brit,Smalltalk_American and ST_American_DonutEnthusiest
//objects using unique pointers.  Watches are given sequentially starting with first person in the vector until 
//all watches given or everyone has a watch (case where more watches than people)
//Since we are using c++11 returning this vector by value is fine since the 
//compiler will move the vector on return rather than recreate it (this means there is no copy penalty)
std::vector<std::unique_ptr<Smalltalk>> getPeople(int numBrit, int numAmerican,
		int numbAmericanDonutEnthusiest, int numWatches) {
	int cnt = 0;

	//create a vector to hold SmallTalk unique pointers
	vector<unique_ptr<Smalltalk>> vector;

	//add brits to vector
	for (int i = 0; i < numBrit; i++) {
		unique_ptr<Smalltalk> ptr(new Smalltalk_Brit(cnt));
		vector.push_back(std::move(ptr));
		cnt++;
	}

	//add americans  to vector
	for (int i = 0; i < numAmerican; i++) {
		unique_ptr<Smalltalk> ptr(new Smalltalk_American(cnt));
		vector.push_back(std::move(ptr));
		cnt++;
	}

	//add american donut enthusiest  to vector
	for (int i = 0; i < numAmerican; i++) {
		unique_ptr<Smalltalk> ptr(new ST_American_DonutEnthusiest(cnt));
		vector.push_back(std::move(ptr));
		cnt++;
	}

	//create some watches (as long as number watches <= numb people)
	//then give the watches away to first NUM_WATCHES people in the vector
	//keep in mind that you are responsible for deleting any pointers to
	//watches allocated on the heap when you are finished using the vector you return
	//from this function(see Smalltalk header for hints)
	unsigned int watches = numWatches;

	if ((unsigned) numWatches > vector.size()) {
		watches = vector.size();
	}

	Watch *watch = new Watch;
	for (unsigned int i = 0; i < watches; i++) {
		vector[i]->giveWatch(watch);
		watch = new Watch;
	}

	if (watch) {
		delete watch;
	}

//return your vector
	return vector;
}

