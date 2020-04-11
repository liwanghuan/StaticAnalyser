#include "JoinOperation.h"

JoinOperation::JoinOperation() {
}

ResultTable JoinOperation::hashJoin(ResultTable & currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList) {
	//vector<string> commonSynonymList = getCommonSynonymList(currentTable, clauseSynonymList);
	int numOfCommonSynonym = (int)commonSynonymList.size();

	if (numOfCommonSynonym == 0) {
		return hashJoinNoCommonSynonym(currentTable, clauseTable, clauseSynonymList, commonSynonymList);
	} else if (numOfCommonSynonym == 1) {
		return hashJoinOneCommonSynonym(currentTable, clauseTable, clauseSynonymList, commonSynonymList);
	} else {
		return hashJoinTwoCommonSynonym(currentTable, clauseTable, clauseSynonymList, commonSynonymList);
	}
}

/*
vector<string> JoinOperation::getCommonSynonymList(ResultTable& currentTable, vector<string>& clauseSynonymList) {
	vector<string> commonSynonymList;
	vector<string> currentTableSynonymList = currentTable.getSynonymList();

	for (vector<string>::iterator it1 = currentTableSynonymList.begin(); it1 != currentTableSynonymList.end(); ++it1) {
		for (vector<string>::iterator it2 = clauseSynonymList.begin(); it2 != clauseSynonymList.end(); ++it2) {
			if ((*it1) == (*it2)) {
				commonSynonymList.push_back(*it1);
			}
		}
	}
	return commonSynonymList;
}
*/

ResultTable JoinOperation::hashJoinNoCommonSynonym(ResultTable & currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList) {
	int numOfSynonymInClause = (int)clauseSynonymList.size();
	int currentTableSize = currentTable.getTableSize();
	vector<pair<string, string>> newTableSynonymList = currentTable.getSynonymList();
	for (int i = 0; i < (int)clauseSynonymList.size(); ++i) {
		newTableSynonymList.push_back(clauseSynonymList.at(i));
	}
	ResultTable newResultTable = ResultTable(newTableSynonymList);

	for (int i = 0; i < currentTableSize; ++i) {
		if (numOfSynonymInClause == 1) {
			unordered_map<int, vector<int>>::iterator it1;
			for (it1 = clauseTable.begin(); it1 != clauseTable.end(); ++it1) {
				unordered_map<string, int> newEntry = currentTable.getEntry(i);
				newEntry[clauseSynonymList.at(0).first] = it1->first;
				newResultTable.addEntry(newEntry);
			}
		} else {
			unordered_map<int, vector<int>>::iterator it1;
			for (it1 = clauseTable.begin(); it1 != clauseTable.end(); ++it1) {
				vector<int> clauseTableSecondColumnList = it1->second;
				for (vector<int>::iterator it2 = clauseTableSecondColumnList.begin(); it2 != clauseTableSecondColumnList.end(); ++it2) {
					unordered_map<string, int> newEntry = currentTable.getEntry(i);
					newEntry[clauseSynonymList.at(0).first] = it1->first;
					newEntry[clauseSynonymList.at(1).first] = *it2;
					newResultTable.addEntry(newEntry);
				}
			}
		}
	}
	return newResultTable;
}

ResultTable JoinOperation::hashJoinOneCommonSynonym(ResultTable & currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList) {
	int numOfSynonymInClause = (int)clauseSynonymList.size();
	int currentTableSize = currentTable.getTableSize();

	vector<pair<string, string>> newTableSynonymList = currentTable.getSynonymList();

	if (numOfSynonymInClause > 1) {
		newTableSynonymList.push_back(clauseSynonymList.at(1));
	}

	ResultTable newResultTable = ResultTable(newTableSynonymList);

	for (int i = 0; i < currentTableSize; ++i) {

		unordered_map<string, int> newEntry = currentTable.getEntry(i);
		string val = commonSynonymList.at(0);

		if (numOfSynonymInClause == 1) {

			auto it1 = newEntry.find(val);
			if (it1 != newEntry.end()) {
				auto it2 = clauseTable.find(it1->second);
				if (it2 != clauseTable.end()) {
					newResultTable.addEntry(newEntry);
				}
			}
		} else {

			auto it1 = newEntry.find(val);
			if (it1 != newEntry.end()) {
				auto it2 = clauseTable.find(it1->second);
				if (it2 != clauseTable.end()) {
					vector<int> list = it2->second;
					for (vector<int>::iterator it3 = list.begin(); it3 != list.end(); ++it3) {
						newResultTable.addEntry(newEntry);
					}
				}
			}
		}
	}
	return newResultTable;
}

ResultTable JoinOperation::hashJoinTwoCommonSynonym(ResultTable & currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList) {
	//int numOfSynonymInClause = (int)clauseSynonymList.size();
	int currentTableSize = currentTable.getTableSize();

	vector<pair<string, string>> newTableSynonymList = currentTable.getSynonymList();

	ResultTable newResultTable = ResultTable(newTableSynonymList);
	string synonym1 = commonSynonymList.at(0);
	string synonym2 = commonSynonymList.at(1);

	for (int i = 0; i < currentTableSize; ++i) {

		unordered_map<string, int> newEntry = currentTable.getEntry(i);

			auto it1 = newEntry.find(synonym1);
			if (it1 != newEntry.end()) {
				auto it2 = clauseTable.find(it1->second);
				if (it2 != clauseTable.end()) {
					vector<int> list = it2->second;

					int synonym2Value = 0;
					auto it3 = newEntry.find(synonym2);
					if (it3 != newEntry.end()) {
						synonym2Value = it3->second;
					}

					if (find(list.begin(), list.end(), synonym2Value) != list.end()) {
						newResultTable.addEntry(newEntry);
					}
				}
			}
		}
	return newResultTable;
}