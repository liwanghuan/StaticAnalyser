#include "Query.h"
Query::Query() {

}
void Query::addDeclaration(Declaration declaration) {
	declarationList.push_back(declaration);
}

void Query::addSelect(Select select) {
	selectList.push_back(select);
}

void Query::addClause(Clause clause) {
	clauseList.push_back(clause);
}

void Query::setVarNameToType(string name, string type) {
	varNameToTypeMap[name] = type;
}

vector<Declaration> Query::getDeclarationList() {
	return declarationList;
}

vector<Select> Query::getSelectList() {
	return selectList;
}

vector<Clause> Query::getClauseList() {
	return clauseList;
}

string Query::getVarTypeByName(string name)
{
	auto it = varNameToTypeMap.find(name);
	if (it == varNameToTypeMap.end()) {
		return ""; // shouldn't reach this line and return empty string
	}
	string type = it->second;
	return type;
}
