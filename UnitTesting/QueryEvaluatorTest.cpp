#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "../PKB/PKB.h"
#include "../Query/Query Evaluator/QueryEvaluator.h"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStudent_VS2015
{
	TEST_CLASS(QueryEvaluatorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialzization) {
			/*
			Source code:
			procedure SIMPLE {
			1	a = 4;
			2	b = a + 2;
			3	c = b + a;
			4	while a {
			5		x = a + 2;
			6		while b {
			7			y = x + 2;
			8			while c {
			9				z = y + 3;
						}
			10			x = z + x + y * 2;
					}
			11		y = z + z * y + 3 + 1 ;
			12		x = x + 1;
				}
			13	a = x + y + z;
			}
			*/
			//-----------------Start initialization------------------------------------
					//init procTable
			PKB::getPKBInstance()->insertProc("SIMPLE");

			//init varTable
			PKB::getPKBInstance()->insertVar("a");
			PKB::getPKBInstance()->insertVar("b");
			PKB::getPKBInstance()->insertVar("c");
			PKB::getPKBInstance()->insertVar("x");
			PKB::getPKBInstance()->insertVar("y");
			PKB::getPKBInstance()->insertVar("z");

			//init follows
			PKB::getPKBInstance()->setFollows(1, 2);
			PKB::getPKBInstance()->setFollows(2, 3);
			PKB::getPKBInstance()->setFollows(3, 4);
			PKB::getPKBInstance()->setFollows(5, 6);
			PKB::getPKBInstance()->setFollows(7, 8);
			PKB::getPKBInstance()->setFollows(8, 10);
			PKB::getPKBInstance()->setFollows(11, 12);
			PKB::getPKBInstance()->setFollows(4, 13);

			//init followStar
			list<int> list1 = { 2,3,4,13 };
			PKB::getPKBInstance()->setFollowsStar(1, list1);
			list<int> list2 = { 3,4,13 };
			PKB::getPKBInstance()->setFollowsStar(2, list2);
			list<int> list3 = { 4,13 };
			PKB::getPKBInstance()->setFollowsStar(3, list3);
			list<int> list4 = { 13 };
			PKB::getPKBInstance()->setFollowsStar(4, list4);
			list<int> list5 = { 6, 11, 12 };
			PKB::getPKBInstance()->setFollowsStar(5, list5);
			list<int> list6 = { 11,12 };
			PKB::getPKBInstance()->setFollowsStar(6, list6);
			list<int> list7 = { 8, 10 };
			PKB::getPKBInstance()->setFollowsStar(7, list7);
			list<int> list8 = { 10 };
			PKB::getPKBInstance()->setFollowsStar(8, list8);
			list<int> list11 = { 12 };
			PKB::getPKBInstance()->setFollowsStar(11, list11);


			//init parent
			PKB::getPKBInstance()->setParent(4, 5);
			PKB::getPKBInstance()->setParent(4, 6);
			PKB::getPKBInstance()->setParent(6, 7);
			PKB::getPKBInstance()->setParent(6, 7);
			PKB::getPKBInstance()->setParent(6, 8);
			PKB::getPKBInstance()->setParent(8, 9);
			PKB::getPKBInstance()->setParent(6, 10);
			PKB::getPKBInstance()->setParent(6, 10);
			PKB::getPKBInstance()->setParent(4, 11);
			PKB::getPKBInstance()->setParent(4, 12);


			//init parentStar(DE)
			list4 = { 5,6,7,8,9,10,11,12 };
			PKB::getPKBInstance()->setParentStar(4, list4);
			list6 = { 7,8,9 };
			PKB::getPKBInstance()->setParentStar(6, list6);
			list8 = { 9 };
			PKB::getPKBInstance()->setParentStar(8, list8);

			//init modifies

			PKB::getPKBInstance()->setStmtModifies(1, 1);
			PKB::getPKBInstance()->setStmtModifies(2, 2);
			PKB::getPKBInstance()->setStmtModifies(3, 3);
			PKB::getPKBInstance()->setStmtModifies(4, 4);
			PKB::getPKBInstance()->setStmtModifies(4, 5);
			PKB::getPKBInstance()->setStmtModifies(4, 6);
			PKB::getPKBInstance()->setStmtModifies(5, 4);
			PKB::getPKBInstance()->setStmtModifies(6, 4);
			PKB::getPKBInstance()->setStmtModifies(6, 5);
			PKB::getPKBInstance()->setStmtModifies(6, 6);
			PKB::getPKBInstance()->setStmtModifies(7, 5);
			PKB::getPKBInstance()->setStmtModifies(8, 6);
			PKB::getPKBInstance()->setStmtModifies(9, 6);
			PKB::getPKBInstance()->setStmtModifies(10, 4);
			PKB::getPKBInstance()->setStmtModifies(11, 5);
			PKB::getPKBInstance()->setStmtModifies(12, 4);
			PKB::getPKBInstance()->setStmtModifies(13, 1);

			PKB::getPKBInstance()->setProcModifies(1, 1);
			PKB::getPKBInstance()->setProcModifies(1, 2);
			PKB::getPKBInstance()->setProcModifies(1, 3);
			PKB::getPKBInstance()->setProcModifies(1, 4);
			PKB::getPKBInstance()->setProcModifies(1, 5);
			PKB::getPKBInstance()->setProcModifies(1, 6);

			//init uses

			PKB::getPKBInstance()->setStmtUses(2, 1);
			PKB::getPKBInstance()->setStmtUses(3, 1);
			PKB::getPKBInstance()->setStmtUses(3, 2);
			PKB::getPKBInstance()->setStmtUses(4, 1);
			PKB::getPKBInstance()->setStmtUses(4, 2);
			PKB::getPKBInstance()->setStmtUses(4, 3);
			PKB::getPKBInstance()->setStmtUses(4, 4);
			PKB::getPKBInstance()->setStmtUses(4, 5);
			PKB::getPKBInstance()->setStmtUses(4, 6);
			PKB::getPKBInstance()->setStmtUses(5, 1);
			PKB::getPKBInstance()->setStmtUses(6, 2);
			PKB::getPKBInstance()->setStmtUses(6, 3);
			PKB::getPKBInstance()->setStmtUses(6, 4);
			PKB::getPKBInstance()->setStmtUses(6, 5);
			PKB::getPKBInstance()->setStmtUses(6, 6);
			PKB::getPKBInstance()->setStmtUses(7, 4);
			PKB::getPKBInstance()->setStmtUses(8, 3);
			PKB::getPKBInstance()->setStmtUses(8, 5);
			PKB::getPKBInstance()->setStmtUses(9, 5);
			PKB::getPKBInstance()->setStmtUses(10, 4);
			PKB::getPKBInstance()->setStmtUses(10, 5);
			PKB::getPKBInstance()->setStmtUses(10, 6);
			PKB::getPKBInstance()->setStmtUses(11, 5);
			PKB::getPKBInstance()->setStmtUses(11, 6);
			PKB::getPKBInstance()->setStmtUses(12, 4);
			PKB::getPKBInstance()->setStmtUses(13, 4);
			PKB::getPKBInstance()->setStmtUses(13, 5);
			PKB::getPKBInstance()->setStmtUses(13, 6);


			PKB::getPKBInstance()->setProcUses(1, 1);
			PKB::getPKBInstance()->setProcUses(1, 2);
			PKB::getPKBInstance()->setProcUses(1, 3);
			PKB::getPKBInstance()->setProcUses(1, 4);
			PKB::getPKBInstance()->setProcUses(1, 5);
			PKB::getPKBInstance()->setProcUses(1, 6);

			//setAssignPattern
			PKB::getPKBInstance()->setAssignPattern(1, "a", "4");
			PKB::getPKBInstance()->setAssignPattern(2, "b", "a+2");
			PKB::getPKBInstance()->setAssignPattern(3, "c", "b+a");
			PKB::getPKBInstance()->setAssignPattern(5, "x", "a+2");
			PKB::getPKBInstance()->setAssignPattern(7, "y", "x+2");
			PKB::getPKBInstance()->setAssignPattern(9, "z", "y+3");
			PKB::getPKBInstance()->setAssignPattern(10, "x", "z+x+y*2");
			PKB::getPKBInstance()->setAssignPattern(11, "y", "z+z*y+3+1");
			PKB::getPKBInstance()->setAssignPattern(12, "x", "x+1");
			PKB::getPKBInstance()->setAssignPattern(13, "a", "x+y+z");

			//setWhilePattern
			PKB::getPKBInstance()->setWhilePattern(4, 1);
			PKB::getPKBInstance()->setWhilePattern(6, 2);
			PKB::getPKBInstance()->setWhilePattern(8, 3);

			PKB::getPKBInstance()->sortUsesModifiesMap();

			// build cfg
			vector<Statement> stmtList;
			Statement stmt = Statement();
			stmt.setStatementNum(-1);
			stmt.setStatementData("procedure SIMPLE {");
			stmt.setStatementType("procedure");
			stmtList.push_back(stmt);

			stmt.setStatementNum(1);
			stmt.setStatementData("a=4;");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(2);
			stmt.setStatementData("b=a+2;");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(3);
			stmt.setStatementData("c=b+a;");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(4);
			stmt.setStatementData("while a {");
			stmt.setStatementType("while");
			stmtList.push_back(stmt);

			stmt.setStatementNum(5);
			stmt.setStatementData("x=a+2;");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(6);
			stmt.setStatementData("while b {");
			stmt.setStatementType("while");
			stmtList.push_back(stmt);

			stmt.setStatementNum(7);
			stmt.setStatementData("y=x+2;");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(8);
			stmt.setStatementData("while c{");
			stmt.setStatementType("while");
			stmtList.push_back(stmt);

			stmt.setStatementNum(9);
			stmt.setStatementData("z=y+3;}");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(10);
			stmt.setStatementData("x=z+x+y*2;}");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(11);
			stmt.setStatementData("y=z+z*y+3+1;");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(12);
			stmt.setStatementData("x=x+1;}");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);

			stmt.setStatementNum(13);
			stmt.setStatementData("a=x+y+z;}");
			stmt.setStatementType("assign");
			stmtList.push_back(stmt);
		}

		TEST_METHOD(EvaluateFollowsTest) {

			//1. Select BOOLEAN such that Follows(1, 2)   ->true 
			Clause clause1;
			Declaration declaration1;
			Select select1;
			Query query1;
			QueryEvaluator queryEvaluator1;
			clause1.setClauseType("follows");
			clause1.setFirstArg("1");
			clause1.setFirstArgType("number");
			clause1.setSecondArg("2");
			clause1.setSecondArgType("number");
			select1.setVarType("boolean");
			query1.addClause(clause1);
			query1.addSelect(select1);
			queryEvaluator1.evaluate(query1);
			vector<unordered_map<string, string>> result1 = queryEvaluator1.getResult();
			Assert::IsTrue(result1.front()["boolean"] == "true");

			//2. Select BOOLEAN such that Follows(2, 1)  ->false 
			Clause clause2;
			Declaration declaration2;
			Select select2;
			Query query2;
			QueryEvaluator queryEvaluator2;
			clause2.setClauseType("follows");
			clause2.setFirstArg("2");
			clause2.setFirstArgType("number");
			clause2.setSecondArg("1");
			clause2.setSecondArgType("number");
			select2.setVarType("boolean");
			query2.addClause(clause2);
			query2.addSelect(select2);
			queryEvaluator2.evaluate(query2);
			vector<unordered_map<string, string>> result2 = queryEvaluator1.getResult();


			//3. assign a; Select BOOLEAN such that Follows(a, 2)   ->true
			Clause clause3;
			Declaration declaration3;
			Select select3;
			Query query3;
			QueryEvaluator queryEvaluator3;
			declaration3.setVarName("a");
			declaration3.setVarType("assign");
			clause3.setClauseType("follows");
			clause3.setFirstArg("a");
			clause3.setFirstArgType("assign");
			clause3.setSecondArg("2");
			clause3.setSecondArgType("number");
			select3.setVarType("boolean");
			query3.addClause(clause3);
			query3.addSelect(select3);
			query3.addDeclaration(declaration3);
			queryEvaluator3.evaluate(query3);
			vector<unordered_map<string, string>> result3 = queryEvaluator3.getResult();
			Assert::IsTrue(result3.front()["boolean"] == "true");

			//4. assign a; Select a such that Follows(a, 2)  ->1
			Clause clause4;
			Declaration declaration4;
			Select select4;
			Query query4;
			QueryEvaluator queryEvaluator4;
			declaration4.setVarName("a");
			declaration4.setVarType("assign");
			clause4.setClauseType("follows");
			clause4.setFirstArg("a");
			clause4.setFirstArgType("assign");
			clause4.setSecondArg("2");
			clause4.setSecondArgType("number");
			select4.setVarType("assign");
			select4.setVarName("a");
			query4.addClause(clause4);
			query4.addSelect(select4);
			query4.addDeclaration(declaration4);
			queryEvaluator4.evaluate(query4);
			vector<unordered_map<string, string>> result4 = queryEvaluator4.getResult();
			unordered_map<string, string>::iterator it = result4.at(0).begin();
			Assert::IsTrue(result4.at(0)["a"] == "1");

			// 5. assign a; Select a such that Follows(1, 2)  ->1, 2, 3, 5, 7, 9, 10, 11, 12, 13
			Clause clause5;
			Declaration declaration5;
			Select select5;
			Query query5;
			QueryEvaluator queryEvaluator5;
			declaration5.setVarName("a");
			declaration5.setVarType("assign");
			clause5.setClauseType("follows");
			clause5.setFirstArg("1");
			clause5.setFirstArgType("number");
			clause5.setSecondArg("2");
			clause5.setSecondArgType("number");
			select5.setVarType("assign");
			select5.setVarName("a");
			query5.addClause(clause5);
			query5.addSelect(select5);
			query5.addDeclaration(declaration5);
			queryEvaluator5.evaluate(query5);
			vector<unordered_map<string, string>> result5 = queryEvaluator5.getResult();
			list<string> propsedResult5 = { "1", "2", "3", "5", "7", "9", "10", "11", "12", "13" };
			Assert::IsTrue(propsedResult5.size() == result5.size());
			for (int i = 0; i < result5.size(); i++) {
				Assert::IsFalse(find(propsedResult5.begin(), propsedResult5.end(), result5.at(i)["a"]) == propsedResult5.end());
			}

			//6. assign a; Select a such that Follows(a, 1)  -> none
			Clause clause6;
			Declaration declaration6;
			Select select6;
			Query query6;
			QueryEvaluator queryEvaluator6;
			declaration6.setVarName("a");
			declaration6.setVarType("follows");
			clause6.setClauseType("parent");
			clause6.setFirstArg("a");
			clause6.setFirstArgType("assign");
			clause6.setSecondArg("1");
			clause6.setSecondArgType("number");
			select6.setVarType("assign");
			select6.setVarName("a");
			query6.addClause(clause6);
			query6.addSelect(select6);
			query6.addDeclaration(declaration6);
			queryEvaluator6.evaluate(query6);
			vector<unordered_map<string, string>> result6 = queryEvaluator6.getResult();
			Assert::IsTrue(result6.empty());

			//7. assign a1, assign a2; Select a1 such that follows(a1,a2) -> 1,2,11
			Clause clause7;
			Declaration declaration7;
			Select select7;
			Query query7;
			QueryEvaluator queryEvaluator7;
			declaration7.setVarName("a1");
			declaration7.setVarType("assign");
			query7.addDeclaration(declaration7);
			declaration7.setVarName("a2");
			declaration7.setVarType("assign");
			query7.addDeclaration(declaration7);
			clause7.setClauseType("follows");
			clause7.setFirstArg("a1");
			clause7.setFirstArgType("assign");
			clause7.setSecondArg("a2");
			clause7.setSecondArgType("assign");
			query7.addClause(clause7);
			select7.setVarType("assign");
			select7.setVarName("a1");
			query7.addSelect(select7);
			queryEvaluator7.evaluate(query7);
			vector<unordered_map<string, string>> result7 = queryEvaluator7.getResult();
			list<string> propsedResult7 = { "1","2","11" };
			Assert::IsTrue(propsedResult7.size() == result7.size());
			for (int i = 0; i < result7.size(); i++) {
				Assert::IsFalse(find(propsedResult7.begin(), propsedResult7.end(), result7.at(i)["a1"]) == propsedResult7.end());
			}

			//8. assign a, while w; Select a such that follows(a,w) -> 3,5,7
			Clause clause8;
			Declaration declaration8;
			Select select8;
			Query query8;
			QueryEvaluator queryEvaluator8;
			declaration8.setVarName("a");
			declaration8.setVarType("assign");
			query8.addDeclaration(declaration8);
			declaration8.setVarName("w");
			declaration8.setVarType("while");
			query8.addDeclaration(declaration8);
			clause8.setClauseType("follows");
			clause8.setFirstArg("a");
			clause8.setFirstArgType("assign");
			clause8.setSecondArg("w");
			clause8.setSecondArgType("while");
			query8.addClause(clause8);
			select8.setVarType("assign");
			select8.setVarName("a");
			query8.addSelect(select8);
			queryEvaluator8.evaluate(query8);
			vector<unordered_map<string,string>> result8 = queryEvaluator8.getResult();
			list<string> propsedResult8 = { "3","5","7" };
			Assert::IsTrue(propsedResult8.size() == result8.size());
			for (int i = 0; i < result8.size(); i++) {
				Assert::IsFalse(find(propsedResult8.begin(), propsedResult8.end(), result8.at(i)["a"]) == propsedResult7.end());
			}
			//Assert::IsTrue(result8 == propsedResult8);
		}

		TEST_METHOD(ParentEvaluatorTest) {
			//9. w, while; select w such that Parent(w,7) ->6
			Clause clause9;
			Declaration declaration9;
			Select select9;
			Query query9;
			QueryEvaluator queryEvaluator9;
			declaration9.setVarName("w");
			declaration9.setVarType("while");
			query9.addDeclaration(declaration9);
			clause9.setClauseType("parent");
			clause9.setFirstArg("w");
			clause9.setFirstArgType("while");
			clause9.setSecondArg("7");
			clause9.setSecondArgType("number");
			query9.addClause(clause9);
			select9.setVarType("while");
			select9.setVarName("w");
			query9.addSelect(select9);
			queryEvaluator9.evaluate(query9);
			vector<unordered_map<string, string>> result9 = queryEvaluator9.getResult();
			list<string> propsedResult9 = { "6" };
			Assert::IsTrue(propsedResult9.size() == result9.size());
			for (int i = 0; i < result9.size(); i++) {
				Assert::IsFalse(find(propsedResult9.begin(), propsedResult9.end(), result9.at(i)["w"]) == propsedResult9.end());
			}

			//10. w, while; select w such that Parent(6,w) ->8
			Clause clause10;
			Declaration declaration10;
			Select select10;
			Query query10;
			QueryEvaluator queryEvaluator10;
			declaration10.setVarName("w");
			declaration10.setVarType("while");
			query10.addDeclaration(declaration10);
			clause10.setClauseType("parent");
			clause10.setFirstArg("6");
			clause10.setFirstArgType("number");
			clause10.setSecondArg("w");
			clause10.setSecondArgType("while");
			query10.addClause(clause10);
			select10.setVarType("while");
			select10.setVarName("w");
			query10.addSelect(select10);
			queryEvaluator10.evaluate(query10);
			vector<unordered_map<string,string>> result10 = queryEvaluator10.getResult();
			list<string> propsedResult10 = { "8" };
			Assert::IsTrue(propsedResult10.size() == result10.size());
			for (int i = 0; i < result10.size(); i++) {
				Assert::IsFalse(find(propsedResult10.begin(), propsedResult10.end(), result10.at(i)["w"]) == propsedResult10.end());
			}
		}

		TEST_METHOD(FollowsStarEvaluatorTest) {
			//11. a, assign; select a such that follows*(1,a) -> 2,3,13
			Clause clause11;
			Declaration declaration11;
			Select select11;
			Query query11;
			QueryEvaluator queryEvaluator11;
			declaration11.setVarName("a");
			declaration11.setVarType("assign");
			query11.addDeclaration(declaration11);
			clause11.setClauseType("follows*");
			clause11.setFirstArg("1");
			clause11.setFirstArgType("number");
			clause11.setSecondArg("a");
			clause11.setSecondArgType("assign");
			query11.addClause(clause11);
			select11.setVarType("assign");
			select11.setVarName("a");
			query11.addSelect(select11);
			queryEvaluator11.evaluate(query11);
			vector<unordered_map<string, string>> result11 = queryEvaluator11.getResult();
			list<string> propsedResult11 = { "2","3","13" };
			Assert::IsTrue(propsedResult11.size() == result11.size());
			for (int i = 0; i < result11.size(); i++) {
				Assert::IsFalse(find(propsedResult11.begin(), propsedResult11.end(), result11.at(i)["a"]) == propsedResult11.end());
			}

		}

		TEST_METHOD(ParentStarEvaluatorTest) {
			//12. w, while; select w such that Parent*(4,w) -> 6,8
			Clause clause12;
			Declaration declaration12;
			Select select12;
			Query query12;
			QueryEvaluator queryEvaluator12;
			declaration12.setVarName("w");
			declaration12.setVarType("while");
			query12.addDeclaration(declaration12);
			clause12.setClauseType("parent*");
			clause12.setFirstArg("4");
			clause12.setFirstArgType("number");
			clause12.setSecondArg("w");
			clause12.setSecondArgType("while");
			query12.addClause(clause12);
			select12.setVarType("while");
			select12.setVarName("w");
			query12.addSelect(select12);
			queryEvaluator12.evaluate(query12);
			vector<unordered_map<string, string>> result12 = queryEvaluator12.getResult();
			list<string> propsedResult12 = { "6","8" };
			Assert::IsTrue(propsedResult12.size() == result12.size());
			for (int i = 0; i < result12.size(); i++) {
				Assert::IsFalse(find(propsedResult12.begin(), propsedResult12.end(), result12.at(i)["w"]) == propsedResult12.end());
			}
			
		}
		
		TEST_METHOD(ModifiesEvaluatorTest) {
			//13. v variable; a, assign; select v such that Modifies(a,v) ->a,b,c,x,y,z
			Clause clause13;
			Declaration declaration13;
			Select select13;
			Query query13;
			QueryEvaluator queryEvaluator13;
			declaration13.setVarName("v");
			declaration13.setVarType("variable");
			query13.addDeclaration(declaration13);
			declaration13.setVarName("a");
			declaration13.setVarType("assign");
			query13.addDeclaration(declaration13);
			clause13.setClauseType("modifies");
			clause13.setFirstArg("a");
			clause13.setFirstArgType("assign");
			clause13.setSecondArg("v");
			clause13.setSecondArgType("variable");
			query13.addClause(clause13);
			select13.setVarType("variable");
			select13.setVarName("v");
			query13.addSelect(select13);
			queryEvaluator13.evaluate(query13);
			vector<unordered_map<string,string>> result13 = queryEvaluator13.getResult();
			list<string> propsedResult13 = { "a","b","c","x","y","z" };
			Assert::IsTrue(propsedResult13.size() == result13.size());
			for (int i = 0; i < result13.size(); i++) {
				Assert::IsFalse(find(propsedResult13.begin(), propsedResult13.end(), result13.at(i)["v"]) == propsedResult13.end());
			}

			//14. s stmt; select s such that Modifies(s,"x") -> 4, 5, 6, 10, 12
			Clause clause14;
			Declaration declaration14;
			Select select14;
			Query query14;
			QueryEvaluator queryEvaluator14;
			declaration14.setVarName("s");
			declaration14.setVarType("stmt");
			query14.addDeclaration(declaration14);
			clause14.setClauseType("modifies");
			clause14.setFirstArg("s");
			clause14.setFirstArgType("stmt");
			clause14.setSecondArg("x");
			clause14.setSecondArgType("string");
			query14.addClause(clause14);
			select14.setVarType("stmt");
			select14.setVarName("s");
			query14.addSelect(select14);
			queryEvaluator14.evaluate(query14);
			vector<unordered_map<string, string>> result14 = queryEvaluator14.getResult();
			list<string> propsedResult14 = { "4","5","6", "10","12" };
		    Assert::IsTrue(propsedResult14.size() == result14.size());
			for (int i = 0; i < result14.size(); i++) {
				Assert::IsFalse(find(propsedResult14.begin(), propsedResult14.end(), result14.at(i)["s"]) == propsedResult14.end());
			}

			//15. v variable; select v such that Modifies(4,v) -> x,y,z
			Clause clause15;
			Declaration declaration15;
			Select select15;
			Query query15;
			QueryEvaluator queryEvaluator15;
			declaration15.setVarName("v");
			declaration15.setVarType("variable");
			query15.addDeclaration(declaration15);
			clause15.setClauseType("modifies");
			clause15.setFirstArg("4");
			clause15.setFirstArgType("number");
			clause15.setSecondArg("v");
			clause15.setSecondArgType("variable");
			query15.addClause(clause15);
			select15.setVarType("variable");
			select15.setVarName("v");
			query15.addSelect(select15);
			queryEvaluator15.evaluate(query15);
			vector<unordered_map<string, string>> result15 = queryEvaluator15.getResult();
			list<string> propsedResult15 = { "x","y","z" };
			Assert::IsTrue(propsedResult15.size() == result15.size());
			for (int i = 0; i < result15.size(); i++) {
				Assert::IsFalse(find(propsedResult15.begin(), propsedResult15.end(), result15.at(i)["v"]) == propsedResult15.end());
			}
		}

		TEST_METHOD(UsesEvaluatorTest) {
			//16. v variable; a, assign; select v such that Uses(a,v) ->a,b,x,y,z
			Clause clause16;
			Declaration declaration16;
			Select select16;
			Query query16;
			QueryEvaluator queryEvaluator16;
			declaration16.setVarName("v");
			declaration16.setVarType("variable");
			query16.addDeclaration(declaration16);
			declaration16.setVarName("a");
			declaration16.setVarType("assign");
			query16.addDeclaration(declaration16);
			clause16.setClauseType("uses");
			clause16.setFirstArg("a");
			clause16.setFirstArgType("assign");
			clause16.setSecondArg("v");
			clause16.setSecondArgType("variable");
			query16.addClause(clause16);
			select16.setVarType("variable");
			select16.setVarName("v");
			query16.addSelect(select16);
			queryEvaluator16.evaluate(query16);
			vector<unordered_map<string,string>> result16 = queryEvaluator16.getResult();
			list<string> propsedResult16 = { "a","b","x","y","z" };
			Assert::IsTrue(result16.size() == propsedResult16.size());
			for (int i = 0; i < result16.size(); i++) {
				Assert::IsFalse(find(propsedResult16.begin(), propsedResult16.end(), result16.at(i)["v"]) == propsedResult16.end());
			}

			//17. s stmt; select s such that Uses(s,"y") -> 4, 6, 8, 9, 10, 11, 13
			Clause clause17;
			Declaration declaration17;
			Select select17;
			Query query17;
			QueryEvaluator queryEvaluator17;
			declaration17.setVarName("s");
			declaration17.setVarType("stmt");
			query17.addDeclaration(declaration17);
			clause17.setClauseType("uses");
			clause17.setFirstArg("s");
			clause17.setFirstArgType("stmt");
			clause17.setSecondArg("y");
			clause17.setSecondArgType("string");
			query17.addClause(clause17);
			select17.setVarType("stmt");
			select17.setVarName("s");
			query17.addSelect(select17);
			queryEvaluator17.evaluate(query17);
			vector<unordered_map<string, string>> result17 = queryEvaluator17.getResult();
			list<string> propsedResult17 = { "4", "6", "8", "9", "10","11", "13" };
			Assert::IsTrue(propsedResult17.size() == result17.size());
			for (int i = 0; i < result17.size(); i++) {
				Assert::IsFalse(find(propsedResult17.begin(), propsedResult17.end(), result17.at(i)["s"]) == propsedResult17.end());
			}

			//18. v variable; select v such that Uses(4,v) -> a, b, c, x, y, z
			Clause clause18;
			Declaration declaration18;
			Select select18;
			Query query18;
			QueryEvaluator queryEvaluator18;
			declaration18.setVarName("v");
			declaration18.setVarType("variable");
			query18.addDeclaration(declaration18);
			clause18.setClauseType("uses");
			clause18.setFirstArg("4");
			clause18.setFirstArgType("number");
			clause18.setSecondArg("v");
			clause18.setSecondArgType("variable");
			query18.addClause(clause18);
			select18.setVarType("variable");
			select18.setVarName("v");
			query18.addSelect(select18);
			queryEvaluator18.evaluate(query18);
			vector<unordered_map<string, string>> result18 = queryEvaluator18.getResult();
			list<string> propsedResult18 = { "a", "b", "c", "x","y","z" };
			Assert::IsTrue(propsedResult18.size() == result18.size());
			for (int i = 0; i < result18.size(); i++) {
				Assert::IsFalse(find(propsedResult18.begin(), propsedResult18.end(), result18.at(i)["v"]) == propsedResult18.end());
			}
			
		}
		
		TEST_METHOD(patternAssignEvaluatorTest) {

			//19. v variable; a assign; select a pattern a(v,_) -> 1, 2, 3, 5, 7, 9, 10, 11, 12, 13
			Clause clause19;
			Declaration declaration19;
			Select select19;
			Query query19;
			QueryEvaluator queryEvaluator19;
			declaration19.setVarName("v");
			declaration19.setVarType("variable");
			query19.addDeclaration(declaration19);
			declaration19.setVarName("a");
			declaration19.setVarType("assign");
			query19.addDeclaration(declaration19);
			clause19.setClauseType("patternAssign");
			clause19.setMainArg("a");
			clause19.setMainArgType("assign");
			clause19.setFirstArg("v");
			clause19.setFirstArgType("variable");
			clause19.setSecondArg("_");
			clause19.setSecondArgType("all");
			query19.addClause(clause19);
			select19.setVarType("assign");
			select19.setVarName("a");
			query19.addSelect(select19);
			queryEvaluator19.evaluate(query19);
			vector<unordered_map<string, string>> result19 = queryEvaluator19.getResult();
			list<string> propsedResult19 = { "1","2","3","5","7","9","10","11","12","13" };
			Assert::IsTrue(result19.size() == propsedResult19.size());
			for (int i = 0; i < result19.size(); i++) {
				Assert::IsFalse(find(propsedResult19.begin(), propsedResult19.end(), result19.at(i)["a"]) == propsedResult19.end());
			}

			//20.  a assign; select a pattern a("a","x+y+z") -> 13
			Clause clause20;
			Declaration declaration20;
			Select select20;
			Query query20;
			QueryEvaluator queryEvaluator20;
			declaration20.setVarName("a");
			declaration20.setVarType("assign");
			query20.addDeclaration(declaration20);
			clause20.setClauseType("patternAssign");
			clause20.setMainArg("a");
			clause20.setMainArgType("assign");
			clause20.setFirstArg("a");
			clause20.setFirstArgType("string");
			clause20.setSecondArg("x+y+z");
			clause20.setSecondArgType("string");
			query20.addClause(clause20);
			select20.setVarType("assign");
			select20.setVarName("a");
			query20.addSelect(select20);
			queryEvaluator20.evaluate(query20);
			vector<unordered_map<string, string>> result20 = queryEvaluator20.getResult();
			list<string> propsedResult20 = { "13" };
			Assert::IsTrue(result20.size() == propsedResult20.size());
			for (int i = 0; i < result20.size(); i++) {
				Assert::IsFalse(find(propsedResult20.begin(), propsedResult20.end(), result20.at(i)["a"]) == propsedResult20.end());
			}

			//21. a assign; select a pattern a(v,_"x+y*2"_) -> empty
			Clause clause21;
			Declaration declaration21;
			Select select21;
			Query query21;
			QueryEvaluator queryEvaluator21;
			declaration21.setVarName("a");
			declaration21.setVarType("assign");
			query21.addDeclaration(declaration21);
			clause21.setClauseType("patternAssign");
			clause21.setMainArg("a");
			clause21.setMainArgType("assign");
			clause21.setFirstArg("v");
			clause21.setFirstArgType("variable");
			clause21.setSecondArg("x+y*2");
			clause21.setSecondArgType("substring");
			query21.addClause(clause21);
			select21.setVarType("assign");
			select21.setVarName("a");
			query21.addSelect(select21);
			queryEvaluator21.evaluate(query21);
			vector<unordered_map<string, string>> result21 = queryEvaluator21.getResult();
			Assert::IsTrue(result21.empty());
			
			// 22. a, assign; Select a pattern a(_,"a+2")  -> 2
			Clause clause22;
			Declaration declaration22;
			Select select22;
			Query query22;
			QueryEvaluator queryEvaluator22;
			declaration22.setVarName("a");
			declaration22.setVarType("assign");
			query22.addDeclaration(declaration22);
			clause22.setClauseType("patternAssign");
			clause22.setMainArg("a");
			clause22.setMainArgType("assign");
			clause22.setFirstArg("_");
			clause22.setFirstArgType("all");
			clause22.setSecondArg("a+2");
			clause22.setSecondArgType("string");
			query22.addClause(clause22);
			select22.setVarType("assign");
			select22.setVarName("a");
			query22.addSelect(select22);
			queryEvaluator22.evaluate(query22);
			vector<unordered_map<string,string>> result22 = queryEvaluator22.getResult();
			list<string> propsedResult22 = { "2" };
			Assert::IsTrue(result22.at(0)["a"] == "2");

			//23. a assign; select a pattern a(v,_"z+z*y"_) -> 11
			Clause clause23;
			Declaration declaration23;
			Select select23;
			Query query23;
			QueryEvaluator queryEvaluator23;
			declaration23.setVarName("a");
			declaration23.setVarType("assign");
			query23.addDeclaration(declaration23);
			clause23.setClauseType("patternAssign");
			clause23.setMainArg("a");
			clause23.setMainArgType("assign");
			clause23.setFirstArg("v");
			clause23.setFirstArgType("variable");
			clause23.setSecondArg("z+z*y");
			clause23.setSecondArgType("substring");
			query23.addClause(clause23);
			select23.setVarType("assign");
			select23.setVarName("a");
			query23.addSelect(select23);
			queryEvaluator23.evaluate(query23);
			vector<unordered_map<string, string>> result23 = queryEvaluator23.getResult();
			Assert::IsTrue(result23.at(0).begin()->second == "11");
		}

		TEST_METHOD(patternWhileEvaluatorTest) {
			// 24. w, while; Select w pattern w("a",_)  -> 4
			Clause clause24;
			Declaration declaration24;
			Select select24;
			Query query24;
			QueryEvaluator queryEvaluator24;
			declaration24.setVarName("w");
			declaration24.setVarType("while");
			query24.addDeclaration(declaration24);
			clause24.setClauseType("patternWhile");
			clause24.setMainArg("w");
			clause24.setMainArgType("while");
			clause24.setFirstArg("a");
			clause24.setFirstArgType("string");
			clause24.setSecondArg("_");
			clause24.setSecondArgType("all");
			query24.addClause(clause24);
			select24.setVarType("while");
			select24.setVarName("w");
			query24.addSelect(select24);
			queryEvaluator24.evaluate(query24);
			vector<unordered_map<string,string>> result24 = queryEvaluator24.getResult();
			Assert::IsTrue(result24.at(0).begin()->second == "4");
		}
		
		TEST_METHOD(patternIfEvaluatorTest) {
			// 25. ifs, if; Select ifs pattern ifs("a",_,_)  -> none
			Clause clause25;
			Declaration declaration25;
			Select select25;
			Query query25;
			QueryEvaluator queryEvaluator25;
			declaration25.setVarName("ifs");
			declaration25.setVarType("if");
			query25.addDeclaration(declaration25);
			clause25.setClauseType("PatternIf");
			clause25.setMainArg("ifs");
			clause25.setMainArgType("if");
			clause25.setFirstArg("a");
			clause25.setFirstArgType("string");
			clause25.setSecondArg("_");
			clause25.setSecondArgType("all");
			query25.addClause(clause25);
			select25.setVarType("if");
			select25.setVarName("ifs");
			query25.addSelect(select25);
			queryEvaluator25.evaluate(query25);
			Assert::IsTrue(queryEvaluator25.getResult().empty());
		}
		
		
		TEST_METHOD(NextEvaluatorTest) {
			/*
			// 27. a, assign; Select a such that Next(a,w)-> 3,5,7,9,10,12
			Clause clause27;
			Declaration declaration27;
			Select select27;
			Query query27;
			QueryEvaluator queryEvaluator27;
			declaration27.setVarName("a");
			declaration27.setVarType("assign");
			query27.addDeclaration(declaration27);
			clause27.setClauseType("next");
			clause27.setFirstArg("a");
			clause27.setFirstArgType("assign");
			clause27.setSecondArg("w");
			clause27.setSecondArgType("while");
			query27.addClause(clause27);
			select27.setVarType("assign");
			select27.setVarName("a");
			query27.addSelect(select27);
			queryEvaluator27.evaluate(query27);
			vector<unordered_map<string,string>> result27 = queryEvaluator27.getResult();
			list<string> propsedResult27 = { "3","5","7","9","10","12" };
			Assert::IsTrue(result27.size() == propsedResult27.size());
			for (int i = 0; i < result27.size(); i++) {
				Assert::IsFalse(find(propsedResult27.begin(), propsedResult27.end(), result27.at(i)["a"]) == propsedResult27.end());
			}*/
			/*
			// 28. a, assign; Select a such that Next(a,6)-> 5, 10
			Clause clause28;
			Declaration declaration28;
			Select select28;
			Query query28;
			QueryEvaluator queryEvaluator28;
			declaration28.setVarName("a");
			declaration28.setVarType("assign");
			query28.addDeclaration(declaration28);
			clause28.setClauseType("next");
			clause28.setFirstArg("a");
			clause28.setFirstArgType("assign");
			clause28.setSecondArg("6");
			clause28.setSecondArgType("constant");
			query28.addClause(clause28);
			select28.setVarType("assign");
			select28.setVarName("a");
			query28.addSelect(select28);
			queryEvaluator28.evaluate(query28);
			vector<unordered_map<string,string>> result28 = queryEvaluator28.getResult();
			list<string> propsedResult28 = { "5","10" };
			Assert::IsTrue(result28.size() == propsedResult28.size());
			for (int i = 0; i < result28.size(); i++) {
				Assert::IsFalse(find(propsedResult28.begin(), propsedResult28.end(), result28.at(i)["a"]) == propsedResult28.end());
			}
			*/
		}

		
		TEST_METHOD(NextStarEvaluatorTest) {
			/*
			// 30. a, assign; Select a such that NextStar(a,6)-> 5, 10
			Clause clause30;
			Declaration declaration30;
			Select select30;
			Query query30;
			QueryEvaluator queryEvaluator30;
			declaration30.setVarName("a");
			declaration30.setVarType("assign");
			query30.addDeclaration(declaration30);
			clause30.setClauseType("nextStar");
			clause30.setFirstArg("a");
			clause30.setFirstArgType("assign");
			clause30.setSecondArg("6");
			clause30.setSecondArgType("constant");
			query30.addClause(clause30);
			select30.setVarType("assign");
			select30.setVarName("a");
			query30.addSelect(select30);
			queryEvaluator30.evaluate(query30);
			list<string> result30 = queryEvaluator30.getResult();
			list<string> propsedResult30 = { "5","10" };
			Assert::IsTrue(result30 == propsedResult30);
			*/
		}
		
		TEST_METHOD(CallsEvaluatorTest) {
			// 32. p, procedure; Select p such that calls(p,"Second")-> none
			Clause clause32;
			Declaration declaration32;
			Select select32;
			Query query32;
			QueryEvaluator queryEvaluator32;
			declaration32.setVarName("p");
			declaration32.setVarType("procedure");
			query32.addDeclaration(declaration32);
			clause32.setClauseType("calls");
			clause32.setFirstArg("p");
			clause32.setFirstArgType("procedure");
			clause32.setSecondArg("Second");
			clause32.setSecondArgType("string");
			query32.addClause(clause32);
			select32.setVarType("procedure");
			select32.setVarName("p");
			query32.addSelect(select32);
			queryEvaluator32.evaluate(query32);
			vector<unordered_map<string,string>> result32 = queryEvaluator32.getResult();
			Assert::IsTrue(result32.empty());
		}
		TEST_METHOD(CallsStarEvaluatorTest) {
			// 35. p, procedure; Select p such that calls*(p,"Second")-> First
			Clause clause35;
			Declaration declaration35;
			Select select35;
			Query query35;
			QueryEvaluator queryEvaluator35;
			declaration35.setVarName("p");
			declaration35.setVarType("procedure");
			query35.addDeclaration(declaration35);
			clause35.setClauseType("calls*");
			clause35.setFirstArg("p");
			clause35.setFirstArgType("procedure");
			clause35.setSecondArg("Second");
			clause35.setSecondArgType("string");
			query35.addClause(clause35);
			select35.setVarType("procedure");
			select35.setVarName("p");
			query35.addSelect(select35);
			queryEvaluator35.evaluate(query35);
			vector<unordered_map<string,string>>result35 = queryEvaluator35.getResult();
			Assert::IsTrue(result35.empty());
		}

		TEST_METHOD(WithConstantEvaluatorTest) {
			// 37. a assign; select a with a.prog_line# = 3  -> 3
			Clause clause37;
			Declaration declaration37;
			Select select37;
			Query query37;
			QueryEvaluator queryEvaluator37;
			declaration37.setVarName("a");
			declaration37.setVarType("assign");
			query37.addDeclaration(declaration37);
			clause37.setClauseType("withConstant");
			clause37.setFirstArg("a");
			clause37.setFirstArgType("assign");
			clause37.setSecondArg("3");
			clause37.setSecondArgType("number");
			query37.addClause(clause37);
			select37.setVarType("assign");
			select37.setVarName("a");
			query37.addSelect(select37);
			queryEvaluator37.evaluate(query37);
			vector<unordered_map<string,string>> result37 = queryEvaluator37.getResult();
			Assert::IsTrue(result37.at(0).begin()->second == "3");
		}
		TEST_METHOD(WithStringEvaluatorTest) {
			// 39. v, variable; p, procedure; select v with v.varName = p.procName; -> none
			Clause clause39;
			Declaration declaration39;
			Select select39;
			Query query39;
			QueryEvaluator queryEvaluator39;
			declaration39.setVarName("v");
			declaration39.setVarType("variable");
			query39.addDeclaration(declaration39);
			declaration39.setVarName("p");
			declaration39.setVarType("procedure");
			query39.addDeclaration(declaration39);
			clause39.setClauseType("withString");
			clause39.setFirstArg("v");
			clause39.setFirstArgType("variable");
			clause39.setSecondArg("p");
			clause39.setSecondArgType("prodedure");
			query39.addClause(clause39);
			select39.setVarType("v");
			select39.setVarName("variable");
			query39.addSelect(select39);
			queryEvaluator39.evaluate(query39);
			vector<unordered_map<string,string>> result39 = queryEvaluator39.getResult();
			Assert::IsTrue(result39.empty());
			
		}
			private:

	};
}
