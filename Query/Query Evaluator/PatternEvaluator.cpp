#include "PatternEvaluator.h"

PatternEvaluator::PatternEvaluator() {

}

PatternEvaluator::~PatternEvaluator() {

}

vector<int> PatternEvaluator:: evaluateFirstArgument(string arg1, string arg1Type) {
	vector<int> result;
	if (arg1Type == "string") {
		arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
		result.push_back(PKB::getPKBInstance()->getVarID(arg1));
	}
	else {
		for (int i = 1; i <= PKB::getPKBInstance()->getVarTableSize(); i++) {
			result.push_back(i);
		}
	}

	return result;
}

vector<int> PatternEvaluator::evaluateSecondArgument(string arg2, string arg2Type) {
	cout << "arg2 is " << arg2 << endl;
	cout << "arg2Type is " << arg2Type << endl;
	map<int, pair<string, string>> assignTable = PKB::getPKBInstance()->getAssignPatternMap();
	vector<int> result;
	if (arg2Type == "all") {
		for (int i = 1; i <= PKB::getPKBInstance()->getTotalNumOfProgLine(); i++) {
			result.push_back(i);
		}
	}
	else if (arg2Type == "substring") {
		arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
		cout << "After remove white space, the new arg2 string is " << arg2 << endl;
		list<int> allStmts = PKB::getPKBInstance()->getStmtNoWithString(2,arg2);
		cout << "inside arg2, the result size is " << allStmts.size() << endl;
		while (!allStmts.empty())
		{
			result.push_back(allStmts.front());
			allStmts.pop_front();
		}
	}
	else if (arg2Type == "string") {
		arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
		for (auto it = assignTable.begin(); it != assignTable.end(); it++)
		{
			if (it->second.second == arg2) {
				result.push_back(it->first);
			}
		}
	}
	return result;
}
vector<pair<int, int>> PatternEvaluator::evaluatePattern(Clause clause) {
	string synoName = clause.getMainArg();
	string synoType =clause.getMainArgType();
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();

	if (arg1 == arg2 && arg1Type == arg2Type && arg1!="_") {
		return patternResult;
	}
	cout << "Start evaluate arg1" << endl;
	vector<int> arg1List = evaluateFirstArgument(arg1, arg1Type);
	cout << "arg1List size is" << arg1List.size() << endl;
	cout << "start evaluate arg2" << endl;
	vector<int> arg2List = evaluateSecondArgument(arg2, arg2Type);
	cout << "arg2List size is " <<arg2List.size()<< endl;
	map<int, pair<string, string>> assignTable = PKB::getPKBInstance()->getAssignPatternMap();
	map<int,int> whileTable = PKB::getPKBInstance()->getWhilePatternMap();

	if (synoType == "assign" || synoType == "stmt") {
		vector<int> tempList;
		cout << "inside assign, start combine synonym and arg2" << endl;
		// Firstly combine syno and second Arg, get result inside tempList 
		for (int i = 0; i < arg2List.size(); i++) {
			int possibleStmt = arg2List.at(i);
			if (assignTable.find(possibleStmt) != assignTable.end()) {
				tempList.push_back(possibleStmt);
			}
		}
		cout << "start combine synonym and arg1" << endl;
		// second combine tempList and firstArgument
		for (int i = 0; i < tempList.size(); i++) {
			int possibleStmt = tempList.at(i);
			int varID = PKB::getPKBInstance()->getVarID(assignTable[possibleStmt].first);
			if (find(arg1List.begin(), arg1List.end(), varID) != arg1List.end()) {
				pair<int, int> result = { possibleStmt,varID };
				patternResult.push_back(result);
			}
		}

	}
	else if (synoType == "while"){
		arg1.erase(remove(arg1.begin(),arg1.end(),' '), arg1.end());
		int varID = PKB::getPKBInstance()->getVarID(arg1);
		for (auto it = whileTable.begin(); it != whileTable.end(); it++) {
			if (it->second == varID) {
				pair<int, int> result = {it->first, it->second};
				patternResult.push_back(result);
			}
		}
	}
	else {// if

	}

	return patternResult;
}

void PatternEvaluator::clearResultList() {
	patternResult.clear();
}
