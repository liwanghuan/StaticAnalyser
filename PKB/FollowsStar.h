#pragma once
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

class FollowsStar
{

public:
	FollowsStar();
	~FollowsStar();


	unordered_map<int, list<int>> getFollowsStarMap();
	unordered_map<int, list<int>> getFollowsStarMapReverse();
	void setFollowsStar(int, list<int>);
	void setFollowsStarMapReverse(unordered_map<int, list<int>>);
	list<int> getFollowsStar(int);
	list<int> getFollowsStarBy(int);
	bool isFollowsStarValid(int, int);
	int getFollowsStarMapSize();		
 	int getFollowsStarMapReverseSize();
	
private:
	unordered_map<int, list<int>> followsStarMap;
	unordered_map<int, list<int>> followsStarMapReverse;
};

