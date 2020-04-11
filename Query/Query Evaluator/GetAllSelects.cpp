#include "GetAllSelects.h"

/*
Input: type of the variable
Output: return all answers of such type of variables
*/
vector<int> GetAllSelects::getAllSelects(string selectType) {
	vector<int> result;
	if (selectType == "stmt" || selectType == "all" || selectType == "prog_line") {
		for (int i = 1; i <= PKB::getPKBInstance()->getTotalNumOfProgLine(); i++) {
			result.push_back(i);
		}
	}
	else if (selectType == "while") {
		unordered_map<int, int> whileMp = PKB::getPKBInstance()->getWhilePatternMap();
		for (auto value = whileMp.begin(); value != whileMp.end(); value++) {
			result.push_back(value->first);
		}
	}
	else if (selectType == "if") {
		unordered_map<int, int> ifMap = PKB::getPKBInstance()->getIfPatternMap();
		for (auto it = ifMap.begin(); it != ifMap.end(); it++) {
			result.push_back(it->first);
		}
	}
	else if (selectType == "call" || selectType == "callstmt" || selectType == "callprocname") {
		unordered_map<int, int> callsMap = PKB::getPKBInstance()->getStmtCallsMap();
		for (auto it = callsMap.begin(); it != callsMap.end(); it++) {
			result.push_back(it->first);
		}
	}
	else if (selectType == "assign") {
		unordered_map<int, pair<string, string>> patternMap = PKB::getPKBInstance()->getAssignPatternMap();
		for (auto value = patternMap.begin(); value != patternMap.end(); value++) {
			result.push_back(value->first);
		}
	}
	else if (selectType == "constant") {
		list<int> constantMap = PKB::getPKBInstance()->getConstList();
		while(!constantMap.empty()) {
			result.push_back(constantMap.front());
			constantMap.pop_front();
		}
	}
	else if (selectType == "variable") {
		for (int i = 1; i <= PKB::getPKBInstance()->getVarTableSize(); i++) {
			result.push_back(i);
		}
	}
	else if (selectType == "procedure") {
		for (int i = 1; i <= PKB::getPKBInstance()->getProcTableSize(); i++) {
			result.push_back(i);
		}
	}

	return result;
}