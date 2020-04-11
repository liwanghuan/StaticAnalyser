#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class WithStringEvaluator {
public:
	WithStringEvaluator();
	~WithStringEvaluator();

	vector<string> evaluateOneSide(string arg, string argType);
	void evaluateWithString(Clause clause);
	vector<pair<int, int>> getWithStringResult();
private:
	vector<pair<int, int>> withStringResult;
	GetAllSelects getAllSelects;
};