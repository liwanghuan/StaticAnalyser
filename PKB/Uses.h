#pragma once

#include "VarTable.h"
#include "ProcTable.h"
#include<unordered_map>
#include<list>
#include<string>

using namespace std;

class Uses
{
public:
	Uses();
	~Uses();

	unordered_map<int, list<int>> getStmtUsesMap();
	unordered_map<int, list<int>> getStmtUsesMapReverse();
	unordered_map<int, list<int>> getProcUsesMap();
	unordered_map<int, list<int>> getProcUsesMapReverse();

	void setUses(int, int, int);
	void setStmtUses(int, int);
	void setProcUses(int, int);
	void sortUsesMap();

	list<int> getUses(int);
	list<int> getUsedBy(int);
	bool isUsesValid(int, int);

	list<int> getProcUses(int);
	list<int> getProcUsedBy(int);
	bool isProcUsesValid(int, int);

	int getStmtUsesMapSize();
	int getStmtUsesMapReverseSize();
	int getProcUsesMapSize();
	int getProcUsesMapReverseSize();

private:
	unordered_map<int, list<int>> stmtUsesMap;
	unordered_map<int, list<int>> stmtUsesMapReverse;
	unordered_map<int, list<int>> procUsesMap;
	unordered_map<int, list<int>> procUsesMapReverse;
};

