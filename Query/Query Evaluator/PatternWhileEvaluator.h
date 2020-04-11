#pragma once
#include "../Query Processor/Clause.h"
#include "../../PKB/PKB.h"

#include <list>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class PatternWhileEvaluator {
public:
	PatternWhileEvaluator();
	~PatternWhileEvaluator();
	void evaluatePatternWhile(Clause clause);
	vector<pair<int, int>> getPatternWhileResultList();

private:
	vector<pair<int, int>> resultList;
};