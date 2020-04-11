#include "ParentStar.h"
#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

ParentStar::ParentStar() {
}


ParentStar::~ParentStar() {
}

unordered_map<int, list<int>> ParentStar::getParentStarMap() {
	return parentStarMap;
}

unordered_map<int, list<int>> ParentStar::getParentStarMapReverse() {
	return parentStarMapReverse;
}

void ParentStar::setParentStar(int parent, list<int> childList) {
	parentStarMap[parent] = childList;
}

void ParentStar::setParentStarMapReverse(unordered_map<int, list<int>> unordered_map) {
	parentStarMapReverse = unordered_map;
}

list<int> ParentStar::getParentStar(int s2){
	unordered_map<int, list<int>>::iterator itKey = parentStarMapReverse.find(s2);

	if (itKey == parentStarMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}

}

list<int> ParentStar::getAllChildrenStar(int s1) {
	unordered_map<int, list<int>>::iterator itKey = parentStarMap.find(s1);

	if (itKey == parentStarMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}

	else {
		return itKey->second;
	}
}


bool ParentStar::isParentStarValid(int s1, int s2) {
	unordered_map<int, list<int>>::iterator it;
	for (it = parentStarMap.begin(); it != parentStarMap.end(); it++) {
		if (it->first == s1) {
			list<int>::iterator itlist;
			itlist = find(it->second.begin(), it->second.end(), s2);

			if (itlist != it->second.end()) {
				return true;
			}

			else {
				return false;
			}
		}
	}
	return false;
}

int ParentStar::getParentStarMapSize() {
	return parentStarMap.size();
}

int ParentStar::getParentStarMapReverseSize() {
	return parentStarMapReverse.size();
}
