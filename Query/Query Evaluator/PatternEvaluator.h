#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class PatternEvaluator {
public:
	PatternEvaluator();
	~PatternEvaluator();
	vector<int> evaluateFirstArgument(string arg1, string arg1Type);
	vector<int> evaluateSecondArgument(string arg2, string arg2Type);
	vector<pair<int, int>>evaluatePattern(Clause caluse);
	void clearResultList();

private:
	vector<pair<int, int>> patternResult;
	GetAllSelects getAllSelects;
};
