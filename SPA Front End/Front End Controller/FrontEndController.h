#pragma once

#include <iostream>
#include <list>
#include <string>

#include "../Parser/Parser.h"
#include "../Design Extractor/DesignExtractor.h"
#include "../../PKB/PKB.h" // remove later for testing environment

using namespace std;


class FrontEndController {
public:
	// default constructor
	FrontEndController();

	// destructor
	//~FrontEndController();

	// method of reading and initializing the source code
	vector<Statement> processSourceCode(string code);
	void createFollowsStarMap();
	void createFollowsStarMapReverse();
	void createParentStarMap();
	void createParentStarMapReverse();
	void createCallsMap();
	void createCallsStarMap();
	void createStmtCallsMap();
	void updateProcUsesMap();
	void updateProcModifiesMap();
	void updateStmtUsesMap();
	void updateStmtModifiesMap();
	void sortUsesModifiesMap();
	void createCFG();

private:
	Parser parser;
	DesignExtractor designExtractor;
};