#include "Clause.h"

Clause::Clause() {
	clauseType = "";

	firstArg = "";
	firstArgType = "";

	secondArg = "";
	secondArgType = "";

	mainArg = "";
	mainArgType = "";
}

Clause::~Clause() {
}

string Clause::getClauseType() {
	return clauseType;
}

void Clause::setClauseType(string type) {
	clauseType = type;
}

string Clause::getFirstArg() {
	return firstArg;
}

string Clause::getFirstArgType() {
	return firstArgType;
}

string Clause::getSecondArg() {
	return secondArg;
}

string Clause::getSecondArgType() {
	return secondArgType;
}

string Clause::getMainArg() {
	return mainArg;
}

string Clause::getMainArgType() {
	return mainArgType;
}

void Clause::setFirstArg(string arg) {
	firstArg = arg;
}

void Clause::setFirstArgType(string arg) {
	firstArgType = arg;
}

void Clause::setSecondArg(string arg) {
	secondArg = arg;
}

void Clause::setSecondArgType(string arg) {
	secondArgType = arg;
}

void Clause::setMainArg(string arg) {
	mainArg = arg;
}

void Clause::setMainArgType(string arg) {
	mainArgType = arg;
}

void Clause::setIsFirstArgIntercept(bool isIntercept) {
	isFirstArgIntercept = isIntercept;
}

void Clause::setIsSecondArgIntercept(bool isIntercept) {
	isSecondArgIntercept = isIntercept;
}

void Clause::setIsMainArgIntercept(bool isIntercept) {
	isMainArgIntercept = isIntercept;
}

void Clause::setIsSubExpr(bool isAll) {
	isSubExpr = isAll;
}

vector<string> Clause::getVariables() {
	return variables;
}

void Clause::setVariables(vector<string> newVariables) {
	variables = newVariables;
}
