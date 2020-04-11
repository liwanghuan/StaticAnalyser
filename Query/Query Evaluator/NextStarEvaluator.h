#pragma once

#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class NextStarEvaluator {
public:
	NextStarEvaluator();
	~NextStarEvaluator();
	vector<pair<int, int>> evaluateNextStar(Clause clause);
private:
	vector<pair<int, int>> nextStarResult;
	GetAllSelects getAllSelects;
};

