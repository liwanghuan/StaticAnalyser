#include "QueryResultProjector.h"

QueryResultProject::QueryResultProject() {

}
/*
TODO: check whether should return empty list
*/
bool QueryResultProject::getIsNothing() {
	return isNothing;
}

/*
TODO: combine select lists from query evaluator
*/
void QueryResultProject::combineResults(vector<unordered_map<string, string>> projectResult) {
	if (projectResult.empty()) {
		isNothing = true;
	}
	else {
		unordered_map<string, string> sample = projectResult.at(0);
		if (sample.find("boolean") != sample.end()) {
			string validation = sample["boolean"];
			if (validation == "false") {
				isNothing = true;
				intermediateResult.clear();
			}
		}
		else {
			if (intermediateResult.empty()) {
				intermediateResult = projectResult;
			}
			else {// do cartition  product
				for (int i = 0; i < intermediateResult.size(); i++) {
					unordered_map<string, string> currentRow = intermediateResult.at(i);
					for (int j = 0; j < projectResult.size(); j++) {
						unordered_map<string, string> currentElement = projectResult.at(j);
						for (auto it = currentElement.begin(); it != currentElement.end(); it++) {
							currentRow[it->first] = it->second;
						}
						tempResult.push_back(currentRow);
					}
				}
				intermediateResult = tempResult;
				tempResult.clear();
			}
		}
	}
}
/*
Input: query from validator
Output: list of string which is the final answer 
*/
list<string> QueryResultProject::getResult(Query query) {
	vector<Select> selectList = query.getSelectList();
	list<string> resultList;
	if (selectList.at(0).getVarType() == "boolean") {
		if (isNothing) {
			resultList.push_back("false");
		}
		else {
			resultList.push_back("true");
		}
	}
	else {
		if (!isNothing) {
			for (int i = 0; i < intermediateResult.size(); i++) {
				unordered_map<string, string> currentRow = intermediateResult.at(i);
				string result = currentRow[selectList.at(0).getVarName()];
				for (int j = 1; j < selectList.size(); j++) {
					string value = currentRow[selectList.at(j).getVarName()];
					result = result + " " + value;
				}
				if (find(resultList.begin(), resultList.end(), result) == resultList.end())
					resultList.push_back(result);
			}
		}
	}
	return resultList;
}
