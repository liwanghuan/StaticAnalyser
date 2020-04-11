#include "PatternWhileEvaluator.h"

PatternWhileEvaluator::PatternWhileEvaluator() {

}
PatternWhileEvaluator::~PatternWhileEvaluator() {

}

/*
Input: pattern while clause
Output: pattern while clause result 
*/
void PatternWhileEvaluator::evaluatePatternWhile(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	unordered_map<int, int> whilePatternMap = PKB::getPKBInstance()->getWhilePatternMap();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	if (arg1Type == "string") {
		int arg1Num = PKB::getPKBInstance()->getVarID(arg1);
		list<int> possibleWhiles = PKB::getPKBInstance()->getWhilePatternStmtNumber(arg1);
		while (!possibleWhiles.empty()) {
			pair<int, int> result = { possibleWhiles.front(),arg1Num };
			resultList.push_back(result);
			possibleWhiles.pop_front();
		}
	}
	else {
		for (auto it = whilePatternMap.begin(); it != whilePatternMap.end(); it++) {
			pair<int, int> result = { it->first, it->second };
			resultList.push_back(result);
		}
	}
	
}

vector<pair<int, int>> PatternWhileEvaluator::getPatternWhileResultList() {
	return resultList;
}