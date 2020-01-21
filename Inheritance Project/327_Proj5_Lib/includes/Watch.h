/*
 * Watch.h
 *
 *  Created on: Nov 5, 2017
 *      Author: keith
 */

#ifndef WATCH_H_
#define WATCH_H_
#include <string>

class Watch {
public:
	Watch();
	virtual ~Watch();
	virtual std::string getTime();
};

#endif /* WATCH_H_ */
