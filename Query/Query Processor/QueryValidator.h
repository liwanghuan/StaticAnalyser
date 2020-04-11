#pragma once

#include <string>
#include <list>
#include <vector>
#include <unordered_map>

#include "RelationshipTable.h"
#include "QueryTree.h"
#include "../Query Evaluator/QueryEvaluator.h"

#include "Query.h";
#include "Clause.h";
#include "Declaration.h";

using namespace std;

class QueryValidator {
private:
	bool isValidDeclaration(string declaration);
	bool isValidQuery(string query);

	bool specialSelection(vector<string> specialSelection);

	bool findSuchThatClause(string &subquery);
	bool findSuchThatClauseArguments(string relationshipType, vector<string> &variableArr, vector<string> &variableType);

	bool findPatternClause(string &subquery);
	bool findPatternType(string word, string &relationshipType, string &synonym, string &synonymType);
	bool findPatternArgs1(string relationshipType, string &args1, string &variableType);
	bool findPatternArgs2_Assign(string relationshipType, string &subquery, string &variableType);
	bool findPatternArgs2_WhileAndIf(string relationshipType, string &subquery, string &variableType);

	bool findWithClause(string &subquery);
	bool findWithClauseConstant(string &subquery, string &relationshipType, vector<string> &variableArr, vector<string> &variableType);
	bool findWithClauseString(string &subquery, string &relationshipType, vector<string> &variableArr, vector<string> &variableType);

	// Helper methods
	vector<string> split(string str, char c);
	vector<string> split(string str, char c, int num);
	string toLower(string str);
	string trim(string query);

	bool isVariableNameExists(string variableName);
	bool isValidVariableName(string variableName);
	string getVariableType(string variableType);
	bool isString(string variableStr);
	bool isInteger(string content);
	string getStringContents(string word);

	int numOfLeftBrackets(string stmt);
	int numOfRightBrackets(string stmt);

	void clearDeclarationObject(void);
	void clearSelectObject(void);
	void clearClauseObject(void);

	// Data structures
	unordered_map<string, string> map;
	RelationshipTable relationshipTable;

	// For storing tokenized queries into their respective objects
	Query queryObj;
	Declaration declarationObj;
	Select selectObj;
	Clause clauseObj;

public:
	string isValidDeclarationAndQuery(string query);
	Query getQuery();

	// For debugging purposes
	void printQuery(string subquery);
};