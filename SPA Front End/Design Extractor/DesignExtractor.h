#pragma once

#include <string>
#include <iostream>
#include <map>
#include <list>
#include <vector>

#include "../../PKB/PKB.h"

using namespace std;

class DesignExtractor {
public:
	unordered_map<int, int> reverseMap(unordered_map<int, int>);

	unordered_map<string, int> reverseStringTable(unordered_map<int, string> stringTable);

	void setFollowsStarMap();
	void setCallsMap();
	void setStmtCallsMap();
	void setCallsStarMap();
	void setCallsStarMapDFS(int, vector<bool>&, list<int>);
	void setFollowsStarMapReverse();
	void setParentStarMap();
	void sortUsesModifiesMap();
	void setParentStarMapReverse();
	void updateProcUsesMap();
	void updateProcModifiesMap();
	void updateStmtUsesMap();
	void updateStmtModifiesMap();

	unordered_map<int, list<int>> reverseListMap(unordered_map<int, list<int>>);

	void buildCFG();
};
