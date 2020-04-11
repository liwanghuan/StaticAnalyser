#pragma once

#include "VarTable.h"
#include "ProcTable.h"
#include<unordered_map>
#include<list>
#include<string>

using namespace std;

class Modifies{

public:
	Modifies();
	~Modifies();

	unordered_map<int, list<int>> getStmtModifiesMap();
	unordered_map<int, list<int>> getStmtModifiesMapReverse();
	unordered_map<int, list<int>> getProcModifiesMap();
	unordered_map<int, list<int>> getProcModifiesMapReverse();

	void setModifies(int, int, int);
	void setStmtModifies(int, int);
	void setProcModifies(int, int);
	void sortModifiesMap();

	list<int> getModifies(int);
	list<int> getModifiedBy(int);
	bool isModifiesValid(int, int);

	list<int> getProcModifies(int);
	list<int> getProcModifiedBy(int);
	bool isProcModifiesValid(int, int);
	
	int getStmtModifiesMapSize();
	int getStmtModifiesMapReverseSize();
	int getProcModifiesMapSize();
	int getProcModifiesMapReverseSize();

private:
	unordered_map<int, list<int>> stmtModifiesMap;
	unordered_map<int, list<int>> stmtModifiesMapReverse;
	unordered_map<int, list<int>> procModifiesMap;
	unordered_map<int, list<int>> procModifiesMapReverse;
};

