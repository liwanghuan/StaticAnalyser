#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "../Query/Query Optimizer/QueryOptimizer.h"

const string VALID_QUERY = "VALID";
const string INVALID_QUERY = "INVALID";
const string INVALID_BOOLEAN_QUERY = "INVALID_BOOLEAN";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryOptimizer)
	{
	public:

		TEST_METHOD(testQueryOptimizerSelect) // Sample
		{
			QueryOptimizer qo; string s;

			// No clauses one select
			Query initial;
			Select a;
			a.setVarName("a");
			a.setVarType("assign");
			initial.addSelect(a);
			
			vector<Query> result = qo.optimizeQuery(initial);
			Query tempQuery = result.at(0);
			vector<Select> tempSelect = tempQuery.getSelectList();
			Assert::AreEqual(tempSelect.at(0).getVarName().compare("a"), 0);
			Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);

			// No clauses two select
			Select b;
			b.setVarName("b");
			b.setVarType("assign");
			initial.addSelect(b);

			result = qo.optimizeQuery(initial);
			for (int i = 0; i < result.size(); i++) {
				Query tempQuery = result.at(i);
				vector<Select> tempSelect = tempQuery.getSelectList();
				if (i == 0) {
					Assert::AreEqual(tempSelect.at(0).getVarName().compare("a"), 0);
					Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);
				}
				else {
					Assert::AreEqual(tempSelect.at(0).getVarName().compare("b"), 0);
					Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);
				}
			}
		}

		TEST_METHOD(testQueryOptimizerClause) // Sample
		{
			QueryOptimizer qo; string s;

			// One clause one select
			Query initial;
			Select a;
			a.setVarName("a");
			a.setVarType("assign");
			initial.addSelect(a);
			Clause clauseA;
			clauseA.setClauseType("Follows");
			clauseA.setFirstArg("a");
			clauseA.setFirstArgType("assign");
			clauseA.setSecondArg("5");
			clauseA.setSecondArgType("number");
			initial.addClause(clauseA);

			vector<Query> result = qo.optimizeQuery(initial);
			Query tempQuery = result.at(0);
			vector<Select> tempSelect = tempQuery.getSelectList();
			Assert::AreEqual(tempSelect.at(0).getVarName().compare("a"), 0);
			Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);
			vector < Clause > tempClause = tempQuery.getClauseList();
			Assert::AreEqual(tempClause.at(0).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArg().compare("5"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArgType().compare("number"), 0);

			// Two clauses with similar synonyms one select
			Clause clauseB;
			clauseB.setClauseType("Follows");
			clauseB.setFirstArg("a");
			clauseB.setFirstArgType("assign");
			clauseB.setSecondArg("2");
			clauseB.setSecondArgType("number");
			initial.addClause(clauseB);

			result = qo.optimizeQuery(initial);
			tempQuery = result.at(0);
			tempSelect = tempQuery.getSelectList();
			Assert::AreEqual(tempSelect.at(0).getVarName().compare("a"), 0);
			Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);
			tempClause = tempQuery.getClauseList();
			Assert::AreEqual(tempClause.at(0).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArg().compare("5"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArgType().compare("number"), 0);
			Assert::AreEqual(tempClause.at(1).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(1).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(1).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(1).getSecondArg().compare("2"), 0);
			Assert::AreEqual(tempClause.at(1).getSecondArgType().compare("number"), 0);

			// Three clauses with similar synonyms and one non similar one select
			Clause clauseC;
			clauseC.setClauseType("Follows");
			clauseC.setFirstArg("b");
			clauseC.setFirstArgType("assign");
			clauseC.setSecondArg("2");
			clauseC.setSecondArgType("number");
			initial.addClause(clauseC);

			result = qo.optimizeQuery(initial);
			tempQuery = result.at(1);
			tempSelect = tempQuery.getSelectList();
			Assert::AreEqual(tempSelect.at(0).getVarName().compare("a"), 0);
			Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);
			tempClause = tempQuery.getClauseList();
			Assert::AreEqual(tempClause.at(0).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArg().compare("5"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArgType().compare("number"), 0);
			Assert::AreEqual(tempClause.at(1).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(1).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(1).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(1).getSecondArg().compare("2"), 0);
			Assert::AreEqual(tempClause.at(1).getSecondArgType().compare("number"), 0);

			tempQuery = result.at(0);
			tempSelect = tempQuery.getSelectList();
			Assert::AreEqual(tempSelect.at(0).getVarName().compare(""), 0);
			Assert::AreEqual(tempSelect.at(0).getVarType().compare("boolean"), 0);
			tempClause = tempQuery.getClauseList();
			Assert::AreEqual(tempClause.at(0).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArg().compare("b"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArg().compare("2"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArgType().compare("number"), 0);

			// Foure clauses with similar synonyms causing merging one select
			Clause clauseD;
			clauseD.setClauseType("Affects");
			clauseD.setFirstArg("b");
			clauseD.setFirstArgType("assign");
			clauseD.setSecondArg("a");
			clauseD.setSecondArgType("assign");
			initial.addClause(clauseD);

			result = qo.optimizeQuery(initial);
			tempQuery = result.at(0);
			tempSelect = tempQuery.getSelectList();
			Assert::AreEqual(tempSelect.at(0).getVarName().compare("a"), 0);
			Assert::AreEqual(tempSelect.at(0).getVarType().compare("assign"), 0);
			tempClause = tempQuery.getClauseList();
			Assert::AreEqual(tempClause.at(0).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(0).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArg().compare("5"), 0);
			Assert::AreEqual(tempClause.at(0).getSecondArgType().compare("number"), 0);
			Assert::AreEqual(tempClause.at(1).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(1).getFirstArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(1).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(1).getSecondArg().compare("2"), 0);
			Assert::AreEqual(tempClause.at(1).getSecondArgType().compare("number"), 0);
			Assert::AreEqual(tempClause.at(2).getClauseType().compare("Affects"), 0);
			Assert::AreEqual(tempClause.at(2).getFirstArg().compare("b"), 0);
			Assert::AreEqual(tempClause.at(2).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(2).getSecondArg().compare("a"), 0);
			Assert::AreEqual(tempClause.at(2).getSecondArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(3).getClauseType().compare("Follows"), 0);
			Assert::AreEqual(tempClause.at(3).getFirstArg().compare("b"), 0);
			Assert::AreEqual(tempClause.at(3).getFirstArgType().compare("assign"), 0);
			Assert::AreEqual(tempClause.at(3).getSecondArg().compare("2"), 0);
			Assert::AreEqual(tempClause.at(3).getSecondArgType().compare("number"), 0);

		}
	};
}