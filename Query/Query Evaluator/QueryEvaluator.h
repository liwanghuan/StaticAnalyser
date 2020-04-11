#pragma once

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <regex>
#include <map>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


#include "../Query Processor/Clause.h"
//#include "../Query Processor/Declaration.h"
#include "../Query Processor/Query.h"

#include "FollowsEvaluator.h"
#include "FollowsStarEvaluator.h"
#include "ModifiesEvaluator.h"
#include "ParentEvaluator.h"
#include "ParentStarEvaluator.h"
#include "UsesEvaluator.h"
#include "AffectsEvaluator.h"
#include "AffectsStarEvaluator.h"
#include "CallsEvaluator.h"
#include "CallsStarEvaluator.h"
#include "NextEvaluator.h"
#include "NextStarEvaluator.h"
#include "PatternAssignEvaluator.h"
#include "PatternWhileEvaluator.h"
#include "PatternIfEvaluator.h"
#include "WithConstantEvaluator.h"
#include "WithStringEvaluator.h"
#include "GetAllSelects.h"

#include "EvaluatorResultMap.h"
#include "../../PKB/PKB.h"
#include "ResultTable.h"
#include "JoinOperation.h"
#include "EvaluateSelect.h"

using namespace std;

class QueryEvaluator {
	public:
		QueryEvaluator();
		~QueryEvaluator();
		vector<pair<int, int>> evaluateClause(Clause clause);
		void evaluate(Query query);
		vector<unordered_map<string,string>> getResult();

	private:
		vector<unordered_map<string,string>> finalResultList;
		vector<unordered_map<string, int>> finalMap;
		GetAllSelects getAllSelects;
		EvaluateSelect evaluateSelect;
		EvaluatorResultMap evaluatorResults;
		vector<pair<string, string>> synonymList;
};