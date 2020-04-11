
#include "EvaluateSelect.h"

EvaluateSelect::EvaluateSelect() {

}
/*
Input: varId/ progLine/procID
Output: varName/progline(string)/procName
*/
string EvaluateSelect::IDtoString(string varType, int id) {
	string value = "";
	if (varType == "variable") {
		value = PKB::getPKBInstance()->getVarName(id);
	}
	else if (varType == "procedure") {
		value = PKB::getPKBInstance()->getProcName(id);
	}
	else if (varType == "callprocname") {
		int procID = PKB::getPKBInstance()->getProcCalledByStmt(id);
		value = PKB::getPKBInstance()->getProcName(procID);
	}
	else {
		value = to_string(id);
	}
	return value;
}
/*
Input: result table and selectlist
TODO: group all selects in two groups: Select in result table and select not in result table 
*/
void EvaluateSelect::groupSelect(EvaluatorResultMap resultMap, vector<Select> selectList) {
	
	if (resultMap.getResultMap().empty()) {
		for (int i = 0; i < selectList.size(); i++) {
			selectNotInMap.push_back(selectList.at(i));
		}
	}
	else {
		unordered_map<string, int> sample = resultMap.getResultMap().at(0);
		for (int i = 0; i < selectList.size(); i++) {
			Select current = selectList.at(i);
			if (sample.find(current.getVarName()) != sample.end()) {
				selectInMap.push_back(current);
			}
			else {
				selectNotInMap.push_back(current);
			}
		}
	}
}
/*
Input: result map and select list
Output: all variables need to be selected
*/
vector<unordered_map<string,string>> EvaluateSelect::getResultList(EvaluatorResultMap resultMap, vector<Select> selectList){
	if (selectList.at(0).getVarType() == "stmtlst") {
		string varName = selectList.at(0).getVarName();
		unordered_map<string, string> result;
		list<int> stmtList = PKB::getPKBInstance()->getStmtLst();
		while (!stmtList.empty()) {
			int current = stmtList.front();
			result[varName] = to_string(current);
			resultList.push_back(result);
			stmtList.pop_front();
		}
		return resultList;
	}

	if (resultMap.getIsNothing()) {
		if (selectList.at(0).getVarType() == "boolean") {// select boolean
			unordered_map<string,string> resultTuple;
			resultTuple["boolean"] = "false";
			resultList.push_back(resultTuple);
		}
	}
	else {
		if (selectList.at(0).getVarType() == "boolean") {// select boolean
			unordered_map<string, string> resultTuple;
			resultTuple["boolean"] = "true";
			resultList.push_back(resultTuple);
		}
		else {// do the tuple
			// step 1: group all select elements
			groupSelect(resultMap, selectList);

			// step 2: set up select table in the final map
			if (!selectInMap.empty()) {
				vector<unordered_map<string, int>> table = resultMap.getResultMap();
				for (int i = 0; i < table.size(); i++) {
					unordered_map<string, int> row = table.at(i);
					unordered_map<string, string> result;
					for (int j = 0; j < selectInMap.size(); j++) {
						Select currentSelect = selectInMap.at(j);
						string selectType = currentSelect.getVarType();
						string selectName = currentSelect.getVarName();
						int id = row[selectName];
						string value = IDtoString(selectType,id);
						result[selectName] = value;
					}

					if (find(resultList.begin(), resultList.end(), result) == resultList.end()) {
						resultList.push_back(result);
					}
				}
			}

			// step 3: do cross product with not in group elements
			if (selectNotInMap.empty()) {
				return resultList;
			}
			else {
				for (int i = 0; i < selectNotInMap.size(); i++) {
					Select current = selectNotInMap.at(i);
					string selectName = current.getVarName();
					string selectType = current.getVarType();
					vector<int> allPossibleSelect = getAllSelects.getAllSelects(selectType);
					for (int j = 0; j < allPossibleSelect.size(); j++) {
						unordered_map<string, string> result;
						int id = allPossibleSelect.at(j);
						string value = IDtoString(selectType, id);
						result[selectName] = value;
						resultList.push_back(result);
					}
				}
				return resultList;
			}


		}
	}
	return resultList;
}
