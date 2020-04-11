#include "QueryEvaluator.h"

using namespace std;

QueryEvaluator::QueryEvaluator() {

}

QueryEvaluator::~QueryEvaluator() {

}


vector<pair<int, int>> QueryEvaluator::evaluateClause(Clause clause) {
	string relationship = clause.getClauseType();
	// start evaluate
	vector<pair<int, int>> result;
	if (relationship == "follows") {
		FollowsEvaluator followsEvaluator;
		result = followsEvaluator.evaluateFollows(clause);
	}
	else if (relationship == "follows*") {
		FollowsStarEvaluator followsStarEvaluator;
		result = followsStarEvaluator.evaluateFollowsStar(clause);

	}
	else if (relationship == "parent") {
		ParentEvaluator parentEvaluator;
		result = parentEvaluator.evaluateParent(clause);
	}
	else if (relationship == "parent*") {
		ParentStarEvaluator parentStarEvaluator;
		result = parentStarEvaluator.evaluateParentStar(clause);
	}
	else if (relationship == "modifies") {
		ModifiesEvaluator modifiesEvaluator;
		result = modifiesEvaluator.evaluateModifies(clause);
	}
	else if (relationship == "uses") {
		UsesEvaluator usesEvaluator;
		result = usesEvaluator.evaluateUses(clause);
	}
	else if (relationship == "next") {
		NextEvaluator nextEvaluator;
		result = nextEvaluator.evaluateNext(clause);
	}
	else if (relationship == "next*") {
		NextStarEvaluator nextStarEvaluator;
		result = nextStarEvaluator.evaluateNextStar(clause);
	}
	else if (relationship == "calls") {
		CallsEvaluator callsEvaluator;
		result = callsEvaluator.evaluateCalls(clause);
	}
	else if (relationship == "calls*") {
		CallsStarEvaluator callsStarEvaluator;
		result = callsStarEvaluator.evaluateCallsStar(clause);
	}
	else if (relationship == "affects") {
		AffectsEvaluator affectsEvaluator;
		result = affectsEvaluator.evaluateAffects(clause);
	}
	else if (relationship == "affects*") {
		AffectsStarEvaluator affectsStarEvaluator;
		result = affectsStarEvaluator.evaluateAffectsStar(clause);
	}
	else if (relationship == "patternAssign") {
		PatternAssignEvaluator patternAssignEvaluator;
		patternAssignEvaluator.evaluatePatternAssign(clause);
		result = patternAssignEvaluator.getPatternAssignResultList();
	}
	else if (relationship == "patternWhile") {
		PatternWhileEvaluator patternWhileEvaluator;
		patternWhileEvaluator.evaluatePatternWhile(clause);
		result = patternWhileEvaluator.getPatternWhileResultList();
	}
	else if (relationship == "patternIf") {
		PatternIfEvaluator patternIfEvaluator;
		patternIfEvaluator.evaluatePatternIf(clause);
		result = patternIfEvaluator.getPatternIfResultList();
	}
	else if (relationship == "withConstant") {
		WithConstantEvaluator withConstantEvaluator;
		withConstantEvaluator.evaluateWithConstant(clause);
		result = withConstantEvaluator.getWithConstantResult();
	}
	else if (relationship == "withString") {
		WithStringEvaluator withStringEvaluator;
		withStringEvaluator.evaluateWithString(clause);
		result = withStringEvaluator.getWithStringResult();
	}

	return result;
}

void QueryEvaluator::evaluate(Query query) {
	//vector<Declaration> declarationList = query.getDeclarationList();
	vector<Select> selectionList = query.getSelectList();
	vector<Clause> clauseList = query.getClauseList();
	for (int i = 0; i < clauseList.size(); i++) {
		Clause currentClause = clauseList.at(i);
		vector<pair<int, int>> smallResult = evaluateClause(currentClause);
		evaluatorResults.combineClauseResult(currentClause, smallResult);
		finalMap = evaluatorResults.getResultMap();
		//cout << "size of final map is" << finalMap.size() << endl;
	}
	finalResultList = evaluateSelect.getResultList(evaluatorResults, selectionList);
	//cout << finalResultList.size() << endl;
	//cout << finalResultList.at(0)["boolean"] << endl;
}

vector<unordered_map<string,string>> QueryEvaluator::getResult() {
	return finalResultList;
}