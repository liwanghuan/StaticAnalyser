#pragma once
#include "../Query Processor/Clause.h"
#include "../../PKB/PKB.h"

#include <list>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class PatternAssignEvaluator {
public:
	PatternAssignEvaluator();
	~PatternAssignEvaluator();
	void evaluatePatternAssign(Clause clause);
	vector<pair<int, int>> getPatternAssignResultList();
	void evaluateSecondArg(string arg2, string arg2Type);

private:
	vector<pair<int, int>> resultList;
	list<int> arg2List;
};