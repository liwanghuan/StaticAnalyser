#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>

#include "../../SPA Logs/SPALogs.h"
#include "QueryController.h"
#include "../Query Processor/Query.h"
#include "../Query Processor/QueryValidator.h"
#include "../Query Optimizer/QueryOptimizer.h"
#include "../Query Evaluator/QueryEvaluator.h"
#include "QueryResultProjector.h" 

using namespace std;

class QueryController
{
public:
	QueryController();
	list<string> processAllQueries(string myQueries, list<string>& results);
};