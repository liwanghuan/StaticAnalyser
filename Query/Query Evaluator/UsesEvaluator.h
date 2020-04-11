#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <list>

using namespace std;

class UsesEvaluator {
public:
	UsesEvaluator();
	~UsesEvaluator();
	vector<pair<int,int>> evaluateUses(Clause clause);
	void evaluateProc(string procedure, string variable, string variableType);
	void evaluateStmt(int stmtNum, string variable, string variableType);
	void clearResultList();
private:
	vector<pair<int, int>> usesResult;
	GetAllSelects getAllSelects;
};

