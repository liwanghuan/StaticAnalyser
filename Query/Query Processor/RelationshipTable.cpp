#include "RelationshipTable.h"
#include <iostream>

// Parent & Parent*
const vector<string> ARGUMENT_TYPE_PARENT_ARG1 = { "stmt", "prog_line", "while", "if", "constant", "all" };
const vector<string> ARGUMENT_TYPE_PARENT_ARG2 = { "stmt", "assign", "prog_line", "while", "if" , "call", "constant", "all" };

// Follows & Follows*
const vector<string> ARGUMENT_TYPE_FOLLOWS_ARG1 = { "stmt", "assign", "prog_line", "while", "if", "call", "constant", "all" };
const vector<string> ARGUMENT_TYPE_FOLLOWS_ARG2 = { "stmt", "assign", "prog_line", "while", "if", "call", "constant", "all" };

// Modifies
const vector<string> ARGUMENT_TYPE_MODIFIES_ARG1 = { "stmt", "assign", "while", "prog_line", "if", "call", "procedure", "string", "constant" };
const vector<string> ARGUMENT_TYPE_MODIFIES_ARG2 = { "variable", "string", "all" };

// Uses
const vector<string> ARGUMENT_TYPE_USES_ARG1 = { "stmt", "assign", "while", "prog_line", "if", "call", "procedure", "string", "constant" };
const vector<string> ARGUMENT_TYPE_USES_ARG2 = { "variable", "string", "all" };

// Pattern (Assign)
const vector<string> ARGUMENT_TYPE_PATTERN_ASSIGN_ARG1 = { "variable", "string", "all" };
const vector<string> ARGUMENT_TYPE_PATTERN_ASSIGN_ARG2 = { "substring", "string", "all" };

// Pattern (While) & Pattern (If)
const vector<string> ARGUMENT_TYPE_PATTERN_WHILE_IF_ARG1 = { "variable", "string", "all" };
const vector<string> ARGUMENT_TYPE_PATTERN_WHILE_IF_ARG2 = { "all" };

// Next & Next*
const vector<string> ARGUMENT_TYPE_NEXT_ARG1 = { "stmt", "assign", "while", "if", "call", "prog_line", "constant", "all" };
const vector<string> ARGUMENT_TYPE_NEXT_ARG2 = { "stmt", "assign", "while", "if", "call", "prog_line", "constant", "all" };

// Calls & Calls*
const vector<string> ARGUMENT_TYPE_CALLS_ARG1 = { "procedure", "string", "all" };
const vector<string> ARGUMENT_TYPE_CALLS_ARG2 = { "procedure", "string", "all" };

// Affects & Affects*
const vector<string> ARGUMENT_TYPE_AFFECTS_ARG1 = { "prog_line", "stmt", "assign", "constant", "all" };
const vector<string> ARGUMENT_TYPE_AFFECTS_ARG2 = { "prog_line", "stmt", "assign", "constant", "all" };

// With (Constant)
const vector<string> ARGUMENT_TYPE_WITH_CONSTANT_ARG1 = { "constant", "stmt", "assign", "while", "if", "call", "stmtNumber", "prog_line" };
const vector<string> ARGUMENT_TYPE_WITH_CONSTANT_ARG2 = { "constant", "stmt", "assign", "while", "if", "call", "stmtNumber", "prog_line" };

// With (String)
const vector<string> ARGUMENT_TYPE_WITH_STRING_ARG1 = { "procedure", "call", "variable", "string" };
const vector<string> ARGUMENT_TYPE_WITH_STRING_ARG2 = { "procedure", "call", "variable", "string" };

