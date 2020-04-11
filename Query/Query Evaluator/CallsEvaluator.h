#pragma once
#include "../../PKB/PKB.h"
#include "getAllSelects.h"
#include "../Query Processor/Clause.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class CallsEvaluator {
public:
	CallsEvaluator();
	~CallsEvaluator();
	vector<pair<int, int>> evaluateCalls(Clause clause);
private:
	vector<pair<int, int>> callsResult;
};
