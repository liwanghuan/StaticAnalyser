#include "ResultTable.h"

ResultTable::ResultTable(vector<pair<string, string>> synonymList) {
	for (vector<pair<string, string>>::iterator it = synonymList.begin(); it != synonymList.end(); ++it) {
		isSetSynonymMap[(*it).first] = false;
	}
	setSynonymList(synonymList);
}

void ResultTable::addEntry(unordered_map<string, int> entry) {
	table.push_back(entry);
}

bool ResultTable::getIsSetSynonym(string synonym) {
	unordered_map<string, bool>::iterator itKey;
	for (itKey = isSetSynonymMap.begin(); itKey != isSetSynonymMap.end(); itKey++) {
		if (itKey->first == synonym) {
			return itKey->second;
		}
	}
	return false; // Should not reach this line
}

int ResultTable::getTableSize(){
	return (int) table.size();
}

vector<unordered_map<string, int>> ResultTable::getTable() {
	return table;
}

vector<pair<string, string>> ResultTable::getSynonymList() {
	return synonymList;
}

void ResultTable::setSynonym(string synonym) {
	unordered_map<string, bool>::iterator itKey;
	for (itKey = isSetSynonymMap.begin(); itKey != isSetSynonymMap.end(); itKey++) {
		if (itKey->first == synonym) {
			isSetSynonymMap[synonym] = true;
		}
	}
}

unordered_map<string, int> ResultTable::getEntry(int index) {
	if (index < table.size()) {
		return table.at(index);
	}
	return unordered_map<string, int>(); // Should not reach this line
}

void ResultTable::setSynonymList(vector<pair<string, string>> list) {
	synonymList = list;
}