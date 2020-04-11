#pragma once

#include <unordered_map>
#include <list>

using namespace std;

class Calls {

public:
	Calls();
	~Calls();

	unordered_map<int, list<int>> getCallsMap();
	unordered_map<int, list<int>> getCallsMapReverse();

	unordered_map<int, int> getStmtCallsMap();
	unordered_map<int, list<int>> getStmtCallsMapReverse();

	list<int> getCalls(int);
	list<int> getCalledBy(int);

	int getProcCalledByStmt(int); // get proc called by stmt
	list<int> getStmtCallsProc(int); // get list of stmt that calls proc

	void sortCallsMap();

	void setCalls(int, int);
	void setStmtCalls(int, int);

	bool isCallsValid(int, int);
	bool isStmtCallsValid(int, int);
	int getCallsMapSize();
	int getStmtCallsMapSize();
	int getCallsMapReverseSize();

private:
	unordered_map<int, list<int>> callsMap;
	unordered_map<int, list<int>> callsMapReverse;

	unordered_map<int, int> stmtCallsMap;
	unordered_map<int, list<int>> stmtCallsMapReverse;
};