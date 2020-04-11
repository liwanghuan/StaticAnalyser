#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class ModifiesEvaluator {
public:
	ModifiesEvaluator();
	~ModifiesEvaluator();
	vector<pair<int, int>> evaluateModifies(Clause clause);
	void evaluateProc(string procedure, string variable, string variableType);
	void evaluateStmt(int stmtNum, string variable, string variableType);
	void clearResultList();

private:
	vector<pair<int, int>> modifiesResult;
	GetAllSelects getAllSelects;
};
