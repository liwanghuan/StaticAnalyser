#include "Calls.h"

Calls::Calls() {
}

Calls::~Calls() {
}

int Calls::getProcCalledByStmt(int s1) {
	unordered_map<int, int>::iterator itKey = stmtCallsMap.find(s1);
	if (itKey == stmtCallsMap.end()) {
		return -1;
	}
	else {
		return itKey->second;
	}
}

list<int> Calls::getStmtCallsProc(int p1) {
	unordered_map<int, list<int>>::iterator itKey = stmtCallsMapReverse.find(p1);

	if (itKey == stmtCallsMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}

void Calls::sortCallsMap() {
	for (auto it1 = callsMap.begin(); it1 != callsMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = callsMapReverse.begin(); it1 != callsMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = stmtCallsMapReverse.begin(); it1 != stmtCallsMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}
}

unordered_map<int, list<int>> Calls::getCallsMap() {
	return callsMap;
}

unordered_map<int, list<int>> Calls::getCallsMapReverse() {
	return callsMapReverse;
}

unordered_map<int, int> Calls::getStmtCallsMap() {
	return stmtCallsMap;
}

unordered_map<int, list<int>> Calls::getStmtCallsMapReverse() {
	return stmtCallsMapReverse;
}

list<int> Calls::getCalledBy(int p2) {
	unordered_map<int, list<int>>::iterator itKey = callsMapReverse.find(p2);

	if (itKey == callsMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}

list<int> Calls::getCalls(int p1) {
	unordered_map<int, list<int>>::iterator itKey = callsMap.find(p1);

	if (itKey == callsMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}

void Calls::setCalls(int p1, int p2) {
	auto it1 = callsMap.find(p1);
	if (it1 != callsMap.end()) {
		callsMap[p1].push_back(p2);
	}
	else {
		callsMap[p1] = list<int>();
		callsMap[p1].push_back(p2);
	}

	auto it2 = callsMapReverse.find(p2);
	if (it2 != callsMapReverse.end()) {
		callsMapReverse[p2].push_back(p1);
	}
	else {
		callsMapReverse[p2] = list<int>();
		callsMapReverse[p2].push_back(p1);
	}
}

void Calls::setStmtCalls(int s1, int p1) {
	stmtCallsMap[s1] = p1;
	auto it3 = stmtCallsMapReverse.find(p1);
	if (it3 != stmtCallsMapReverse.end()) {
		stmtCallsMapReverse[p1].push_back(s1);
	}
	else {
		stmtCallsMapReverse[p1] = list<int>();
		stmtCallsMapReverse[p1].push_back(s1);
	}
}

bool Calls::isCallsValid(int p1, int p2) {
	unordered_map<int, list<int>>::iterator it;
	for (it = callsMap.begin(); it != callsMap.end(); it++) {
		if (it->first == p1) {
			list<int>::iterator itList;
			itList = find(it->second.begin(), it->second.end(), p2);

			if (itList != it->second.end()) {
				return true;
			}

			else {
				return false;
			}
		}
	}
	return false;
}

bool Calls::isStmtCallsValid(int s1, int p1) {
	unordered_map<int, int>::iterator it;
	for (it = stmtCallsMap.begin(); it != stmtCallsMap.end(); it++) {
		if (it->first == s1 && it->second == p1) {
			return true;
		}
	}
	return false;
}

int Calls::getCallsMapSize() {
	return callsMap.size();
}

int Calls::getStmtCallsMapSize() {
	return stmtCallsMap.size();
}

int Calls::getCallsMapReverseSize() {
	return callsMapReverse.size();
}