#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class WithConstantEvaluator {
public:
	WithConstantEvaluator();
	~WithConstantEvaluator();

	void evaluateWithConstant(Clause clause);
	vector<pair<int, int>> getWithConstantResult();
private:
	vector<pair<int, int>> withConstantResult;
	GetAllSelects getAllSelects;
};