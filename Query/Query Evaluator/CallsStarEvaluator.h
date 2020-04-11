#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class CallsStarEvaluator {
public:
	CallsStarEvaluator();
	~CallsStarEvaluator();
	vector<pair<int, int>> evaluateCallsStar(Clause clause);

private:
	vector<pair<int, int>> callsStarResult;
	GetAllSelects getAllSelects;
};
