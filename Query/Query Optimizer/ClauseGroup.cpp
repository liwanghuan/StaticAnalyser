#include "ClauseGroup.h"

ClauseGroup::ClauseGroup() {
	variableIDs = {};
	clauses = {};
	score = {};
	selects = {};
}

//Adds a clause in the the clause group. If it has less unknowns than the current 
//first clause and is not affects, it will replace the current first clause, else
//it will be placed at the back
void ClauseGroup::addClause(Clause clause, vector<string> newVariables) {
	if (clauses.size() == 0) {
		clauses.push_back(clause);
	}
	else {
		vector<string> clauseVariables = clause.getVariables();
		if (clauses.at(0).getVariables().size() > clauseVariables.size() && clauses.at(0).getClauseType() == "affects" || clauses.at(0).getClauseType() == "affects*") {
			clauses.insert(clauses.begin(), clause);
		}
		else {
			clauses.push_back(clause);
		}
	}
	for (int i = 0; i < newVariables.size(); i++) {
		variableIDs[newVariables.at(i)] = false;
	}
}

//Combines two clause groups togther, the first clauses from both groups will be compared
//to make sure that the first clause in the new group continues to mantain the standards stated above in
//addClause
void ClauseGroup::combineClauseGroup(ClauseGroup clauseGroup) {
	unordered_map<string, bool> variables = clauseGroup.getVariableIDs();
	vector<Clause> newClauses = clauseGroup.getClauses();
	variableIDs.insert(variables.begin(), variables.end());
	if (clauses.at(0).getVariables().size() > newClauses.at(0).getVariables().size() && clauses.at(0).getClauseType() == "affects" || clauses.at(0).getClauseType() == "affects*") {
		clauses.insert(clauses.begin(), newClauses.at(0));
		clauses.insert(clauses.end(), newClauses.begin()+1, newClauses.end());
	}
	else {
		clauses.insert(clauses.end(), newClauses.begin(), newClauses.end());
	}
}

//Compares two clausegroups to see if they should be combined returns true if they should
bool ClauseGroup::compareClauseGroup(ClauseGroup clauseGroup) {
	unordered_map<string, bool> variables = clauseGroup.getVariableIDs();
	unordered_map<string, bool>::iterator it = variables.begin();

	while (it != variables.end()) {
		unordered_map<string, bool>::iterator find = variableIDs.find(it->first);
		if (find != variableIDs.end()) {
			return true;
		}
		it++;
	}

	if (variables.size() == 0 && variableIDs.size() == 0) {
		return true;
	}
	return false;
}

//Sorts the clauses in the  clause group starting from the first clause, subsequent clauses
//will have the common synonyms.
void ClauseGroup::sortGroup() {
	vector<Clause> sorted = { clauses.at(0) };
	clauses.erase(clauses.begin());
	int counter = 0;
	bool added = false;
	for (int i = 0; i < sorted.at(0).getVariables().size(); i++) {
		variableIDs[sorted.at(0).getVariables().at(i)] = true;
	}
	while (clauses.size() != 0) {
		for (int j = 0; j < clauses.at(counter).getVariables().size(); j++) {
			if (variableIDs[clauses.at(counter).getVariables().at(j)] == true) {
				sorted.push_back(clauses.at(counter));
				toTrue(clauses.at(counter).getVariables());
				clauses.erase(clauses.begin() + counter);
				added = true;
				break;
			}
		}
		if (added) {
			added = false;
			counter = 0;
		}
		else {
			counter++;
		}
	}
	clauses = sorted;
}

//Check if any of the variables in the input are present in the clause group
bool ClauseGroup::checkVariables(vector<string> variables) {
	bool result = false;
	for (int i = 0; i < variables.size(); i++) {
		unordered_map<string, bool>::iterator find = variableIDs.find(variables.at(i));
		if (find != variableIDs.end()) {
			result = true;
		}
	}
	return result;
}

//Check if the input select selects any on the variables in the clause group if yes, reutrn true
bool ClauseGroup::checkSelect(Select select) {
	bool result = false;
	unordered_map<string, bool>::iterator find = variableIDs.find(select.getVarName());
	if (find != variableIDs.end()) {
		result = true;
	}
	return result;
}

//Returns a query object with all the clauses and selects in the clause group
Query ClauseGroup::toQuery() {
	Query result;
	Select boole;
	boole.setVarType("boolean");
	for (int i = 0; i < selects.size(); i++) {
		result.addSelect(selects[i]);
	}
	if (variableIDs.size() != 0) {
		sortGroup();
	}
	for (int j = 0; j < clauses.size(); j++) {
		result.addClause(clauses.at(j));
	}
	if (result.getSelectList().size() == 0) {
		result.addSelect(boole);
	}
	return result;
}

//Converts all input variables to true in the variable map, for easier clause group sorting
void ClauseGroup::toTrue(vector<string> variables) {
	for (int i = 0; i < variables.size(); i++) {
		variableIDs[variables.at(i)] = true;
	}
}

//Return all variables present in the clause group
unordered_map<string, bool> ClauseGroup::getVariableIDs() {
	return variableIDs;
}

//Return all clauses present in the clause group
vector<Clause> ClauseGroup::getClauses() {
	return clauses;
}


void ClauseGroup::addSelect(Select select) {
	selects.push_back(select);
}