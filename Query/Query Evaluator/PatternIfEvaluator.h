#pragma once
#include "../Query Processor/Clause.h"
#include "../../PKB/PKB.h"

#include <list>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class PatternIfEvaluator {
public:
	PatternIfEvaluator();
	~PatternIfEvaluator();
	void evaluatePatternIf(Clause clause);
	vector<pair<int, int>> getPatternIfResultList();

private:
	vector<pair<int, int>> resultList;
};
