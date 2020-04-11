#include "CallsStarEvaluator.h"
CallsStarEvaluator::CallsStarEvaluator() {

}

CallsStarEvaluator::~CallsStarEvaluator() {

}
/*
Input: calls star clause
Output: a list of first arg and second arg
*/
vector<pair<int, int>> CallsStarEvaluator::evaluateCallsStar(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());

	if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {// calls*(p,p)
		return callsStarResult;
	}
	if (arg1Type == "string" && arg2Type == "string") {// calls*("first","second")
		int arg1Num = PKB::getPKBInstance()->getProcID(arg1);
		int arg2Num = PKB::getPKBInstance()->getProcID(arg2);
		if (PKB::getPKBInstance()->isCallsStarValid(arg1Num, arg2Num)) {
			pair<int, int> result = { arg1Num, arg2Num };
			callsStarResult.push_back(result);
		}
	}
	else if (arg1Type == "string") {// calls*("first",q)
		int arg1Num = PKB::getPKBInstance()->getProcID(arg1);
		list<int> propsedArg2 = PKB::getPKBInstance()->getCallsStar(arg1Num);
		while (!propsedArg2.empty())
		{
			int currentArg2 = propsedArg2.front();
			propsedArg2.pop_front();
			vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
			if (find(allPossibleArg2.begin(), allPossibleArg2.end(), currentArg2) != allPossibleArg2.end()) {
				pair<int, int> result = { arg1Num, currentArg2 };
				callsStarResult.push_back(result);
			}
		}
	}
	else if (arg2Type == "string") { // calls*(p,"second")
		int arg2Num = PKB::getPKBInstance()->getProcID(arg2);
		list<int> propsedArg1 = PKB::getPKBInstance()->getCalledStarBy(arg2Num);
		while (!propsedArg1.empty()) {
			int currentArg1 = propsedArg1.front();
			propsedArg1.pop_front();
			vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
			if (find(allPossibleArg1.begin(), allPossibleArg1.end(), currentArg1) != allPossibleArg1.end()) {
				pair<int, int> result = { currentArg1, arg2Num };
				callsStarResult.push_back(result);
			}
		}
	}
	else {// calls*(p,q)
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
		vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
		for (int i = 0; i < allPossibleArg1.size(); i++) {
			int currentArg1 = allPossibleArg1.at(i);
			for (int j = 0; j < allPossibleArg2.size(); j++) {
				int currentArg2 = allPossibleArg2.at(j);
				if (PKB::getPKBInstance()->isCallsStarValid(currentArg1, currentArg2)) {
					pair<int, int> result = { currentArg1, currentArg2 };
					callsStarResult.push_back(result);
				}
			}
		}
	}
	return callsStarResult;
}

