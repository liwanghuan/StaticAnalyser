#include "QueryTree.h"
#include <string>

using namespace std;

QueryTree::QueryTree() {
	queryTree.push_back(variableTree);
	queryTree.push_back(suchThatTree);
	queryTree.push_back(patternTree);
	queryTree.push_back(selectTree);
}


// To insert the query into its respective tree
void QueryTree::insertSuchThat(string relationship, vector<string> variableArr, vector<string> argumentTypeArr) {
	vector<string> suchThatArr;

	string variableFront = variableArr.at(0), variableEnd = variableArr.at(1);
	string argTypeFront = argumentTypeArr.at(0), argTypeEnd = argumentTypeArr.at(1);

	suchThatArr.push_back(relationship);
	suchThatArr.push_back(variableFront);
	suchThatArr.push_back(argTypeFront);
	suchThatArr.push_back(variableEnd);
	suchThatArr.push_back(argTypeEnd);

	queryTree.at(1).push_back(suchThatArr);
}

void QueryTree::insertPattern(string synonym, string synonymType, vector<string> patternArr, vector<string> patternTypeArr) {
	vector<string> patternArrTemp;

	string patternFront = patternArr.at(0), patternEnd = patternArr.at(1);
	string patternTypeFront = patternTypeArr.at(0), patternTypeEnd = patternTypeArr.at(1);

	patternArrTemp.push_back(synonym);
	patternArrTemp.push_back(synonymType);
	patternArrTemp.push_back(patternFront);
	patternArrTemp.push_back(patternTypeFront);
	patternArrTemp.push_back(patternEnd);
	patternArrTemp.push_back(patternTypeEnd);

	queryTree.at(2).push_back(patternArrTemp);
}

void QueryTree::insertVariable(string variable, string variableType) {
	vector<string> variableArr;
	variableArr.push_back(variable);
	variableArr.push_back(variableType);
	queryTree.at(0).push_back(variableArr);
}

void QueryTree::insertSelect(string variable, string variableType) {
	vector<string> selectArr;
	selectArr.push_back(variable);
	selectArr.push_back(variableType);
	queryTree.at(3).push_back(selectArr);
}

// To get query for the respective query types at specific clause
vector<vector<string>> QueryTree::getSuchThatQuery() {
	return queryTree.at(1);
}

vector<vector<string>> QueryTree::getPatternQuery() {
	return queryTree.at(2);
}

vector<vector<string>> QueryTree::getVariableQuery() {
	return queryTree.at(0);
}

vector<vector<string>> QueryTree::getSelectQuery() {
	return queryTree.at(3);
}

vector<string> QueryTree::getSuchThatQueryTree(int qPosition)
{
	return queryTree.at(1).at(qPosition);
}

vector<string> QueryTree::getPatternQueryTree(int qPosition)
{
	return queryTree.at(2).at(qPosition);
}

vector<string> QueryTree::getVariableQueryTree(int qPosition)
{
	return queryTree.at(0).at(qPosition);
}

vector<string> QueryTree::getSelectQueryTree(int qPosition)
{
	return queryTree.at(3).at(qPosition);
}

// To print tree for checking
void QueryTree::printTree() {
	//cout << "===============Print tree start===============\n";
	for (vector<vector<vector<string>>>::const_iterator i = queryTree.begin(); i != queryTree.end(); ++i)
	{
		for (vector<vector<string>>::const_iterator j = i->begin(); j != i->end(); ++j)
		{
			for (vector<string>::const_iterator k = j->begin(); k != j->end(); ++k)
			{
				//cout << *k << ' ';
			}
		}
	}
	//cout << "\n===============print tree end===============\n";
}