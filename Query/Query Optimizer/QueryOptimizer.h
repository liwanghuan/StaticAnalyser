#pragma once

#include <vector>
#include <unordered_map>

#include "../Query Processor/Query.h"
#include "../Query Optimizer/ClauseGroup.h"

typedef Declaration Select;

class QueryOptimizer {
private:
	unordered_map<int, Clause> clauseMap;
	unordered_map<int, vector<string>> variableMap;
	vector<ClauseGroup> groupClauses(vector<Clause> clauses);
	void createMaps(vector<Clause> clauses);
	vector<string> checkVariables(Clause clause);
	bool checkIfVariable(string toCheck);
	vector<Query> createQueries(vector<Select> select, vector<ClauseGroup> groups);
public:
	QueryOptimizer();
	vector<Query> optimizeQuery(Query);
};
