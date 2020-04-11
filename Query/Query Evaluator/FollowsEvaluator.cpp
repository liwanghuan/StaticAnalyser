#include "FollowsEvaluator.h"

FollowsEvaluator::FollowsEvaluator() {

}

FollowsEvaluator::~FollowsEvaluator() {

}
/*
Inoput: follows clause
Output: list of <arg1,arg2> answer
*/
vector<pair<int,int>> FollowsEvaluator::evaluateFollows(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	if (arg1 == arg2 && arg1Type == arg2Type && arg1!="_") {// follows(a,a) ->return none
		return followsResult;
	}
	if (arg1Type == "number" && arg2Type == "number") {// follows(1,2)
		int arg1Num = atoi(arg1.c_str());
		int arg2Num = atoi(arg2.c_str());
		if (PKB::getPKBInstance()->isFollowsValid(arg1Num, arg2Num)) {
			pair<int, int> result = { arg1Num, arg2Num };
			followsResult.push_back(result);
		}

	}
	else if (arg1Type == "number") {// follows(1,a)
		int arg1Num = atoi(arg1.c_str());
		int propsedArg2 = PKB::getPKBInstance()->getFollowedBy(arg1Num);
		vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
		if (find(allPossibleArg2.begin(), allPossibleArg2.end(), propsedArg2) != allPossibleArg2.end()) {
			pair<int, int> result = { arg1Num,propsedArg2 };
			followsResult.push_back(result);
		}
	}
	else if (arg2Type == "number") {// follows(a,2)
		int arg2Num = atoi(arg2.c_str());
		int propsedArg1 = PKB::getPKBInstance()->getFollows(arg2Num);
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
		if (find(allPossibleArg1.begin(), allPossibleArg1.end(), propsedArg1) != allPossibleArg1.end()) {
			pair<int, int> result = { propsedArg1, arg2Num };
			followsResult.push_back(result);
		}
	}
	else {// follows(a1,a2)
		vector<int> allPossibleArg1 = getAllSelects.getAllSelects(arg1Type);
		vector<int> allPossibleArg2 = getAllSelects.getAllSelects(arg2Type);
	
		for (int i = 0; i < allPossibleArg1.size(); i++) {
			int currentArg1 = allPossibleArg1.at(i);
			for (int j = 0; j < allPossibleArg2.size(); j++) {
				int currentArg2 = allPossibleArg2.at(j);
				if (PKB::getPKBInstance()->isFollowsValid(currentArg1,currentArg2)) {
					pair<int, int> result = { currentArg1, currentArg2 };
					followsResult.push_back(result);
				}
			}
		}
	}

	return followsResult;
}

void FollowsEvaluator::clearResultList() {
	followsResult.clear();
}
