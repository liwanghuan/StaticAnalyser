#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class ProcTable{
public:
	ProcTable();
	~ProcTable();
	
	int insertProc(string);
	int getProcID(string);
	string getProcName(int);
	int getProcTableSize();

private:
	unordered_map<int, string> procTable;
	unordered_map<string, int> procTableReverse;
};

