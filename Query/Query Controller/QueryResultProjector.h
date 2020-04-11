#pragma once

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

#include "../Query Evaluator/EvaluateSelect.h"

using namespace std;

class QueryResultProject {

public:
	QueryResultProject();
	bool getIsNothing();
	void combineResults(vector<unordered_map<string, string>> projectResult);
	list<string> getResult(Query query);
private:
	bool isNothing = false;
	vector<unordered_map<string, string>> intermediateResult;
	vector<unordered_map<string, string>> tempResult;
};
