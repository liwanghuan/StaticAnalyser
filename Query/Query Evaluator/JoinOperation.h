#pragma once

#include <string>
#include <unordered_map>
#include <list>
#include <vector>

#include "ResultTable.h"

using namespace std;

class JoinOperation {
public:
	JoinOperation();
	ResultTable hashJoin(ResultTable& currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList);
private:
	//vector<string> getCommonSynonymList(ResultTable& currentTable, vector<string>& clauseSynonymList);
	ResultTable hashJoinNoCommonSynonym(ResultTable& currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList);
	ResultTable hashJoinOneCommonSynonym(ResultTable& currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList);
	ResultTable hashJoinTwoCommonSynonym(ResultTable& currentTable, unordered_map<int, vector<int>>& clauseTable, vector<pair<string, string>>& clauseSynonymList, vector<string>& commonSynonymList);
};