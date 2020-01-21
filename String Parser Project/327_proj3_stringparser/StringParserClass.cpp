/*
 * StringParserClass.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: Nic Falcione
 */

#include <string>
#include <string.h>
#include <iostream>

#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;

char *pStartTag;
char *pEndTag;
bool areTagsSet;

namespace KP_StringParserClass {

//dont forget to initialize member variables
StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

//call cleanup to release any allocated memory
StringParserClass::~StringParserClass(void) {
	StringParserClass::cleanup();
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	int iLen = strlen(pStart);

	pStartTag = new char[iLen + 1];

	strncpy(pStartTag, pStart, iLen);

	int iLeng = strlen(pEnd);

	pEndTag = new char[iLeng + 1];

	strncpy(pEndTag, pEnd, iLeng);

	areTagsSet = true;
	return SUCCESS;
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
		std::vector<std::string> &myVector) {
	myVector.clear();

	if (pStartTag == NULL || pEndTag == NULL) {
		return ERROR_TAGS_NULL;
	}

	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}

	bool openTag = false;
	string data;
	int size = 0;
	for (; *pStartTag != '\0'; ++pStartTag) {
		size++;
	}
	for (int i = 0; i < size; i++) {
		pStartTag--;
	}

	for (; *pDataToSearchThru != '\0'; ++pDataToSearchThru) {
		if (!openTag and *pDataToSearchThru == '<') {
			bool tagRight = true;
			for (int i = 0; i < size - 2; i++) {
				if (*pDataToSearchThru != *pStartTag) {
					tagRight = false;
				}
				if (*pDataToSearchThru == *pStartTag) {
					if (tagRight and *pDataToSearchThru == '>') {
						openTag = true;
					}
				}
				pDataToSearchThru++;
				pStartTag++;
			}
			for (int i = 0; i < size - 2; i++) {
				pStartTag--;
			}
		}

		if (openTag and *pDataToSearchThru == '<') {
			bool tagRight = true;
			for (int i = 0; i < size - 1; i++) {
				if (*pDataToSearchThru != *pEndTag) {
					tagRight = false;
				}
				if (tagRight and *pDataToSearchThru == *pEndTag) {
					if (*pDataToSearchThru == '>') {
						myVector.push_back(data);
						data = "";
					}
				}
				pDataToSearchThru++;
				pEndTag++;
			}

			pDataToSearchThru--;
			for (int i = 0; i < size - 1; i++) {
				pEndTag--;
			}
			openTag = false;
		}

		if (openTag) {
			data += *pDataToSearchThru;
		}

	}

	return SUCCESS;
}

void StringParserClass::cleanup() {
	if (pStartTag) {
		delete pStartTag;
	}

	if (pEndTag) {
		delete pEndTag;
	}
	areTagsSet = false;
}

//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	if (*pEnd == 0) {
		return FAIL;
	}
	return SUCCESS;
}

}
