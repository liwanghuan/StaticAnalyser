#pragma once
using namespace std;
#ifndef CFGNode_H
#define CFGNode_H
class CFGNode
{
	int index;
	int start;
	int end;
public:
	CFGNode();
	CFGNode(int, int, int);
	int getIndex();
	int getStart();
	int getEnd();
	bool contains(int);
	bool isLargerThan(int);
	bool isSmallerThan(int);
	~CFGNode();
};
#endif
