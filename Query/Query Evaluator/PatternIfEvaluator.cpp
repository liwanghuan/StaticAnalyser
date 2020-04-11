#include "PatternIfEvaluator.h"

PatternIfEvaluator::PatternIfEvaluator() {

}
PatternIfEvaluator::~PatternIfEvaluator() {

}

/*
Input: pattern if clause
Output: pattern if answers
*/
void PatternIfEvaluator::evaluatePatternIf(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	unordered_map<int, int> IfPatternMap = PKB::getPKBInstance()->getIfPatternMap();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	
	if (arg1Type == "string") {
		arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
		int arg1Num = PKB::getPKBInstance()->getVarID(arg1);
		list<int> possibleIfs = PKB::getPKBInstance()->getIfPatternStmtNumber(arg1);
		while(!possibleIfs.empty()) {
			pair<int, int> result = { possibleIfs.front(),arg1Num };
			resultList.push_back(result);
			possibleIfs.pop_front();
		}
	}
	else {
		for (auto it = IfPatternMap.begin(); it != IfPatternMap.end(); it++) {
			pair<int, int> result = { it->first, it->second };
			resultList.push_back(result);
		}
	}

}

vector<pair<int, int>> PatternIfEvaluator::getPatternIfResultList() {
	return resultList;
}