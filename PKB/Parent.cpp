#include "Parent.h"

using namespace std;

Parent::Parent() {
}

Parent::~Parent() {
}

unordered_map<int, list<int>> Parent::getParentMap() {
	return parentMap;
}

unordered_map<int, int> Parent::getParentMapReverse() {
	return parentMapReverse;
}

void Parent::setParent(int s1, int s2) {
	parentMapReverse[s2] = s1;
	auto it3 = parentMap.find(s1);
	if (it3 != parentMap.end()) {
		parentMap[s1].push_back(s2);
	} else {
		parentMap[s1] = list<int>();
		parentMap[s1].push_back(s2);
	}
}

//return -1 if s2 doesnt have parent

int Parent::getParent(int s2) {
	unordered_map<int,int>::iterator itKey = parentMapReverse.find(s2);
	if (itKey == parentMapReverse.end()){
		return -1;
	}

	else {
		return itKey->second;
	}
}

list<int> Parent::getAllChildren(int s1) {
	unordered_map<int, list<int>>::iterator itKey = parentMap.find(s1);

	if (itKey == parentMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}

bool Parent::isParentValid(int s1, int s2) {
	unordered_map<int, list<int>>::iterator it;
	for (it = parentMap.begin(); it != parentMap.end(); it++) {
		if (it->first == s1) {
			list<int>::iterator itList;
			itList = find(it->second.begin(), it->second.end(), s2);

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

int Parent::getParentMapSize() {
	return parentMap.size();
}

int Parent::getParentMapReverseSize() {
	return parentMapReverse.size();
}