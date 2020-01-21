/*
 * fileIO.cpp
 *
 *  Created on: Oct 1, 2018
 *      Author: Nic Falcione
 */

#include "../includes_usr/fileIO.h"
#include "../includes_usr/constants.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/library.h"
#include<iostream>
#include<stdio.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//Converts book struct into a string of information for the library file
string bookToString(book &b) {
	int stateNum = 0;
	if (b.state == IN) {
		stateNum = 1;
	}

	else if (b.state == OUT) {
		stateNum = 2;
	}

	return to_string(b.book_id) + "," + b.title + "," + b.author + ","
			+ to_string(stateNum) + "," + to_string(b.loaned_to_patron_id);
}

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename) {
	books.clear();

	//Grabs string from pointer
	string name = filename;

	//Create in/out stream for library file
	ifstream file;

	//Opens library file
	file.open(name.c_str());

	//Returns error if the file cannot be opened
	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	int emptyCheck = -1;

	while (!file.eof()) {
		emptyCheck++;

		int iD;
		string title;
		string author;
		book_checkout_state state;
		int patronloanedto;
		book b;

		string csv;
		int i = 0;

		getline(file, line);
		istringstream myline(line);

		while (getline(myline, csv, ',')) {
			switch (i) {
			case 0:
				iD = stoi(csv);
				i++;
				break;
			case 1:
				title = csv;
				i++;
				break;
			case 2:
				author = csv;
				i++;
				break;
			case 3:
				switch (stoi(csv)) {
				case 0:
					state = UNKNOWN;
					i++;
					break;

				case 1:
					state = IN;
					i++;
					break;
				case 2:
					state = OUT;
					i++;
					break;
				}
				break;
			case 4:
				patronloanedto = stoi(csv);
				b.book_id = iD;
				b.title = title;
				b.author = author;
				b.state = state;
				b.loaned_to_patron_id = patronloanedto;

				books.push_back(b);
				i = 0;
				break;
			}
		}
	}

	//Checks to see if file is empty
	if (emptyCheck == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	//Returns success is file is successfully loaded into the vector
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {
	if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	string name = filename;
	ofstream file;
	file.open(name.c_str());

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	for (unsigned int i = 0; i < books.size(); i++) {
		line = bookToString(books.at(i));
		file << line << endl;
	}

	file.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {
	patrons.clear();

	string name = filename;
	ifstream file;
	file.open(name.c_str());

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	int emptyCheck = -1;

	string line;
	while (!file.eof()) {
		emptyCheck++;

		int iD;
		string name;
		int books;
		patron p;

		string csv;
		int i = 0;

		getline(file, line);
		istringstream myline(line);

		while (getline(myline, csv, ',')) {
			switch (i) {
			case 0:
				iD = stoi(csv);
				i++;
				break;
			case 1:
				name = csv;
				i++;
				break;
			case 2:
				books = stoi(csv);
				p.patron_id = iD;
				p.name = name;
				p.number_books_checked_out = books;
				patrons.push_back(p);

				i = 0;
				break;
			}
		}
	}

	if (emptyCheck == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	return SUCCESS;
}
/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {
	if (patrons.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	string name = filename;
	ofstream file;
	file.open(name.c_str());

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	for (unsigned int i = 0; i < patrons.size(); i++) {
		line = to_string(patrons.at(i).patron_id) + "," + patrons.at(i).name
				+ "," + to_string(patrons.at(i).number_books_checked_out);
		file << line << endl;
	}

	file.close();
	return SUCCESS;
}

