#include "Uses.h"

Uses::Uses() {
}


Uses::~Uses() {
}


unordered_map<int, list<int>> Uses::getStmtUsesMap() {
	return stmtUsesMap;
}

unordered_map<int, list<int>> Uses::getStmtUsesMapReverse() {
	return stmtUsesMapReverse;
}

unordered_map<int, list<int>> Uses::getProcUsesMap() {
	return procUsesMap;
}

unordered_map<int, list<int>> Uses::getProcUsesMapReverse() {
	return procUsesMapReverse;
}

void Uses::setUses(int procID, int stmtNo, int varID) {
	setStmtUses(stmtNo, varID);
	setProcUses(procID, varID);
}
void Uses::setStmtUses(int stmtNo, int varID) {
	auto it1 = stmtUsesMap.find(stmtNo);
	if (it1 != stmtUsesMap.end()) {
		stmtUsesMap[stmtNo].push_back(varID);
	}
	else {
		stmtUsesMap[stmtNo] = list<int>();
		stmtUsesMap[stmtNo].push_back(varID);
	}

	auto it2 = stmtUsesMapReverse.find(varID);
	if (it2 != stmtUsesMapReverse.end()) {
		stmtUsesMapReverse[varID].push_back(stmtNo);
	}
	else {
		stmtUsesMapReverse[varID] = list<int>();
		stmtUsesMapReverse[varID].push_back(stmtNo);
	}

}
void Uses::sortUsesMap() {
	for (auto it1 = stmtUsesMap.begin(); it1 != stmtUsesMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = stmtUsesMapReverse.begin(); it1 != stmtUsesMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = procUsesMap.begin(); it1 != procUsesMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}

	for (auto it1 = procUsesMapReverse.begin(); it1 != procUsesMapReverse.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}
}

void Uses::setProcUses(int procID, int varID) {
	unordered_map<int, list<int>>::iterator it;

	//ProcUsesMap
	auto it1 = procUsesMap.find(procID);
	if (it1 != procUsesMap.end()) {
		procUsesMap[procID].push_back(varID);
	}
	else {
		procUsesMap[procID] = list<int>();
		procUsesMap[procID].push_back(varID);
	}

	auto it2 = procUsesMapReverse.find(varID);
	if (it2 != procUsesMapReverse.end()) {
		procUsesMapReverse[varID].push_back(procID);
	}
	else {
		procUsesMapReverse[varID] = list<int>();
		procUsesMapReverse[varID].push_back(procID);
	}
}


list<int> Uses::getUses(int varID) {
	unordered_map<int, list<int>>::iterator itKey = stmtUsesMapReverse.find(varID);
	
	if (itKey == stmtUsesMapReverse.end()) {
		list<int> nullResultList;
		return nullResultList;
	}
	
	else {
		return itKey->second;
	}
}


//return empty list if nothing
list<int> Uses::getUsedBy(int stmtNo) {
	unordered_map<int, list<int>>::iterator itKey = stmtUsesMap.find(stmtNo);

	if (itKey == stmtUsesMap.end()) {
		list<int> nullResultList;
		return nullResultList;
	}

	else {
		return itKey->second;
	}
}


bool Uses::isUsesValid(int stmtNumber, int varID) {
	unordered_map<int, list<int>>::iterator it;
	for (it = stmtUsesMap.begin(); it != stmtUsesMap.end(); it++) {
		if (it->first == stmtNumber) {
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



list<int> Uses::getProcUses(int varID) {
	unordered_map<int, list<int>>::iterator itKey = procUsesMapReverse.find(varID);

	if (itKey == procUsesMapReverse.end()) {
		list<int> nullResultList;
		return nullResultList;
	}

	else {
		return itKey->second;
	}
	
}


list<int> Uses::getProcUsedBy(int procID) {
	unordered_map<int, list<int>>::iterator itKey = procUsesMap.find(procID);

	if (itKey == procUsesMap.end()) {
		list<int> nullResultList;
		return nullResultList;
	}

	else {
		return itKey->second;
	}
}

bool Uses::isProcUsesValid(int procID, int varID) {
	unordered_map<int, list<int>>::iterator it;
	for (it = procUsesMap.begin(); it != procUsesMap.end(); it++) {
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

int Uses::getStmtUsesMapSize() {
	return stmtUsesMap.size();
}

int Uses::getStmtUsesMapReverseSize() {
	return stmtUsesMapReverse.size();
}

int Uses::getProcUsesMapSize() {
	return procUsesMap.size();
}

int Uses::getProcUsesMapReverseSize() {
	return procUsesMapReverse.size();
}