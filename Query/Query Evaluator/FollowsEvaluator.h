#pragma once
#include "../../PKB/PKB.h"
#include "../Query Processor/Clause.h"
#include "GetAllSelects.h"

using namespace std;

class FollowsEvaluator {
	public:
		FollowsEvaluator();
		~FollowsEvaluator();
		vector<pair<int,int>> evaluateFollows(Clause clause);
		void clearResultList();
	private:
		vector<pair<int, int>> followsResult;
		GetAllSelects getAllSelects;
};
