#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class AffectsEvaluator {
public:
	AffectsEvaluator();
	~AffectsEvaluator();
	vector<pair<int, int>> evaluateAffects(Clause clause);
private:
	vector<pair<int, int>> affectsResult;
	GetAllSelects getAllSelects;
};


