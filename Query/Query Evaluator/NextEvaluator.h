#pragma once

#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class NextEvaluator {
public:
	NextEvaluator();
	~NextEvaluator();
	vector<pair<int, int>> evaluateNext(Clause clause);
private:
	vector<pair<int, int>> nextResult;
	GetAllSelects getAllSelects;
};



