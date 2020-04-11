#include "PatternAssignEvaluator.h"

PatternAssignEvaluator::PatternAssignEvaluator() {

}
PatternAssignEvaluator::~PatternAssignEvaluator() {

}
/*
Input: arg2 and arg2Tyoe
Output: all possible assignment lines
*/
void PatternAssignEvaluator::evaluateSecondArg(string arg2, string arg2Type) {
	unordered_map<int, pair<string, string>> assignMap = PKB::getPKBInstance()->getAssignPatternMap();
	if (arg2Type == "string") {
		arg2List = PKB::getPKBInstance()->getAssignPatternStmtNumber(2, arg2);
	}
	else if (arg2Type == "substring") {
		arg2List = PKB::getPKBInstance()->getStmtNoWithString(2, arg2);
	}
	else if (arg2Type == "all") {
		for (auto it = assignMap.begin(); it != assignMap.end(); it++) {
			arg2List.push_back(it->first);
		}
	}
}

/*
Input: pattern assign clause
Output: answer of main args and first arg
*/
void PatternAssignEvaluator::evaluatePatternAssign(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	unordered_map<int, pair<string, string>> assignMap = PKB::getPKBInstance()->getAssignPatternMap();
	evaluateSecondArg(arg2, arg2Type);

	while (!arg2List.empty()) {
		int current = arg2List.front();
		arg2List.pop_front();
		string currentVarName = PKB::getPKBInstance()->getAssignPatternLHS(current);
		int currentVarID = PKB::getPKBInstance()->getVarID(currentVarName);
		if (arg1Type == "variable" || arg1Type == "all") {// all variables are valid
			pair<int, int> result = { current, currentVarID};
			resultList.push_back(result);
		}
		else if (arg1Type == "string") {
			if (arg1 == currentVarName) {// only if matches valid 
				pair<int, int> result = { current, currentVarID};
				resultList.push_back(result);
			}
		}
	}
}

/*
TODO: return all pattern assign answers
*/
vector<pair<int,int>> PatternAssignEvaluator::getPatternAssignResultList() {
	return resultList;
}