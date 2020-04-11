#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class VarTable{
public:
	VarTable();
	~VarTable();

	int insertVar(string);
	int getVarID(string);
	string getVarName(int);
	int getVarTableSize();

private:
	unordered_map<int, string> varTable;
	unordered_map<string, int> varTableReverse;
};