RelationshipTable::RelationshipTable()
{
	// Parent
	Relationship parentTable(2, ARGUMENT_TYPE_PARENT_ARG1, ARGUMENT_TYPE_PARENT_ARG2);
	relationshipTable["parent"] = parentTable;

	// Parent*
	Relationship parentStar(2, ARGUMENT_TYPE_PARENT_ARG1, ARGUMENT_TYPE_PARENT_ARG2);
	relationshipTable["parent*"] = parentStar;

	// Follows
	Relationship follows(2, ARGUMENT_TYPE_FOLLOWS_ARG1, ARGUMENT_TYPE_FOLLOWS_ARG2);
	relationshipTable["follows"] = follows;
	
	// Follows*
	Relationship followsStar(2, ARGUMENT_TYPE_FOLLOWS_ARG1, ARGUMENT_TYPE_FOLLOWS_ARG2);
	relationshipTable["follows*"] = followsStar;

	// Modifies
	Relationship modifies(2, ARGUMENT_TYPE_MODIFIES_ARG1, ARGUMENT_TYPE_MODIFIES_ARG2);
	relationshipTable["modifies"] = modifies;

	// Uses
	Relationship uses(2, ARGUMENT_TYPE_USES_ARG1, ARGUMENT_TYPE_USES_ARG2);
	relationshipTable["uses"] = uses;

	// Pattern (Assign)
	Relationship patternAssign(2, ARGUMENT_TYPE_PATTERN_ASSIGN_ARG1, ARGUMENT_TYPE_PATTERN_ASSIGN_ARG2);
	relationshipTable["patternAssign"] = patternAssign;

	// Pattern (While)
	Relationship patternWhile(2, ARGUMENT_TYPE_PATTERN_WHILE_IF_ARG1, ARGUMENT_TYPE_PATTERN_WHILE_IF_ARG2);
	relationshipTable["patternWhile"] = patternWhile;

	// Pattern (If)
	Relationship patternIf(2, ARGUMENT_TYPE_PATTERN_WHILE_IF_ARG1, ARGUMENT_TYPE_PATTERN_WHILE_IF_ARG2);
	relationshipTable["patternIf"] = patternIf;

	// Next
	Relationship next(2, ARGUMENT_TYPE_NEXT_ARG1, ARGUMENT_TYPE_NEXT_ARG2);
	relationshipTable["next"] = next;

	// Next*
	Relationship nextStar(2, ARGUMENT_TYPE_NEXT_ARG1, ARGUMENT_TYPE_NEXT_ARG2);
	relationshipTable["next*"] = nextStar;

	// Calls
	Relationship calls(2, ARGUMENT_TYPE_CALLS_ARG1, ARGUMENT_TYPE_CALLS_ARG2);
	relationshipTable["calls"] = calls;

	// Calls*
	Relationship callsStar(2, ARGUMENT_TYPE_CALLS_ARG1, ARGUMENT_TYPE_CALLS_ARG2);
	relationshipTable["calls*"] = callsStar;

	// Affects
	Relationship affects(2, ARGUMENT_TYPE_AFFECTS_ARG1, ARGUMENT_TYPE_AFFECTS_ARG2);
	relationshipTable["affects"] = affects;

	// Affects*
	Relationship affectsStar(2, ARGUMENT_TYPE_AFFECTS_ARG1, ARGUMENT_TYPE_AFFECTS_ARG2);
	relationshipTable["affects*"] = affectsStar;

	// With (Constant)
	Relationship withConstant(2, ARGUMENT_TYPE_WITH_CONSTANT_ARG1, ARGUMENT_TYPE_WITH_CONSTANT_ARG2);
	relationshipTable["withConstant"] = withConstant;

	// With (String)
	Relationship withString(2, ARGUMENT_TYPE_WITH_STRING_ARG1, ARGUMENT_TYPE_WITH_STRING_ARG2);
	relationshipTable["withString"] = withString;
}

// Check if argument 1 is valid
bool RelationshipTable::isArgs1Valid(string relationship, string type)
{
	Relationship rel = relationshipTable.find(relationship)->second;
	
	vector<string> currentArg1 = rel.getArg1();
	for (vector<string>::const_iterator i = currentArg1.begin(); i != currentArg1.end(); ++i) {
		if (type.compare(*i) == 0) {
			return true;
		}
	}
	return false;
}

// Check if argument 2 is valid
bool RelationshipTable::isArgs2Valid(string relationship, string type)
{
	Relationship rel = relationshipTable.find(relationship)->second;

	vector<string> currentArg2 = rel.getArg2();
	for (vector<string>::const_iterator i = currentArg2.begin(); i != currentArg2.end(); ++i) {
		if (type.compare(*i) == 0) {
			return true;
		}
	}
	return false;
}

// Check if argument type is possible in that particular clause
bool RelationshipTable::hasRelationship(string relationship)
{
	 unordered_map<string, Relationship>::iterator it = relationshipTable.find(relationship);

	// There is no relationship
	if (relationshipTable.find(relationship) == relationshipTable.end()) {
		// cout << "No relationship (RelationshipTable)" << endl;
		return false;
	}
	return true;
}

bool RelationshipTable::isNumOfArgsEqual(string relationship, int num)
{
	Relationship rel = relationshipTable.find(relationship)->second;
	if (rel.getNumOfArgs() == num) {
		return true;
	}
	return false;
}

// Controller to check if both arguments are valid
bool RelationshipTable::isArgsValid(string relationship, int arg, string type)
{
	bool argNumValid = false;

	if (arg == 1) {
		return isArgs1Valid(relationship, type);
	}
	else if (arg == 2) {
		return isArgs2Valid(relationship, type);
	}
}