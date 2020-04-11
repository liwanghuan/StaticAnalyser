#pragma once

#include <list>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <regex>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "CFGNode.h"
#include "Statement.h"

using namespace std;

class CFG
{
public:

	CFG();
	unordered_map<int, list<int>> nextCfgNode;
	unordered_map<int, list<int>> nextTable;
	unordered_map<int, list<int>> previousTable;
	unordered_map<int, list<int>> nextStarTable;
	unordered_map<int, list<int>> previousStarTable;

	void clearStarMap();

	vector<string> typeTable;
	unordered_map<int, int> procMap;
	vector<int> procTable;
	unordered_map<int, CFGNode*> nodeMap;

	vector<Statement>::iterator codeIterator;
	vector<Statement> codeLst;
	stack<pair<int, string>> nodeInOperation;
	vector<int> statBuffer;

	int nodeIndex;
	int size;
	int currentProcCount;
	bool isProcFirstStmt;

	int getProcFirstStmt(int);
	int getProcMap(int);

	void buildCFG(vector<Statement>);

	list<int> getNext(int);
	list<int> getPrevious(int);
	bool isNextValid(int, int);

	list<int> getNextStar(int);
	list<int> getPreviousStar(int);
	bool isNextStarValid(int, int);

private:
	int createNormalStmtNode();
	int createContainerNode(int);
	int createDummyNode();
	int insertNode(CFGNode*);
	list<int> traverse(int, unordered_map<int, list<int>>);
	void solveCode();
	void solveNode(int, string);
	void initializeStack();
	void insertNext(int, int);
	void insertPreviousTable(int, int, unordered_map<int, list<int>>&);
	void storeTable();
};