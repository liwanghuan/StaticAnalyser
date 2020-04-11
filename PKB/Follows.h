#pragma once

#include <unordered_map>

using namespace std;

class Follows
{

public:
	Follows();
	~Follows();

	unordered_map<int, int> getFollowsMap();
	unordered_map<int, int> getFollowsMapReverse();
	void setFollows(int, int);
	int getFollows(int);
	int getFollowedBy(int);
	bool isFollowsValid(int, int);
	int getFollowsMapSize();
	int getFollowsMapReverseSize();

private:
	unordered_map<int, int> followsMap;
	unordered_map<int, int> followsMapReverse;
};

