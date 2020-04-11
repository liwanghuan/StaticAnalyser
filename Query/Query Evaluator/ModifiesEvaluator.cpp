#include "ModifiesEvaluator.h"

ModifiesEvaluator::ModifiesEvaluator() {

}

ModifiesEvaluator::~ModifiesEvaluator() {

}
/*
Input: procName variable and varType
TO DO: crteate all answers of such type of modify 
*/
void ModifiesEvaluator::evaluateProc(string procedure,  string variable, string variableType) {
	list<int> insideProc = PKB::getPKBInstance()->getProcModifiedBy(procedure);
	int procID = PKB::getPKBInstance()->getProcID(procedure);
	if (variableType == "string") {
		int varNum = PKB::getPKBInstance()->getVarID(variable);
		if (find(insideProc.begin(),insideProc.end(),varNum) != insideProc.end()) {
			pair<int, int> result = { procID, varNum };
			modifiesResult.push_back(result);
		}
	}
	else {
		while (!insideProc.empty()) {
			int current = insideProc.front();
			insideProc.pop_front();
			pair<int, int> result = { procID,current };
			modifiesResult.push_back(result);
		}
	}
}
/*
Input: stmtLine number, variable and varType
TODO: create answers of such type of modifies
*/
void ModifiesEvaluator::evaluateStmt(int stmtNum, string variable, string variableType) {
	list<int> allVariables = PKB::getPKBInstance()->getModifiedBy(stmtNum);
	if (variableType == "string") {
		int varID = PKB::getPKBInstance()->getVarID(variable);
		// check whether modifies valid
		if (find(allVariables.begin(),allVariables.end(),varID) != allVariables.end()) {
			pair<int, int> result = { stmtNum, varID };
			modifiesResult.push_back(result);
		}
	}
	else {
		while (!allVariables.empty()) {
			int current = allVariables.front();
			allVariables.pop_front();
			pair<int, int> result = {stmtNum, current};
			modifiesResult.push_back(result);
		}
	}
}
/*
	Input: modifies clause
	Output: answers of this clause
*/
vector<pair<int, int>> ModifiesEvaluator::evaluateModifies(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	if (arg1 == arg2 && arg1Type == arg2Type&&arg1 != "_") {
		return modifiesResult;
	}

	if (arg1Type == "string") {// string must be proc name
		evaluateProc(arg1, arg2, arg2Type);
	}
	else if (arg1Type == "procedure") {
		for (int i = 1; i <= PKB::getPKBInstance()->getProcTableSize(); i++) {
			string procName = PKB::getPKBInstance()->getProcName(i);
			evaluateProc(procName, arg2, arg2Type);
		}
	}
	else if (arg1Type == "number") {// known progline
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
	return modifiesResult;
}

void ModifiesEvaluator::clearResultList() {
	modifiesResult.clear();
}