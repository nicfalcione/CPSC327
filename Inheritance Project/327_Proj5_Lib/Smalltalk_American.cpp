/*
 * Smalltalk_American.cpp
 *
 *  Created on: Nov 5, 2018
 *      Author: Nic Falcione
 */
#include <vector>
#include "includes/Smalltalk_American.h"
#include "includes/constants.h"

using namespace std;

//create with appropriate phrases
//use base class call to set Nationality (See constants for Nationality strings)
Smalltalk_American::Smalltalk_American(int iPerson) :
		Smalltalk(AMERICAN, iPerson) {
	populatePhrases();

}
Smalltalk_American::Smalltalk_American(std::string myNationality, int iPerson) :
		Smalltalk(AMERICAN, iPerson) {
	populatePhrases();
}

Smalltalk_American::~Smalltalk_American(void) {

}

void Smalltalk_American::populatePhrases() {
	mySmallTalk.push_back(AMERICAN_PHRASE_1);
	mySmallTalk.push_back(AMERICAN_PHRASE_2);
	mySmallTalk.push_back(AMERICAN_PHRASE_3);
	mySmallTalk.push_back(AMERICAN_PHRASE_4);
	mySmallTalk.push_back(AMERICAN_PHRASE_5);
}

