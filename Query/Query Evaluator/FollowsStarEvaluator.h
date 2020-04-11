#pragma once

#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class FollowsStarEvaluator {
public:
	FollowsStarEvaluator();
	~FollowsStarEvaluator();
	vector<pair<int, int>> evaluateFollowsStar(Clause clause);
	void clearResultList();
private:
	vector<pair<int, int>> followsStarResult;
	GetAllSelects getAllSelects;
};
