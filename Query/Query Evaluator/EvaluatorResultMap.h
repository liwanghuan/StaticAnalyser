#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

#include "../Query Processor/Clause.h"

using namespace std;
class EvaluatorResultMap{
	
public:
	EvaluatorResultMap();
	~EvaluatorResultMap();
	bool isKnown(string argType);
	void combineClauseResult(Clause clause, vector<pair<int, int>> clauseResult);
	void combineSingleResult(string var, vector<int> singleResultList);
	void combineDoubleResults(string arg1, string arg2, vector<pair<int, int>> clauseResult);
	vector<unordered_map<string, int>> getResultMap();
	bool getIsNothing();
private:
	vector<unordered_map<string, int>> resultMap;
	vector< unordered_map<string, int>> tempMap;
	bool isNothing = false;
};
