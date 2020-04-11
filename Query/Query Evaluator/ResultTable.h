#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class ResultTable {
public:
	ResultTable(vector<pair<string, string>>);

	int getTableSize();
	vector<pair<string, string>> getSynonymList();
	vector<unordered_map<string, int>> getTable();
	void setSynonym(string);
	unordered_map<string, int> getEntry(int);

	void addEntry(unordered_map<string, int> entry);
	bool getIsSetSynonym(string);
private:

	int columnSize;
	void setSynonymList(vector<pair<string, string>> list);
	vector<pair<string, string>> synonymList;
	unordered_map<string, bool> isSetSynonymMap;
	unordered_map<string, string> SynonymTypeMap;
	vector<unordered_map<string, int>> table;
};