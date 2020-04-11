#include "WithConstantEvaluator.h"

WithConstantEvaluator::WithConstantEvaluator() {

}

WithConstantEvaluator::~WithConstantEvaluator() {

}

/*
Input: with constant clause
TODO: generate with constant result
*/
void WithConstantEvaluator::evaluateWithConstant(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	if (arg1Type == "number" && arg2Type == "number") {// with 1 = 2;
		int arg1Value = atoi(arg1.c_str());
		int arg2Value = atoi(arg2.c_str());
		if (arg1Value == arg2Value) {
			pair<int, int> result = { arg1Value,arg2Value };
			withConstantResult.push_back(result);
		}
	}
	else if (arg1Type == "number") {// with 1 = a.stmt#
		int arg1Value = atoi(arg1.c_str());
		vector<int> allArg2 = getAllSelects.getAllSelects(arg2Type);
		if (find(allArg2.begin(), allArg2.end(), arg1Value) != allArg2.end()) {
			pair<int, int> result = { arg1Value,arg1Value };
			withConstantResult.push_back(result);
		}
	}
	else if (arg2Type == "number") {// with a.stmt# = 1
		int arg2Value = atoi(arg2.c_str());
		vector<int> allArg1 = getAllSelects.getAllSelects(arg1Type);
		if (find(allArg1.begin(), allArg1.end(), arg2Value) != allArg1.end()) {
			pair<int, int> result = { arg2Value,arg2Value };
			withConstantResult.push_back(result);
		}
	}			
	else {// a.stmtNumber = c.value
		vector<int> allArg1 = getAllSelects.getAllSelects(arg1Type);
		vector<int> allArg2 = getAllSelects.getAllSelects(arg2Type);
		for (int i = 0; i < allArg1.size(); i++) {
			int current = allArg1.at(i);
			if (find(allArg2.begin(), allArg2.end(), current) != allArg2.end()) {
				pair<int, int> result = { current,current };
				withConstantResult.push_back(result);
			}
		}
	}
}

// TODO: return with constant answer
vector<pair<int,int>> WithConstantEvaluator::getWithConstantResult() {
	return withConstantResult;
}
