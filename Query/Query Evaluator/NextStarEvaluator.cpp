#include "NextStarEvaluator.h"
NextStarEvaluator::NextStarEvaluator() {

}

NextStarEvaluator::~NextStarEvaluator() {

}
/*
Input: next star clause
Output: Result of next star
*/
vector<pair<int, int>> NextStarEvaluator::evaluateNextStar(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	if (arg1Type == "number" && arg2Type == "number") {// next*(1,2)
		if (isdigit(arg1.at(0)) && isdigit(arg2.at(0))) {
			int arg1Num = atoi(arg1.c_str());
			int arg2Num = atoi(arg2.c_str());
			if (PKB::getPKBInstance()->isNextStarValid(arg1Num, arg2Num)) {
				pair<int, int> result = { arg1Num, arg2Num };
				nextStarResult.push_back(result);
			}
		}
	}
	else if (arg1Type == "number") {// next*(1,a)
		if (isdigit(arg1.at(0))) {
			int arg1Num = atoi(arg1.c_str());
			list<int> propsedArg2 = PKB::getPKBInstance()->getNextStar(arg1Num);
			while (!propsedArg2.empty())
			{
				int currentArg2 = propsedArg2.front();
				propsedArg2.pop_front();
				vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
				if (find(allPossibleArg2.begin(), allPossibleArg2.end(), currentArg2) != allPossibleArg2.end()) {
					pair<int, int> result = { arg1Num, currentArg2 };
					nextStarResult.push_back(result);
				}
			}
		}
	}
	else if (arg2Type == "number") {// next*(a,2)
		if (isdigit(arg2.at(0))) {
			int arg2Num = atoi(arg2.c_str());
			list<int> propsedArg1 = PKB::getPKBInstance()->getPreviousStar(arg2Num);
			while (!propsedArg1.empty()) {
				int currentArg1 = propsedArg1.front();
				propsedArg1.pop_front();
				vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
				if (find(allPossibleArg1.begin(), allPossibleArg1.end(), currentArg1) != allPossibleArg1.end()) {
					pair<int, int> result = { currentArg1, arg2Num };
					nextStarResult.push_back(result);
				}
			}
		}
	}
	else {// next*(_,_)
		if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {// next*(a,a)
			vector<int> allPossibles = getAllSelects.getAllSelects(arg2Type);
			for (int i = 0; i < allPossibles.size(); i++) {
				int current = allPossibles.at(i);
				if (PKB::getPKBInstance()->isNextStarValid(current,current)) {
					pair<int, int> result = { current,current };
					nextStarResult.push_back(result);
				}
			}
		}
		else {// next*(a1,a2)
			vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
			vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
			for (int i = 0; i < allPossibleArg1.size(); i++) {
				int currentArg1 = allPossibleArg1.at(i);
				for (int j = 0; j < allPossibleArg2.size(); j++) {
					int currentArg2 = allPossibleArg2.at(j);
					if (PKB::getPKBInstance()->isNextStarValid(currentArg1, currentArg2)) {
						pair<int, int> result = { currentArg1, currentArg2 };
						nextStarResult.push_back(result);
					}
				}
			}
		}
	}
	return nextStarResult;
}

