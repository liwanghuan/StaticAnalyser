#include "ParentEvaluator.h"
ParentEvaluator::ParentEvaluator() {

}

ParentEvaluator::~ParentEvaluator() {

}
/*
Input: parent clause
Output: parent clause answers
*/
vector<pair<int, int>> ParentEvaluator::evaluateParent(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	if (arg1 == arg2 && arg1Type == arg2Type && arg1 != "_") {// parent(w,w) -> return nothing
		return parentResult;
	}
	if (arg1Type == "number" && arg2Type == "number") {// parent(1,2)
		int arg1Num = atoi(arg1.c_str());
		int arg2Num = atoi(arg2.c_str());
		if (PKB::getPKBInstance()->isParentValid(arg1Num, arg2Num)) {
			pair<int, int> result = { arg1Num,arg2Num };
			parentResult.push_back(result);
		}
	}
	else if (arg1Type == "number") {// parent (1,w)
		int arg1Num = atoi(arg1.c_str());
		list<int> propsedArg2 = PKB::getPKBInstance()->getAllChildren(arg1Num);
		while (!propsedArg2.empty())
		{
		    int currentArg2 = propsedArg2.front();
			propsedArg2.pop_front();
			vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
			if (find(allPossibleArg2.begin(), allPossibleArg2.end(), currentArg2) != allPossibleArg2.end()) {
				pair<int, int> result = {arg1Num,currentArg2};
				parentResult.push_back(result);
			}
		}
		
	}
	else if (arg2Type == "number") {// parent (w,2)
		int arg2Num = atoi(arg2.c_str());
		int propsedArg1 = PKB::getPKBInstance()->getParent(arg2Num);
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
		if (find(allPossibleArg1.begin(), allPossibleArg1.end(), propsedArg1) != allPossibleArg1.end()) {
			pair<int, int> result = { propsedArg1, arg2Num };
			parentResult.push_back(result);
		}
	}
	else {// parent (w,a)
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
		vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
		for (int i = 0; i < allPossibleArg1.size(); i++) {
			int currentArg1 = allPossibleArg1.at(i);
			for (int j = 0; j < allPossibleArg2.size(); j++) {
				int currentArg2 = allPossibleArg2.at(j);
				if (PKB::getPKBInstance()->isParentValid(currentArg1,currentArg2)) {
					pair<int, int> result = { currentArg1, currentArg2 };
					parentResult.push_back(result);
				}
			}
		}
	}

	return parentResult;
}

void ParentEvaluator::clearResultList() {
	parentResult.clear();
}