#pragma once

#include <unordered_map>

#include "../Query Processor/Clause.h"
#include "../Query Processor/Query.h"

class ClauseGroup {

private:

	vector<Clause> clauses;
	unordered_map<string,bool> variableIDs;
	vector<int> score;
	vector<Select> selects;

public:

	ClauseGroup();
	void addClause(Clause, vector<string>);
	void addSelect(Select);
	void combineClauseGroup(ClauseGroup clauseGroup);
	bool compareClauseGroup(ClauseGroup clauseGroup);
	void sortGroup();
	unordered_map<string, bool> getVariableIDs();
	vector<Clause> getClauses();
	bool checkVariables(vector<string> variables);
	bool checkSelect(Select select);
	Query toQuery();
	void toTrue(vector<string> variables);
	
};