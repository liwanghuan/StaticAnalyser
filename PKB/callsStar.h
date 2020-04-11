#pragma once

#include<unordered_map>
#include<list>

using namespace std;

class CallsStar {

public:
	CallsStar();
	~CallsStar();

	void sortCallsStarMap();

	unordered_map<int, list<int>> getCallsStarMap();
	unordered_map<int, list<int>> getCallsStarMapReverse();
	list<int> getCallsStar(int);
	list<int> getCalledStarBy(int);
	void setCallsStar(int, int);
	bool isCallsStarValid(int, int);
	int getCallsStarMapSize();
	int getCallsStarMapReverseSize();

private:
	unordered_map<int, list<int>> callsStarMap;
	unordered_map<int, list<int>> callsStarMapReverse;
};

