#include "Relationship.h"

// Relationship object class to support RelationshipTable
Relationship::Relationship()
{
}

Relationship::Relationship(int num, vector<string> args1, vector<string> args2)
{
	totalArgs = num;
	arg1 = args1;
	arg2 = args2;
}

int Relationship::getNumOfArgs()
{
	return totalArgs;
}

vector<string> Relationship::getArg1()
{
	return arg1;
}

vector<string> Relationship::getArg2()
{
	return arg2;
}
