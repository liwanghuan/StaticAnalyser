#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class ParentStarEvaluator {
public:
	ParentStarEvaluator();
	~ParentStarEvaluator();
	vector<pair<int, int>> evaluateParentStar(Clause clause);
	void clearResultList();
private:
	vector<pair<int, int>> parentStarResult;
	GetAllSelects getAllSelects;
};
