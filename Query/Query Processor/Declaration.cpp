#include "Declaration.h"

Declaration::Declaration() {
	varName = "";
	varType = "";
}

Declaration::~Declaration() {
}

void Declaration::setVarName(string name) {
	varName = name;
}

void Declaration::setVarType(string type) {
	varType = type;
}

string Declaration::getVarName() {
	return varName;
}

string Declaration::getVarType() {
	return varType;
}
