#pragma once

#include <unordered_map>
#include <list>

using namespace std;

class Parent
{

public:
	Parent();
	~Parent();

	unordered_map<int, list<int>> getParentMap();
	unordered_map<int, int> getParentMapReverse();
	void setParent(int, int);
	int getParent(int);
	list<int> getAllChildren(int);
	bool isParentValid(int, int);
	int getParentMapSize();
	int getParentMapReverseSize();

private:
	unordered_map<int, list<int>> parentMap;
	unordered_map<int, int> parentMapReverse;
};

