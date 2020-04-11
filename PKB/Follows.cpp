#include "Follows.h"

using namespace std;

Follows::Follows() {
}


Follows::~Follows() {
}

unordered_map<int, int> Follows::getFollowsMap() {
	return followsMap;
}

unordered_map<int, int> Follows::getFollowsMapReverse() {
	return followsMapReverse;
}

void Follows::setFollows(int s1, int s2) {
	followsMapReverse[s2] = s1;
	followsMap[s1] = s2;
}

//return -1 if s2 follows nothing

int Follows::getFollows(int s2) {
	unordered_map<int, int>::iterator itKey = followsMapReverse.find(s2);
		if (itKey == followsMapReverse.end()) {
			return -1;
		}
	
		else {
			return itKey->second;
		}
}



//returns -1 if s1 is followed by no statements

int Follows::getFollowedBy(int s1) {
	unordered_map<int, int>::iterator itKey = followsMap.find(s1);
	if (itKey == followsMap.end()) {
		return -1;
	}
	else {
		return itKey->second;
	}
}


bool Follows::isFollowsValid(int s1, int s2) {
	unordered_map<int, int>::iterator it;
	for (it = followsMap.begin(); it != followsMap.end(); it++) {
		if (it->first == s1 && it->second == s2) {
			return true;
		}
	}
	return false;
}

int Follows::getFollowsMapSize() {
	return followsMap.size();
}

int Follows::getFollowsMapReverseSize() {
	return followsMapReverse.size();
}