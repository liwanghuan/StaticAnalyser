#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class QueryTree {
public:
	QueryTree();

	// Insert the relationships of the query in their respective trees here
	void insertSuchThat(string relationship, vector<string> variableArr, vector<string> argumentTypeArr);
	void insertPattern(string synonym, string synonymType, vector<string> patternArr, vector<string> patternTypeArr);
	void insertVariable(string variable, string variableType);
	void insertSelect(string variable, string variableType);

	// To get a specific tree
	// For WH
	vector<vector<string>> getSuchThatQuery();
	vector<vector<string>> getPatternQuery();
	vector<vector<string>> getVariableQuery();
	vector<vector<string>> getSelectQuery();

	// For validator to obtain information of specific relationship in a specific clause
	vector<string> getSuchThatQueryTree(int qPosition);
	vector<string> getPatternQueryTree(int qPosition);
	vector<string> getVariableQueryTree(int qPosition);
	vector<string> getSelectQueryTree(int qPosition);

	void printTree();

private:
	vector<vector<vector<string>>> queryTree;
	vector<vector<string>> suchThatTree;
	vector<vector<string>> patternTree;
	vector<vector<string>> withTree;
	vector<vector<string>> variableTree;
	vector<vector<string>> selectTree;
};