/*
 * Smalltalk_Brit.cpp
 *
 *  Created on: Nov 5, 2018
 *      Author: Nic Falcione
 */
#include "includes/Smalltalk_Brit.h"
#include "includes/constants.h"

Smalltalk_Brit::Smalltalk_Brit(int iPerson) :
		Smalltalk(BRIT, iPerson) {
	populatePhrases();
}
Smalltalk_Brit::~Smalltalk_Brit(void) {

}
void Smalltalk_Brit::populatePhrases() {
	mySmallTalk.push_back(BRIT_1);
	mySmallTalk.push_back(BRIT_2);
	mySmallTalk.push_back(BRIT_3);
	mySmallTalk.push_back(BRIT_4);
	mySmallTalk.push_back(BRIT_5);
	mySmallTalk.push_back(BRIT_6);
	mySmallTalk.push_back(BRIT_7);
}

