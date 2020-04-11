#include "QueryController.h"

using namespace std;

const string VALID_QUERY = "VALID";
const string INVALID_QUERY = "INVALID";
const string INVALID_BOOLEAN_QUERY = "INVALID_BOOLEAN";

QueryController::QueryController() {

}

list<string> QueryController::processAllQueries(string myQueries, list<string>& results) {
	QueryValidator queryValidator;
	QueryOptimizer queryOptimizer;
	vector<Query> queryList;
	vector<unordered_map<string,string>> projectedResults;
	QueryResultProject resultProjector;

	string checkValidity = queryValidator.isValidDeclarationAndQuery(myQueries);
	// cout << "checkValidity: " << checkValidity << endl;

	if (checkValidity.compare(VALID_QUERY) == 0) {
		Query query = queryValidator.getQuery();
		vector<Clause> clauseList = query.getClauseList();
		for (int i = 0; i < clauseList.size(); i++) {
			string clauseType = clauseList.at(i).getClauseType();
			if (clauseType == "affects" || clauseType == "affects*") {
				PKB::getPKBInstance()->processAffectsMap();
				break;
			}
		}
		queryList = queryOptimizer.optimizeQuery(query);
		for (int i = 0; i < queryList.size(); i++){
			if (!resultProjector.getIsNothing()) {
				QueryEvaluator queryEvaluator;
				queryEvaluator.evaluate(queryList.at(i));
				projectedResults = queryEvaluator.getResult();
				resultProjector.combineResults(projectedResults);
			}
		}
		PKB::getPKBInstance()->clearCacheMaps();
		results = resultProjector.getResult(query);

       
    }
    else if (checkValidity.compare(INVALID_BOOLEAN_QUERY) == 0) {
		results.push_back("false");
    }

	return results;
}
