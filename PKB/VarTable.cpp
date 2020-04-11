#include "VarTable.h"

VarTable::VarTable(){
}

VarTable::~VarTable(){
}
//return added index 
int VarTable::insertVar(string varName) {
	int varIndex = -1;
	auto it = varTableReverse.find(varName);
	if (it != varTableReverse.end()) {
		return it->second;
	}
	varIndex = varTableReverse.size() + 1;
	varTableReverse[varName] = varIndex;
	varTable[varIndex] = varName;
	return varIndex;
}

//return -1 if not found

int VarTable::getVarID(string varName) {
	unordered_map<string, int>::iterator itKey = varTableReverse.find(varName);
	
	if (itKey == varTableReverse.end()) {
		return -1;
	}

	else {
		return itKey->second;
	}
}

//return -1 string if index does not exist

string VarTable::getVarName(int index) {
	unordered_map<int, string>::iterator itKey = varTable.find(index);
	
	if (itKey == varTable.end()) {
		string nullResultString("");
		return nullResultString;
	}
	else {
		return itKey->second;
	}
}

int VarTable::getVarTableSize() {
	return varTable.size();
}
