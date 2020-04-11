#include "AffectsEvaluator.h"

AffectsEvaluator::AffectsEvaluator() {

}

AffectsEvaluator::~AffectsEvaluator() {

}
/*
Input: Affects clause
Output: Return a list of arg1 arg2 
*/
vector<pair<int, int>> AffectsEvaluator::evaluateAffects(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());

	if (arg1Type == "number" && arg2Type == "number") {// Affects(1,2)
		int arg1Num = atoi(arg1.c_str());
		int arg2Num = atoi(arg2.c_str());
		if (PKB::getPKBInstance()->isAffectsValid(arg1Num,arg2Num)) {
			pair<int,int> result = { arg1Num, arg2Num };
			affectsResult.push_back(result);
		}

	}
	else if (arg1Type == "number") {// Affects (a,1)
		int arg1Num = atoi(arg1.c_str());
		list<int> propsedArg2 = PKB::getPKBInstance()->getAffectedBy(arg1Num);
		while(!propsedArg2.empty()) {
			pair<int,int> result = { arg1Num,propsedArg2.front()};
			affectsResult.push_back(result);
			propsedArg2.pop_front();
		}
	}
	else if (arg2Type == "number") {// Affects (1,a)
		int arg2Num = atoi(arg2.c_str());
		list<int> propsedArg1 = PKB::getPKBInstance()->getAffects(arg2Num);
		while (!propsedArg1.empty()) {
			pair<int,int> result = { propsedArg1.front(), arg2Num };
			affectsResult.push_back(result);
			propsedArg1.pop_front();
		}
		
	}
	else {// Affects (a1,a2)
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects("assign");
		if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {
			for (int i = 0; i < allPossibleArg1.size(); i++) {
				int current = allPossibleArg1.at(i);
				if (PKB::getPKBInstance()->isAffectsValid(current, current)) {
					pair<int, int> result = { current,current };
					affectsResult.push_back(result);
				}
			}
		}
		else {
			for (int i = 0; i < allPossibleArg1.size(); i++) {
				int currentArg1 = allPossibleArg1.at(i);
				list<int> propsedArg2 = PKB::getPKBInstance()->getAffectedBy(currentArg1);
				while (!propsedArg2.empty()) {
					pair<int, int> result = { currentArg1, propsedArg2.front() };
					affectsResult.push_back(result);
					propsedArg2.pop_front();
				}
			}
		}
	}

	return affectsResult;
}
