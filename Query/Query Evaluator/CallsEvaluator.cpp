#include "CallsEvaluator.h"

CallsEvaluator::CallsEvaluator() {

}

CallsEvaluator::~CallsEvaluator() {

}
/*
Input: calls clause
Output: return a list of arg1, arg2 procedure
*/
vector<pair<int, int>> CallsEvaluator::evaluateCalls(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
    arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());

	if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {
		return callsResult;
	}

	if (arg1Type == "string" && arg2Type == "string") { // calls("first","second")
		int arg1Num = PKB::getPKBInstance()->getProcID(arg1);
		int arg2Num = PKB::getPKBInstance()->getProcID(arg2);
		if (PKB::getPKBInstance()->isCallsValid(arg1Num, arg2Num)) {
			pair<int, int> result = { arg1Num, arg2Num };
			callsResult.push_back(result);
		}
	}
	else if (arg1Type == "string") {// calls("first",p)
		int arg1Num = PKB::getPKBInstance()->getProcID(arg1);
		list<int> propsedArg2 = PKB::getPKBInstance()->getCalls(arg1Num);
		while (!propsedArg2.empty()) {
			pair<int, int> result = { arg1Num, propsedArg2.front() };
			callsResult.push_back(result);
			propsedArg2.pop_front();
		}
	}
	else if (arg2Type == "string") {// calls (p,"second")
		int arg2Num = PKB::getPKBInstance()->getProcID(arg2);
		list<int> propsedArg1 = PKB::getPKBInstance()->getCalledBy(arg2Num);
		while (!propsedArg1.empty()) {
			pair<int, int> result = { propsedArg1.front(),arg2Num};
			callsResult.push_back(result);
			propsedArg1.pop_front();
		}
	}
	else {// calls(p,q)
		for (int i = 1; i <= PKB::getPKBInstance()->getProcTableSize(); i++) {
			for (int j = 1; j <= PKB::getPKBInstance()->getProcTableSize(); j++) {
				if (PKB::getPKBInstance()->isCallsValid(i, j)) {
					pair<int, int> result = {i,j};
					callsResult.push_back(result);
				}
			}
		}
	}

	return callsResult;
}

