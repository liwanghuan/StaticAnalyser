#pragma once

#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class ParentEvaluator {

public:
	ParentEvaluator();
	~ParentEvaluator();
	vector<pair<int, int>> evaluateParent(Clause clause);
	void clearResultList();

private:
	vector<pair<int, int>> parentResult;
	GetAllSelects getAllSelects;
};

