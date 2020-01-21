#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

#include "../includes_usr/library.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/fileIO.h"
using namespace std;

//NOTE: please ensure patron and book data are loaded from disk before calling the following
//NOTE: also make sure you save patron and book data to disk any time you make a change to them
//NOTE: for files where data is stored see constants.h BOOKFILE and PATRONFILE

vector<book> books;
vector<patron> patrons;
int nextPatronID = 0;

/*
 * clear books and patrons containers
 * then reload them from disk 
 */
void reloadAllData() {
	//Use standard library to clear book and patron containers
	books.clear();
	patrons.clear();

	//Loads books from disk
	loadBooks(books, BOOKFILE.c_str());

	//Loads patrons from disk
	loadPatrons(patrons, PATRONFILE.c_str());
}

/* checkout a book to a patron
 * first load books and patrons from disk
 * make sure patron enrolled (patronid is assigned to a patron in patrons container)
 * make sure book in collection (bookid is assigned to a book in books container)
 * 
 * see if patron can check out any more books 
 * 	if not return TOO_MANY_OUT patron has the MAX_BOOKS_ALLOWED_OUT
 * 	
 * if so then check the book out to the patron, set the following fields for the book in the
 * books container
 * book.loaned_to_patron_id = patronid;
 * book.state = OUT;
 * 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 *         PATRON_NOT_ENROLLED
 * 		   BOOK_NOT_IN_COLLECTION
 *         TOO_MANY_OUT patron has the max number of books allowed checked out
 */
int checkout(int bookid, int patronid) {
	//Load Books from disk
	loadBooks(books, BOOKFILE.c_str());

	//Load Books from disk
	loadPatrons(patrons, PATRONFILE.c_str());

	//Used to check if Patron is enrolled
	bool patronFound = false;

	//Used to check if book is in collection
	bool bookFound = false;

	//stores position of patron in the vector if needed
	int patronPos;

	//Stores position of the book in the vector if needed
	int bookPos;

	//checks to see if the patron is in the vector
	for (unsigned int i = 0; i < patrons.size(); i++) {
		if (patronid == patrons.at(i).patron_id) {
			patronFound = true;
			patronPos = i;
		}
	}

	//If patron not found, return error code
	if (!patronFound) {
		return PATRON_NOT_ENROLLED;
	}

	//Checks to see if book is in the vector
	for (unsigned int i = 0; i < books.size(); i++) {
		if (books.at(i).book_id == bookid) {
			bookFound = true;
			bookPos = i;
		}
	}

	//If book is not found, return error code
	if (!bookFound) {
		return BOOK_NOT_IN_COLLECTION;
	}

	//If patron has 5 books checked out already, it does not allow another and returns error code
	if (patrons.at(patronPos).number_books_checked_out == 5) {
		return TOO_MANY_OUT;
	}

	//Increments the amount of books checked out by the patron
	patrons.at(patronPos).number_books_checked_out++;

	//Tracks what patron has the book checked out
	books.at(bookPos).loaned_to_patron_id = patronid;

	//Changes book's state to checked out
	books.at(bookPos).state = OUT;

	//Save patrons to disk
	savePatrons(patrons, PATRONFILE.c_str());

	//Save books to disk
	saveBooks(books, BOOKFILE.c_str());

	return SUCCESS;
}

/* check a book back in 
 * first load books and patrons from disk
 * make sure book in collection (bookid is assigned to a book in books container)
 *  	
 * if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
 * then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;
 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 * 		   BOOK_NOT_IN_COLLECTION
 */
int checkin(int bookid) {
	//Load Books from disk
	loadBooks(books, BOOKFILE.c_str());

	//Load Books from disk
	loadPatrons(patrons, PATRONFILE.c_str());

	//Tracks whether book is in the collection or not
	bool inCollection = false;

	//Stores patron position if needed
	int patronWithBookID;

	//Stores book position if needed
	int bookNumber;

	//Checks to see if the book is in the collection
	for (unsigned int i = 0; i < books.size(); i++) {
		if (books.at(i).book_id == bookid) {
			inCollection = true;
			patronWithBookID = books.at(i).loaned_to_patron_id;
			bookNumber = i;
		}
	}

	//If book is not in the collection, return error code
	if (!inCollection) {
		return BOOK_NOT_IN_COLLECTION;
	}

	//Decrements the number of books checked out by patron
	patrons.at(patronWithBookID).number_books_checked_out--;

	//Sets book's borrower to none
	books.at(bookNumber).loaned_to_patron_id = NO_ONE;

	//Changes book's state to checked in
	books.at(bookNumber).state = IN;

	//Save patrons to disk
	savePatrons(patrons, PATRONFILE.c_str());

	//Save books to disk
	saveBooks(books, BOOKFILE.c_str());

	return SUCCESS;
}

/*
 * enroll a patron, duplicate names are fine as patrons are uniquely identified by their patronid
 * first load books and patrons from disk
 * create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
 * then push the patron onto the patrons container
 * save all changes to the patrons container to disk
 * return 
 *    the patron_id of the person added
 */
int enroll(std::string &name) {
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, PATRONFILE.c_str());

	patron p;
	p.name = name;
	p.patron_id = nextPatronID;
	p.number_books_checked_out = NONE;

	//Increments next available and unique patronID
	nextPatronID++;

	//Puts patron into vector
	patrons.push_back(p);

	//Save patrons to disk
	savePatrons(patrons, PATRONFILE.c_str());
	return p.patron_id;
}

/*
 * the number of books in the books container
 * (ie. if 3 books returns 3)
 * 
 */
int numbBooks() {
	//Load Books from disk
	loadBooks(books, BOOKFILE.c_str());

	return books.size();
}

/*
 * the number of patrons in the patrons container
 * (ie. if 3 patrons returns 3)
 */
int numbPatrons() {
	//Load patrons from disk
	loadPatrons(patrons, PATRONFILE.c_str());

	return patrons.size();
}

/*the number of books patron has checked out
 *
 *returns a positive number indicating how many books are checked out 
 *        or PATRON_NOT_ENROLLED         
 */
int howmanybooksdoesPatronHaveCheckedOut(int patronid) {
	for (unsigned int i = 0; i < patrons.size(); i++) {
		if (patrons.at(i).patron_id == patronid) {
			return patrons.at(i).number_books_checked_out;
		}
	}
	return PATRON_NOT_ENROLLED;
}

/* search through patrons container to see if patronid is there
 * if so returns the name associated with patronid in the variable name
 * 
 * returns SUCCESS found it and name in name
 *         PATRON_NOT_ENROLLED no patron with this patronid
 */
int whatIsPatronName(std::string &name, int patronid) {
	for (unsigned int i = 0; i < patrons.size(); i++) {
		if (patrons.at(i).patron_id == patronid
				and patrons.at(i).name == name) {
			return SUCCESS;
		}
	}
	return PATRON_NOT_ENROLLED;
}

