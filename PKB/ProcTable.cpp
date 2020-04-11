#include "ProcTable.h"

ProcTable::ProcTable(){
}


ProcTable::~ProcTable(){
}

//tbd: input validation
int ProcTable::insertProc(string procName) {
	auto it = procTableReverse.find(procName);
	if (it != procTableReverse.end()) {
		return -1;
	}
	int procID = procTableReverse.size() + 1;
	procTableReverse[procName] = procID;
	procTable[procID] = procName;
	return procID;
}

//return -1 if not found

int ProcTable::getProcID(string varName) {
	unordered_map<string, int>::iterator itKey = procTableReverse.find(varName);
	
	if (itKey == procTableReverse.end()) {
		return -1;
	}
	
	else {
		return itKey->second;
	}
}


string ProcTable::getProcName(int index) {
	
	unordered_map<int, string>::iterator itKey = procTable.find(index);
	if (itKey == procTable.end()) {
		string nullResultString("");
		return nullResultString;
	}

	else {
		return itKey->second;
	}
}

int ProcTable::getProcTableSize() {
	return procTable.size();
}