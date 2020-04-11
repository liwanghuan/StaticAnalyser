#include "CallsStar.h"

CallsStar::CallsStar() {
}

CallsStar::~CallsStar() {
}

void CallsStar::sortCallsStarMap() {
	for (auto it1 = callsStarMap.begin(); it1 != callsStarMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = callsStarMapReverse.begin(); it1 != callsStarMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}
}

unordered_map<int, list<int>> CallsStar::getCallsStarMap() {
	return callsStarMap;
}

unordered_map<int, list<int>> CallsStar::getCallsStarMapReverse() {
	return callsStarMapReverse;
}

list<int> CallsStar::getCalledStarBy(int p2) {
	unordered_map<int, list<int>>::iterator itKey = callsStarMapReverse.find(p2);

	if (itKey == callsStarMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}

list<int> CallsStar::getCallsStar(int p1) {
	unordered_map<int, list<int>>::iterator itKey = callsStarMap.find(p1);
	
	if (itKey == callsStarMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}

void CallsStar::setCallsStar(int p1, int p2) {
	auto it1 = callsStarMap.find(p1);
	if (it1 != callsStarMap.end()) {
		callsStarMap[p1].push_back(p2);
	}
	else {
		callsStarMap[p1] = list<int>();
		callsStarMap[p1].push_back(p2);
	}

	auto it2 = callsStarMapReverse.find(p2);
	if (it2 != callsStarMapReverse.end()) {
		callsStarMapReverse[p2].push_back(p1);
	}
	else {
		callsStarMapReverse[p2] = list<int>();
		callsStarMapReverse[p2].push_back(p1);
	}
}

bool CallsStar::isCallsStarValid(int p1, int p2) {
	unordered_map<int, list<int>>::iterator it;
	for (it = callsStarMap.begin(); it != callsStarMap.end(); it++) {
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

int CallsStar::getCallsStarMapSize() {
	return callsStarMap.size();
}

int CallsStar::getCallsStarMapReverseSize() {
	return callsStarMapReverse.size();
}