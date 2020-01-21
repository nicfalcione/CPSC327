#pragma once
#include "Smalltalk_American.h"
class ST_American_DonutEnthusiest :
	public Smalltalk_American
{
public:
	//create with appropriate phrases
	ST_American_DonutEnthusiest(int iPerson=1);
	virtual ~ST_American_DonutEnthusiest(void);
	
	//base class populatePhrases() will be called first as part of its construction
	//before this class calls populate phrases as part of its construction
	//the end result is mySmallTalk will contain first the base class phrases and 
	//then this classes phrases
	virtual void populatePhrases();
};

