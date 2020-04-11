#include "AffectsStarEvaluator.h"
AffectsStarEvaluator::AffectsStarEvaluator() {

}

AffectsStarEvaluator::~AffectsStarEvaluator() {

}
/*
Input: Affects star clause
Output: Return a list of arg1, arg2
*/
vector<pair<int, int>> AffectsStarEvaluator::evaluateAffectsStar(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();

	if (arg1Type == "number" && arg2Type == "number") { //Affects*(1,2)
		int arg1Num = atoi(arg1.c_str());
		int arg2Num = atoi(arg2.c_str());
		if (PKB::getPKBInstance()->isAffectsStarValid(arg1Num, arg2Num)) {
			pair<int, int> result = { arg1Num, arg2Num };
			affectsStarResult.push_back(result);
		}
	}
	else if (arg1Type == "number") {// Affects*(a,1)
		int arg1Num = atoi(arg1.c_str());
		list<int> propsedArg2 = PKB::getPKBInstance()->getAffectedByStar(arg1Num);
		while (!propsedArg2.empty())
		{
			pair<int, int> result = { arg1Num, propsedArg2.front() };
			affectsStarResult.push_back(result);
			propsedArg2.pop_front();
		}
	}
	else if (arg2Type == "number") {// Affecst*(1,a)
		int arg2Num = atoi(arg2.c_str());
		list<int> propsedArg1 = PKB::getPKBInstance()->getAffectsStar(arg2Num);
		while (!propsedArg1.empty()) {
			pair<int, int> result = { propsedArg1.front(), arg2Num };
			affectsStarResult.push_back(result);
			propsedArg1.pop_front();
		}
	}
	else {// Affects*(a1,a2)
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects("assign");
		if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {// Affects*(a,a)
			for (int i = 0; i < allPossibleArg1.size(); i++) {
				int current = allPossibleArg1.at(i);
				if (PKB::getPKBInstance()->isAffectsStarValid(current, current)) {
					pair<int, int> result = { current,current };
					affectsStarResult.push_back(result);
				}
			}
		}
		else {
			for (int i = 0; i < allPossibleArg1.size(); i++) {// Affects*(a1,a2)
				int currentArg1 = allPossibleArg1.at(i);
				list<int> propsedArg2 = PKB::getPKBInstance()->getAffectedByStar(currentArg1);
				while (!propsedArg2.empty()) {
					pair<int, int> result = { currentArg1, propsedArg2.front() };
					affectsStarResult.push_back(result);
					propsedArg2.pop_front();
				}
			}
		}
	}
	return affectsStarResult;
}

