#include "QueryOptimizer.h"

QueryOptimizer::QueryOptimizer()
{
}

vector<Query> QueryOptimizer::optimizeQuery(Query query) {
	vector<Clause> clauses = query.getClauseList();
	vector<Select> selects = query.getSelectList();

	createMaps(clauses);
	vector<ClauseGroup> clauseGroups = groupClauses(clauses);
	vector<Query> temp3 = createQueries(selects, clauseGroups);

	return temp3;
}

//Puts clauses into their respective groups based on common synonyms between clauses
vector<ClauseGroup> QueryOptimizer::groupClauses(vector<Clause> clauses) {
	vector<ClauseGroup> result = {};
	if (clauses.size() > 0) {
		ClauseGroup clauseGroup;
		clauseGroup.addClause(clauseMap.find(0)->second, variableMap.find(0)->second);
		result.push_back(clauseGroup);
	}
	for (int i = 1; i < clauses.size(); i++) {
		int added = -1;
		for (int j = 0; j < result.size(); j++) {
			if (result.at(j).checkVariables(variableMap.find(i)->second)) {
				result.at(j).addClause(clauseMap.find(i)->second, variableMap.find(i)->second);
				added = j;
				break;
			}
		}
		if (added == -1) {
			ClauseGroup temp;
			temp.addClause(clauseMap.find(i)->second, variableMap.find(i)->second);
			result.push_back(temp);
			if (temp.getVariableIDs().size() == 0) {
				added = true;
			}
		}
		if (added != -1) {
			for (int h = 0; h < result.size(); h++) {
				if (result.at(added).compareClauseGroup(result.at(h)) && h != added) {
					result.at(added).combineClauseGroup(result.at(h));
					result.erase(result.begin() + h);
				}
			}
		}
	}
	return result;
}

//Places clauses and variabels into a map for easier retrieval when grouping clauses
void QueryOptimizer::createMaps(vector<Clause> clauses) {
	for (int i = 0; i < clauses.size(); i++) {
		vector<string> variables = checkVariables(clauses.at(i));
		variableMap[i] = variables;
		clauses.at(i).setVariables(variables);
		clauseMap[i] = clauses.at(i);
	}
}

//To check if the variables in a clause are variables
vector<string> QueryOptimizer::checkVariables(Clause clause) {
	vector<string> temp;
	temp = {};
	if (checkIfVariable(clause.getMainArgType())) {
		temp.push_back(clause.getMainArg());
	}
	if (checkIfVariable(clause.getFirstArgType())) {
		temp.push_back(clause.getFirstArg());
	}
	if (checkIfVariable(clause.getSecondArgType())) {
		temp.push_back(clause.getSecondArg());
	}
	return temp;
}

//To check if the variables in a with clause are variables
bool QueryOptimizer::checkIfVariable(string toCheck) {
	if (toCheck != "number" &&
		toCheck != "substring" &&
		toCheck != "string" &&
		toCheck != "all" &&
		toCheck != "") {
		return true;
	}
	return false;
}

//Packages each clause group into a query. If there are selects in the original query that are
//not in any query, they will have their own query created with no claues inside. Clause groups
//with no selects will have a "Select boolean" created for them
vector<Query> QueryOptimizer::createQueries(vector<Select> selects, vector<ClauseGroup> groups) {
	vector<Query> result;
	Query temp;
	bool done = false;

	for (int j = 0; j < selects.size(); j++) {
		bool added = false;
		for (int i = 0; i < groups.size(); i++) {
			if (groups.at(i).checkSelect(selects.at(j))) {
				groups.at(i).addSelect(selects.at(j));
				added = true;
				break;
			}
		}
		if (selects.at(j).getVarType() != "boolean" && added == false) {
			Query tempQuery;
			tempQuery.addSelect(selects.at(j));
			result.push_back(tempQuery);
		}
	}

	for (int k = 0; k < groups.size(); k++) {
		temp = groups.at(k).toQuery();
		if (temp.getSelectList().at(0).getVarType() != "boolean") {
			result.push_back(temp);
		}
		else {
			result.insert(result.begin(), temp);
		}
	}
	
	return result;
}