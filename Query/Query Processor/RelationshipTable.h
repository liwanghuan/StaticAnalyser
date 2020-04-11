#pragma once
#include "Relationship.h"

#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class RelationshipTable {
private:
	unordered_map<string, Relationship> relationshipTable;
	bool isArgs1Valid(string relationship, string type);
	bool isArgs2Valid(string relationship, string type);

public:
	RelationshipTable();
	bool hasRelationship(string relationship);
	bool isNumOfArgsEqual(string args, int num);
	bool isArgsValid(string relationship, int args, string type);
};