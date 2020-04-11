#pragma once

#include <vector>
#include <unordered_map>

#include "Declaration.h"
#include "Clause.h"

typedef Declaration Select;

class Query {
private:
	vector<Declaration> declarationList;
	vector<Select> selectList;
	vector<Clause> clauseList;
	unordered_map<string, string> varNameToTypeMap;
public:
	Query();
	void addDeclaration(Declaration);
	void addSelect(Select);
	void addClause(Clause);
	void setVarNameToType(string, string);

	vector<Declaration> getDeclarationList();
	vector<Select> getSelectList();
	vector<Clause> getClauseList();
	string getVarTypeByName(string);
};