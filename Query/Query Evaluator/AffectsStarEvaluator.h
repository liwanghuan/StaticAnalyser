#pragma once

#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class AffectsStarEvaluator {
public:
	AffectsStarEvaluator();
	~AffectsStarEvaluator();
	vector<pair<int, int>> evaluateAffectsStar(Clause clause);

private:
	vector<pair<int, int>> affectsStarResult;
	GetAllSelects getAllSelects;
};



