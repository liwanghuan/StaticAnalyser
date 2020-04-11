#pragma once

#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

class ParentStar
{

public:
	ParentStar();
	~ParentStar();

	unordered_map<int, list<int>> getParentStarMap();
	unordered_map<int, list<int>> getParentStarMapReverse();

	void setParentStar(int, list<int>);
	void setParentStarMapReverse(unordered_map<int, list<int>>);
	list<int> getParentStar(int);
	list<int> getAllChildrenStar(int);
	bool isParentStarValid(int, int);

	int getParentStarMapSize();		
 	int getParentStarMapReverseSize();
private:
	unordered_map<int, list<int>> parentStarMap;
	unordered_map<int, list<int>> parentStarMapReverse;
};

