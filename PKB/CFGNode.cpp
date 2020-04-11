#include "CFGNode.h"
CFGNode::CFGNode()
{
}

CFGNode::~CFGNode()
{
}

CFGNode::CFGNode(int i, int s, int e)
{
	index = i;
	start = s;
	end = e;
}
int CFGNode::getIndex()
{
	return index;
}

int CFGNode::getStart()
{
	return start;
}

int CFGNode::getEnd()
{
	return end;
}

bool CFGNode::contains(int i)
{
	return i >= start && i <= end;
}

bool CFGNode::isLargerThan(int i)
{
	return i<start;
}

bool CFGNode::isSmallerThan(int i)
{
	return i>end;
}


