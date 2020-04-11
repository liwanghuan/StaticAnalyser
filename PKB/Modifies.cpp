#include "Modifies.h"

Modifies::Modifies() {
}

Modifies::~Modifies() {
}

void Modifies::sortModifiesMap() {
	for (auto it1 = stmtModifiesMap.begin(); it1 != stmtModifiesMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = stmtModifiesMapReverse.begin(); it1 != stmtModifiesMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = procModifiesMap.begin(); it1 != procModifiesMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = procModifiesMapReverse.begin(); it1 != procModifiesMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}
}

unordered_map<int, list<int>> Modifies::getStmtModifiesMap() {
	return stmtModifiesMap;
}

unordered_map<int, list<int>> Modifies::getStmtModifiesMapReverse() {
	return stmtModifiesMapReverse;
}

unordered_map<int, list<int>> Modifies::getProcModifiesMap() {
	return procModifiesMap;
}

unordered_map<int, list<int>> Modifies::getProcModifiesMapReverse() {
	return procModifiesMapReverse;
}

void Modifies::setModifies(int procID, int stmtNo, int varID) {
	setStmtModifies(stmtNo, varID);
	setProcModifies(procID, varID);
}

void Modifies::setStmtModifies(int stmtNo, int varID) {
	auto it1 = stmtModifiesMap.find(stmtNo);
	if (it1 != stmtModifiesMap.end()) {
		stmtModifiesMap[stmtNo].push_back(varID);
	}
	else {
		stmtModifiesMap[stmtNo] = list<int>();
		stmtModifiesMap[stmtNo].push_back(varID);
	}

	auto it2 = stmtModifiesMapReverse.find(varID);
	if (it2 != stmtModifiesMapReverse.end()) {
		stmtModifiesMapReverse[varID].push_back(stmtNo);
	}
	else {
		stmtModifiesMapReverse[varID] = list<int>();
		stmtModifiesMapReverse[varID].push_back(stmtNo);
	}
}

void Modifies::setProcModifies(int procID, int varID) {
	auto it1 = procModifiesMap.find(procID);
	if (it1 != procModifiesMap.end()) {
		procModifiesMap[procID].push_back(varID);
	}
	else {
		procModifiesMap[procID] = list<int>();
		procModifiesMap[procID].push_back(varID);
	}

	auto it2 = procModifiesMapReverse.find(varID);
	if (it2 != procModifiesMapReverse.end()) {
		procModifiesMapReverse[varID].push_back(procID);
	}
	else {
		procModifiesMapReverse[varID] = list<int>();
		procModifiesMapReverse[varID].push_back(procID);
	}
}


list<int> Modifies::getModifies(int varID) {
	unordered_map<int, list<int>>::iterator itKey = stmtModifiesMapReverse.find(varID);
	
	if (itKey == stmtModifiesMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}


list<int> Modifies::getModifiedBy(int stmtNo) {
	unordered_map<int, list<int>>::iterator itKey = stmtModifiesMap.find(stmtNo);

	if (itKey == stmtModifiesMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}


bool Modifies::isModifiesValid(int stmtNo, int varID) {
	unordered_map<int, list<int>>::iterator it;
	for (it = stmtModifiesMap.begin(); it != stmtModifiesMap.end(); it++) {
		if (it->first == stmtNo) {
			list<int>::iterator itList;
			itList = find(it->second.begin(), it->second.end(), varID);

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


list<int> Modifies::getProcModifies(int varID) {
	unordered_map<int, list<int>>::iterator itKey = procModifiesMapReverse.find(varID);

	if (itKey == procModifiesMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}


list<int> Modifies::getProcModifiedBy(int procID) {
	unordered_map<int, list<int>>::iterator itKey = procModifiesMap.find(procID);

	if (itKey == procModifiesMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}


bool Modifies::isProcModifiesValid(int procID, int varID) {

	unordered_map<int, list<int>>::iterator it;
	for (it = procModifiesMap.begin(); it != procModifiesMap.end(); it++) {
		if (it->first == procID) {
			list<int>::iterator itList;
			itList = find(it->second.begin(), it->second.end(), varID);

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

int Modifies::getStmtModifiesMapSize() {
	return stmtModifiesMap.size();
}

int Modifies::getStmtModifiesMapReverseSize() {
	return stmtModifiesMapReverse.size();
}

int Modifies::getProcModifiesMapSize() {
	return procModifiesMap.size();
}

int Modifies::getProcModifiesMapReverseSize() {
	return procModifiesMapReverse.size();
}