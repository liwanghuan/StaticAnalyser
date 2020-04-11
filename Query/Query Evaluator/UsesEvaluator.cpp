#include "UsesEvaluator.h"
UsesEvaluator::UsesEvaluator() {

}

UsesEvaluator::~UsesEvaluator() {

}
/*
Input: procedurem, second var name and var type
TODO: evaluate proc uses
*/
void UsesEvaluator::evaluateProc(string procedure, string variable, string variableType) {
	list<int> allVariables = PKB::getPKBInstance()->getProcUsedBy(procedure);
	int procID = PKB::getPKBInstance()->getProcID(procedure);
	if (variableType == "string") {
		int varID = PKB::getPKBInstance()->getVarID(variable);
		if (find(allVariables.begin(), allVariables.end(), varID) != allVariables.end()) {
			pair<int, int> result = { procID, varID };
			usesResult.push_back(result);
		}
	}
	else {
		while (!allVariables.empty()) {
			int current = allVariables.front();
			allVariables.pop_front();
			pair<int, int> result = {procID, current};
			usesResult.push_back(result);
		}
	}
}

/*
Input: stmt number, second vaeType and varName
TODO: evaluate stmt uses
*/
void UsesEvaluator::evaluateStmt(int stmtNum, string variable, string variableType) {
	list<int> allVariables = PKB::getPKBInstance()->getUsedBy(stmtNum);
	if (variableType == "string") {
		int varID = PKB::getPKBInstance()->getVarID(variable);
		// check whether Uses valid
		if (find(allVariables.begin(),allVariables.end(),varID)!= allVariables.end()) {
			pair<int, int> result = { stmtNum, varID};
			usesResult.push_back(result);
		}
	}
	else {
		while (!allVariables.empty()) {
			int current = allVariables.front();
			allVariables.pop_front();
			pair<int, int> result = { stmtNum,current};
			usesResult.push_back(result);
		}
	}
}

/*
Input: uses clause
Output: uses answers
*/
vector<pair<int,int>> UsesEvaluator::evaluateUses(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();

	if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {
		return usesResult;
	}
	if (arg1Type == "string") {// must be proc name
		evaluateProc(arg1, arg2, arg2Type);
	}
	else if (arg1Type == "procedure") {
		for (int i = 1; i <= PKB::getPKBInstance()->getProcTableSize(); i++) {
			string procName = PKB::getPKBInstance()->getProcName(i);
			evaluateProc(procName, arg2, arg2Type);
		}
	}
	else if (arg1Type == "number") {
		int stmtNum = atoi(arg1.c_str());
		evaluateStmt(stmtNum, arg2, arg2Type);
	}
	else {
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
		for (int i = 0; i < allPossibleArg1.size(); i++) {
			int stmtNum = allPossibleArg1.at(i);
			evaluateStmt(stmtNum, arg2, arg2Type);
			
		}
	}

	return usesResult;
}


void UsesEvaluator::clearResultList() {
	usesResult.clear();
}
