#include "EvaluatorResultMap.h"

EvaluatorResultMap::EvaluatorResultMap() {

}
EvaluatorResultMap::~EvaluatorResultMap() {

}
// return whether the type is known 
bool EvaluatorResultMap::isKnown(string argType) {
	return argType == "string" || argType == "substring" || argType == "all" || argType == "number";
}
/*
	Input: variable name and result list
	TODO: merge the result with result table
*/
void EvaluatorResultMap::combineSingleResult(string variable, vector<int> singleResults) {
	if (resultMap.empty()) {
		// if final map is empty, simply add all elements in
		for (int i = 0; i < singleResults.size(); i++) {
			unordered_map<string, int> current;
			current[variable] = singleResults.at(i);
			resultMap.push_back(current);
		}
	}
	else {
		// choose the first row as sample to check whether the variable is inside
		unordered_map<string, int> sample = resultMap.front();
		if (sample.find(variable)!=sample.end()) {
			// if already inside, delete duplicate 
			for (int i = 0; i < resultMap.size(); i++) {
				unordered_map<string, int> current = resultMap.at(i);
				int elementValue =current[variable];
				if (find(singleResults.begin(), singleResults.end(), elementValue) != singleResults.end()) {
					tempMap.push_back(current);
				}
			}
		}
		else {
			// do cross product
			for (int i = 0; i < resultMap.size(); i++) {
				unordered_map<string, int> current = resultMap.at(i);
				for (int j = 0; j < singleResults.size();j++) {
					current[variable] = singleResults.at(j);
					tempMap.push_back(current);
				}
			}
		}
		resultMap = tempMap;
		tempMap.clear();
	}
}
/*
Input: 2 names of arguments and result list
TODO: merge 2 answers with final result list
*/
void EvaluatorResultMap::combineDoubleResults(string arg1, string arg2, vector<pair<int, int>> clauseResult) {
	if (resultMap.empty()) {
		// if map is empty, simply add all cases inside
		for (int i = 0; i < clauseResult.size(); i++) {
			int arg1Value = clauseResult.at(i).first;
			int arg2Value = clauseResult.at(i).second;
			unordered_map<string, int> current;
			current[arg1] = arg1Value;
			current[arg2] = arg2Value;
			resultMap.push_back(current);
		}
	}
	else {
		unordered_map<string, int> sample = resultMap.front();
		bool arg1InMap = sample.find(arg1) != sample.end();
		bool arg2InMap = sample.find(arg2) != sample.end();
		if (arg1InMap && arg2InMap) {
			// delete duplicate
			for (int i = 0; i < resultMap.size(); i++) {
				unordered_map<string, int> currentRow = resultMap.at(i);
				pair<int, int> currentPair = { currentRow[arg1],currentRow[arg2] };
				if (find(clauseResult.begin(), clauseResult.end(), currentPair) != clauseResult.end()) {
					tempMap.push_back(currentRow);
				}
			}
		}
		else if (arg1InMap) {
			// check all possible arg1s and add arg2
			for (int i = 0; i < resultMap.size(); i++) {
				unordered_map<string, int> current = resultMap.at(i);
				for (int j = 0; j < clauseResult.size(); j++) {
					if (current[arg1] == clauseResult.at(j).first) {
						current[arg2] = clauseResult.at(j).second;
						tempMap.push_back(current);
					}
				}
			}
		}
		else if (arg2InMap) {
			// check all arg2s and add arg1
			for (int i = 0; i < resultMap.size(); i++) {
				unordered_map<string, int> current = resultMap.at(i);
				for (int j = 0; j < clauseResult.size(); j++) {
					if (current[arg2] == clauseResult.at(j).second) {
						current[arg1] = clauseResult.at(j).first;
						tempMap.push_back(current);
					}
				}
			}
		}
		else {
			// do cross product
			for (int i = 0; i < resultMap.size(); i++) {
				unordered_map<string, int> current = resultMap.at(i);
				for (int j = 0; j < clauseResult.size(); j++) {
					current[arg1] = clauseResult.at(j).first;
					current[arg2] = clauseResult.at(j).second;
					tempMap.push_back(current);
				}
			
			}
		}
		resultMap = tempMap;
		tempMap.clear();
	}
}

/*
Input: clause and result of clause
TODO: call previous methods and merge with result table 
*/
void EvaluatorResultMap::combineClauseResult(Clause clause, vector<pair<int, int>> clauseResult) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	string synonym = clause.getMainArg();
	string synoType = clause.getMainArgType();
	string relationship = clause.getClauseType();

	if (clauseResult.empty()) {
		isNothing = true;
	}
	if (!isNothing) {
		if (relationship == "patternAssign" || relationship == "patternWhile" || relationship == "patternIf") {
			// if is kind of pattern, check synonym and firstArg
			if (isKnown(arg1Type)) {
				vector<int> synoList;
				for (int i = 0; i < clauseResult.size(); i++) {
					int currentSyno = clauseResult.at(i).first;
					if (find(synoList.begin(), synoList.end(), currentSyno) == synoList.end()) {// remove duplication
						synoList.push_back(currentSyno);
					}
				}
				combineSingleResult(synonym, synoList);
			}
			else {
				combineDoubleResults(synonym, arg1, clauseResult);
			}
			// check nothing
			isNothing = resultMap.empty();
		}
		else {
			// if is kind of such that, check firstArgType and second argType
			// just in case affects (a,a)
			if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {
				vector<int> arg1List;
				for (int i = 0; i < clauseResult.size(); i++) {
					arg1List.push_back(clauseResult.at(i).first);
				}
				combineSingleResult(arg1, arg1List);
			}

            // others
			if (isKnown(arg1Type) && isKnown(arg2Type)) {
				isNothing = clauseResult.empty();
			}
			else if (isKnown(arg1Type)) {
				vector<int> arg2List;
				for (int i = 0; i < clauseResult.size(); i++) {
					int currentArg2 = clauseResult.at(i).second;
					if (find(arg2List.begin(), arg2List.end(), currentArg2) == arg2List.end()) {// remove duplication
						arg2List.push_back(currentArg2);
					}
				}
				combineSingleResult(arg2, arg2List);
				isNothing = resultMap.empty();
			}
			else if (isKnown(arg2Type)) {
				vector<int> arg1List;
				for (int i = 0; i < clauseResult.size(); i++) {
					int currentArg1 = clauseResult.at(i).first;
					if (find(arg1List.begin(), arg1List.end(), currentArg1) == arg1List.end()) {// remove duplication
						arg1List.push_back(currentArg1);
					}
				}
				combineSingleResult(arg1, arg1List);
				isNothing = resultMap.empty();
			}
			else {
				combineDoubleResults(arg1, arg2, clauseResult);
				isNothing = resultMap.empty();
			}
		}
	}
	/*
	// print out map
	cout << "Currently, the resultMap is " << endl;
	for (auto i = resultMap[1].begin(); i != resultMap[1].end(); i++) {
		cout << " " << i->first;
	}
	cout << "" << endl;
	for (auto it = resultMap.begin(); it != resultMap.end(); it++) {
		cout << it->first;
		for (auto it1 = resultMap[it->first].begin(); it1 != resultMap[it->first].end(); it1++) {
			cout << " " << it1->second;
		}
		cout << "" << endl;
	}
	*/
}
bool EvaluatorResultMap::getIsNothing() {
	return isNothing;
}
vector<unordered_map<string, int>> EvaluatorResultMap::getResultMap() {
	return resultMap;
}