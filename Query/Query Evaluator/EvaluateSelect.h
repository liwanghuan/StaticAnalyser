#pragma once
#include "EvaluatorResultMap.h"
#include "../Query Processor/Query.h"
#include "GetAllSelects.h"

using namespace std;

class EvaluateSelect {
public:
	EvaluateSelect();
	string IDtoString(string varType, int id);
	void groupSelect(EvaluatorResultMap resultMap, vector<Select> selectList);
	vector<unordered_map<string,string>> getResultList(EvaluatorResultMap resultMap, vector<Select> selectList);
private:
	vector<Select> selectInMap;
	vector<Select> selectNotInMap;
	GetAllSelects getAllSelects;
	vector<unordered_map<string,string>> resultList;
};
