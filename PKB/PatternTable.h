#pragma once

#include<unordered_map>
#include<map>
#include <list>

using namespace std;

class PatternTable
{
public:
	PatternTable();
	~PatternTable();

	void setAssignPattern(int, string, string);
	void setWhilePattern(int, int);
	void setIfPattern(int, int);

	list<int> getAssignPatternStmtNumber(int, string);
	list<int> getStmtNoWithString(int, string);

	string getAssignPatternLHS(int);
	string getAssignPatternRHS(int);

	list<int> getIfPatternStmtNumber(int);
	list<int> getWhilePatternStmtNumber(int);

	int getWhilePatternUses(int);
	int getIfPatternUses(int);

	unordered_map<int, int> getWhilePatternMap();
	unordered_map<int, int> getIfPatternMap();
	unordered_map<int, pair<string, string>> getassignPatternMap();

	int getAssignPatternMapSize();
	int getWhilePatternMapSize();
	int getWhilePatternMapReverseSize();
	int getIfPatternMapSize();
	int getIfPatternMapReverseSize();

private:
	unordered_map<int, pair<string, string>> assignPatternMap;
	unordered_map<int, int> whilePatternMap;
	unordered_map<int, int> ifPatternMap;

	unordered_map<int, list<int>> whilePatternMapReverse;
	unordered_map<int, list<int>> ifPatternMapReverse;

	string convertToPostFix(string);
	list<string> tokenizeExpression(string);
	int getPriority(string);
	bool isParenthesis(string);
	bool isOperator(string);
};

