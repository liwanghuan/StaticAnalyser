#include "FollowsStar.h"
#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

FollowsStar::FollowsStar() {
}


FollowsStar::~FollowsStar() {
}

unordered_map<int, list<int>> FollowsStar::getFollowsStarMap() {
	return followsStarMap;
}

unordered_map<int, list<int>> FollowsStar::getFollowsStarMapReverse() {
	return followsStarMapReverse;
}

void FollowsStar::setFollowsStar(int s1, list<int> s2List) {
	followsStarMap[s1] = s2List;
}

void FollowsStar::setFollowsStarMapReverse(unordered_map<int, list<int>> unordered_map) {
	followsStarMapReverse = unordered_map;
}

//return -1 list if s1 followed* by nothing
list<int> FollowsStar::getFollowsStar(int s2) {
	unordered_map<int, list<int>>::iterator itKey= followsStarMapReverse.find(s2);
	if (itKey == followsStarMapReverse.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}
	else {
		return itKey->second;
	}
}

list<int> FollowsStar::getFollowsStarBy(int s1){
	unordered_map<int, list<int>>::iterator itKey = followsStarMap.find(s1);
	if (itKey == followsStarMap.end()) {
		list<int> nullResultVector;
		return nullResultVector;
	}
	else {
		return itKey->second;
	}
}


bool FollowsStar::isFollowsStarValid(int s1, int s2) {
	unordered_map<int, list<int>>::iterator it;
	for (it = followsStarMap.begin(); it != followsStarMap.end(); it++) {
		if (it->first == s1) {
			list<int>::iterator itVector;
			itVector = find(it->second.begin(), it->second.end(), s2);

			if (itVector != it->second.end()) {
				return true;
			}

			else {
				return false;
			}
		}
	}
	return false;
}
int FollowsStar::getFollowsStarMapSize() {
	return followsStarMap.size();
}

int FollowsStar::getFollowsStarMapReverseSize() {
	return followsStarMapReverse.size();
}
