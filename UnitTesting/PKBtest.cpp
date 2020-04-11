#include "stdafx.h"
#include "CppUnitTest.h"
#include "../PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStudent_VS2015 {

	TEST_CLASS(PKBtest) {
public:
	TEST_METHOD_INITIALIZE(setUpPKB) {
		//init procTable
		PKB::getPKBInstance()->insertProc("First");
		PKB::getPKBInstance()->insertProc("Second");
		PKB::getPKBInstance()->insertProc("Third");
		PKB::getPKBInstance()->insertProc("Fourth");
		PKB::getPKBInstance()->insertProc("Fifth");

		//init varTable
		PKB::getPKBInstance()->insertVar("a");
		PKB::getPKBInstance()->insertVar("b");
		PKB::getPKBInstance()->insertVar("c");
		PKB::getPKBInstance()->insertVar("d");
		PKB::getPKBInstance()->insertVar("e");
		PKB::getPKBInstance()->insertVar("v");
		PKB::getPKBInstance()->insertVar("w");
		PKB::getPKBInstance()->insertVar("x");
		PKB::getPKBInstance()->insertVar("y");
		PKB::getPKBInstance()->insertVar("z");

		//init follows
		PKB::getPKBInstance()->setFollows(1, 2);
		PKB::getPKBInstance()->setFollows(2, 3);
		PKB::getPKBInstance()->setFollows(3, 4);
		PKB::getPKBInstance()->setFollows(4, 5);
		PKB::getPKBInstance()->setFollows(5, 6);
		PKB::getPKBInstance()->setFollows(7, 8);
		PKB::getPKBInstance()->setFollows(9, 10);
		PKB::getPKBInstance()->setFollows(11, 12);
		PKB::getPKBInstance()->setFollows(13, 14);
		PKB::getPKBInstance()->setFollows(14, 15);
		PKB::getPKBInstance()->setFollows(16, 17);
		PKB::getPKBInstance()->setFollows(17, 18);
		PKB::getPKBInstance()->setFollows(18, 19);
		PKB::getPKBInstance()->setFollows(19, 20);

		//init followStar(DE)



		//init parent
		PKB::getPKBInstance()->setParent(3, 7);
		PKB::getPKBInstance()->setParent(3, 8);
		PKB::getPKBInstance()->setParent(10, 11);
		PKB::getPKBInstance()->setParent(10, 12);
		PKB::getPKBInstance()->setParent(14, 16);
		PKB::getPKBInstance()->setParent(14, 17);
		PKB::getPKBInstance()->setParent(14, 18);


		//init parentStar(DE)


		//init modifies
		PKB::getPKBInstance()->setModifies(1, 1, 1);
		PKB::getPKBInstance()->setModifies(1, 1, 2);
		PKB::getPKBInstance()->setModifies(1, 2, 3);
		PKB::getPKBInstance()->setModifies(1, 3, 4);
		PKB::getPKBInstance()->setModifies(1, 5, 5);
		PKB::getPKBInstance()->setModifies(1, 17, 5);

		PKB::getPKBInstance()->setStmtModifies(7, 5);
		PKB::getPKBInstance()->setStmtModifies(8, 6);
		PKB::getPKBInstance()->setStmtModifies(9, 7);
		PKB::getPKBInstance()->setStmtModifies(11, 8);
		PKB::getPKBInstance()->setStmtModifies(13, 9);
		PKB::getPKBInstance()->setStmtModifies(18, 10);

		PKB::getPKBInstance()->setProcModifies(1, 3);
		PKB::getPKBInstance()->setProcModifies(1, 4);
		PKB::getPKBInstance()->setProcModifies(1, 8);
		PKB::getPKBInstance()->setProcModifies(1, 9);
		PKB::getPKBInstance()->setProcModifies(1, 10);

		//init uses
		PKB::getPKBInstance()->setUses(1, 1, 1);
		PKB::getPKBInstance()->setUses(1, 1, 2);
		PKB::getPKBInstance()->setUses(1, 2, 3);
		PKB::getPKBInstance()->setUses(1, 3, 4);
		PKB::getPKBInstance()->setUses(1, 5, 5);
		PKB::getPKBInstance()->setUses(1, 17, 5);

		PKB::getPKBInstance()->setStmtUses(8, 6);
		PKB::getPKBInstance()->setStmtUses(9, 7);
		PKB::getPKBInstance()->setStmtUses(11, 8);
		PKB::getPKBInstance()->setStmtUses(13, 9);
		PKB::getPKBInstance()->setStmtUses(18, 9);

		PKB::getPKBInstance()->setProcUses(1, 3);
		PKB::getPKBInstance()->setProcUses(1, 4);
		PKB::getPKBInstance()->setProcUses(1, 8);
		PKB::getPKBInstance()->setProcUses(1, 9);
		PKB::getPKBInstance()->setProcUses(1, 10);

		//setAssignPattern
		PKB::getPKBInstance()->setAssignPattern(1, "x", "a+b");
		PKB::getPKBInstance()->setAssignPattern(3, "y", "a*2+3");
		PKB::getPKBInstance()->setAssignPattern(5, "x", "x+c");
		PKB::getPKBInstance()->setAssignPattern(13, "z", "x-y");
		PKB::getPKBInstance()->setAssignPattern(14, "v", "(a+b)-c");
		PKB::getPKBInstance()->setAssignPattern(15, "s", "v+z-a");
		PKB::getPKBInstance()->setAssignPattern(19, "x", "var1+var2*var3");
		PKB::getPKBInstance()->setAssignPattern(20, "x", "1");

		//setWhilePattern
		PKB::getPKBInstance()->setWhilePattern(6, 1);
		PKB::getPKBInstance()->setWhilePattern(10, 5);
		PKB::getPKBInstance()->setWhilePattern(16, 6);


		PKB::getPKBInstance()->sortUsesModifiesMap();


	}

	TEST_METHOD(getAllChildrenTest) {

		list<int> actualList, expectedList;

		Assert::IsTrue(PKB::getPKBInstance()->getAllChildren(7) == list<int>());
		actualList.clear();
		expectedList.clear();

		actualList = PKB::getPKBInstance()->getAllChildren(3);
		expectedList.clear();
		expectedList.push_back(7);
		Assert::IsFalse(actualList == expectedList);
		actualList.clear();
		expectedList.clear();


		expectedList.clear();
		actualList = PKB::getPKBInstance()->getAllChildren(14);
		expectedList.push_back(16);
		expectedList.push_back(17);
		expectedList.push_back(18);
		Assert::IsTrue(actualList == expectedList);


		expectedList.clear();
		actualList.clear();
		actualList = PKB::getPKBInstance()->getAllChildren(14);
		expectedList.push_back(16);
		expectedList.push_back(17);
		expectedList.push_back(18);
		Assert::IsTrue(actualList == expectedList);


		return;
	}

	TEST_METHOD(getModifiedByTest) {
		list<int> actualList, expectedList;
		int stmtNo;
		actualList.clear();
		expectedList.clear();

		stmtNo = 1;
		actualList = PKB::getPKBInstance()->getModifiedBy(stmtNo);
		expectedList.push_back(1);
		expectedList.push_back(2);
		Assert::IsTrue(actualList == expectedList);


		actualList.clear();
		expectedList.clear();
		stmtNo = 18;
		actualList = PKB::getPKBInstance()->getModifiedBy(stmtNo);
		expectedList.push_back(10);
		Assert::IsTrue(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		stmtNo = 18;
		actualList = PKB::getPKBInstance()->getModifiedBy(stmtNo);
		expectedList.push_back(10);
		expectedList.push_back(2);
		Assert::IsFalse(actualList == expectedList);


		return;
	}



	TEST_METHOD(getModifiesTest) {
		list<int> actualList, expectedList;
		string varName;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10

		actualList.clear();
		expectedList.clear();
		varName = "y";
		actualList = PKB::getPKBInstance()->getModifies(varName);
		expectedList.push_back(13);
		Assert::IsTrue(actualList == expectedList);

		expectedList.clear();
		varName = "e";
		actualList = PKB::getPKBInstance()->getModifies(varName);
		expectedList.push_back(5);
		expectedList.push_back(7);
		expectedList.push_back(17);
		Assert::IsTrue(actualList == expectedList);
		actualList.clear();
		expectedList.clear();

		return;
	}



	TEST_METHOD(isUsesValidTest) {
		string varName = "y";
		Assert::IsTrue(PKB::getPKBInstance()->isUsesValid(13, varName));
		Assert::IsTrue(PKB::getPKBInstance()->isUsesValid(18, varName));
		Assert::IsFalse(PKB::getPKBInstance()->isUsesValid(14, varName));

		return;
	}


	TEST_METHOD(isProcUsesValidTest) {
		string procName, varName;
		procName = "First";

		varName = "y";
		Assert::IsTrue(PKB::getPKBInstance()->isProcUsesValid(procName, varName));

		varName = "e";
		Assert::IsTrue(PKB::getPKBInstance()->isProcUsesValid(procName, varName));

		varName = "w";
		Assert::IsFalse(PKB::getPKBInstance()->isProcUsesValid(procName, varName));

		procName = "Third";
		varName = "e";
		Assert::IsFalse(PKB::getPKBInstance()->isProcUsesValid(procName, varName));

		return;
	}

	TEST_METHOD(isProcModifiesValidTest) {
		string procName, varName;
		procName = "First";

		varName = "y";
		Assert::IsTrue(PKB::getPKBInstance()->isProcModifiesValid(procName, varName));

		varName = "e";
		Assert::IsTrue(PKB::getPKBInstance()->isProcModifiesValid(procName, varName));

		varName = "w";
		Assert::IsFalse(PKB::getPKBInstance()->isProcModifiesValid(procName, varName));

		procName = "Third";
		varName = "e";
		Assert::IsFalse(PKB::getPKBInstance()->isProcModifiesValid(procName, varName));

		return;
	}


	TEST_METHOD(getUsesTest) {
		list<int> actualList, expectedList;
		string varName;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10

		actualList.clear();
		expectedList.clear();
		varName = "y";
		actualList = PKB::getPKBInstance()->getUses(varName);
		expectedList.push_back(13);
		expectedList.push_back(18);
		Assert::IsTrue(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		varName = "e";
		actualList = PKB::getPKBInstance()->getUses(varName);
		expectedList.push_back(5);
		expectedList.push_back(17);
		Assert::IsTrue(actualList == expectedList);

		//not empty
		varName = "v";
		Assert::IsFalse(PKB::getPKBInstance()->getUses(varName) == list<int>());

		varName = "z";
		Assert::IsTrue(PKB::getPKBInstance()->getUses(varName) == list<int>());

		return;
	}

	TEST_METHOD(getProcUsesTest) {
		list<int> actualList, expectedList;
		string varName;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10

		actualList.clear();
		expectedList.clear();
		varName = "e";
		actualList = PKB::getPKBInstance()->getProcUses(varName);
		expectedList.push_back(1);
		//Assert::IsTrue(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		varName = "x";
		actualList = PKB::getPKBInstance()->getProcUses(varName);
		expectedList.push_back(1);
		Assert::IsTrue(actualList == expectedList);

		//not empty
		varName = "z";
		Assert::IsFalse(PKB::getPKBInstance()->getProcUses(varName) == list<int>());

		varName = "v";
		Assert::IsTrue(PKB::getPKBInstance()->getProcUses(varName) == list<int>());

		return;
	}


	TEST_METHOD(getUsedByTest) {
		list<int> actualList, expectedList;
		int stmtNo;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10

		actualList.clear();
		expectedList.clear();
		stmtNo = 1;
		actualList = PKB::getPKBInstance()->getUsedBy(1);
		expectedList.push_back(1);
		expectedList.push_back(2);
		Assert::IsTrue(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		stmtNo = 2;
		actualList = PKB::getPKBInstance()->getUsedBy(stmtNo);
		expectedList.push_back(3);
		Assert::IsTrue(actualList == expectedList);

		//not empty
		stmtNo = 18;
		Assert::IsFalse(PKB::getPKBInstance()->getUsedBy(stmtNo) == list<int>());

		stmtNo = 20;
		Assert::IsTrue(PKB::getPKBInstance()->getUsedBy(stmtNo) == list<int>());

		return;
	}

	TEST_METHOD(getProcUsedByTest) {
		list<int> actualList, expectedList;
		string procName;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10


		actualList.clear();
		expectedList.clear();
		procName = "First";

		Assert::IsFalse(PKB::getPKBInstance()->getProcUsedBy(procName) == list<int>());

		actualList = PKB::getPKBInstance()->getProcUsedBy(procName);
		expectedList.push_back(1);
		expectedList.push_back(2);
		expectedList.push_back(3);
		expectedList.push_back(4);
		expectedList.push_back(5);
		expectedList.push_back(8);
		expectedList.push_back(9);
		expectedList.push_back(10);
		Assert::IsTrue(actualList == expectedList);


		actualList.clear();
		expectedList.clear();
		actualList = PKB::getPKBInstance()->getProcUsedBy(procName);
		expectedList.push_back(1);
		expectedList.push_back(2);
		expectedList.push_back(3);
		expectedList.push_back(4);
		expectedList.push_back(5);
		expectedList.push_back(8);
		expectedList.push_back(9);
		expectedList.push_back(10);
		expectedList.push_back(11);
		Assert::IsFalse(actualList == expectedList);


		procName = "Second";
		Assert::IsTrue(PKB::getPKBInstance()->getProcUsedBy(procName) == list<int>());

		return;
	}


	TEST_METHOD(getProcModifiesTest) {
		list<int> actualList, expectedList;
		string varName;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10

		actualList.clear();
		expectedList.clear();
		varName = "e";
		actualList = PKB::getPKBInstance()->getProcModifies(varName);
		expectedList.push_back(1);
		Assert::IsTrue(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		varName = "x";
		actualList = PKB::getPKBInstance()->getProcUses(varName);
		expectedList.push_back(1);
		Assert::IsTrue(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		varName = "x";
		actualList = PKB::getPKBInstance()->getProcUses(varName);
		expectedList.push_back(1);
		expectedList.push_back(1);
		Assert::IsFalse(actualList == expectedList);

		actualList.clear();
		expectedList.clear();
		varName = "x";
		actualList = PKB::getPKBInstance()->getProcUses(varName);
		expectedList.push_back(1);
		expectedList.push_back(2);
		Assert::IsFalse(actualList == expectedList);

		//not empty
		varName = "z";
		Assert::IsFalse(PKB::getPKBInstance()->getProcUses(varName) == list<int>());

		varName = "v";
		Assert::IsTrue(PKB::getPKBInstance()->getProcUses(varName) == list<int>());

		return;
	}

	TEST_METHOD(getProcModifiedByTest) {
		list<int> actualList, expectedList;
		string procName;
		//var Table a=1, b=2, c=3, d=4, e=5, v=6, w=7, x=8, y=9, z=10


		actualList.clear();
		expectedList.clear();
		procName = "First";

		Assert::IsFalse(PKB::getPKBInstance()->getProcModifiedBy(procName) == list<int>());

		actualList = PKB::getPKBInstance()->getProcModifiedBy(procName);
		expectedList.push_back(1);
		expectedList.push_back(2);
		expectedList.push_back(3);
		expectedList.push_back(4);
		expectedList.push_back(5);
		expectedList.push_back(8);
		expectedList.push_back(9);
		expectedList.push_back(10);
		Assert::IsTrue(actualList == expectedList);


		actualList.clear();
		expectedList.clear();
		actualList = PKB::getPKBInstance()->getProcModifiedBy(procName);
		expectedList.push_back(1);
		expectedList.push_back(2);
		expectedList.push_back(3);
		expectedList.push_back(4);
		expectedList.push_back(5);
		expectedList.push_back(8);
		expectedList.push_back(9);
		expectedList.push_back(10);
		expectedList.push_back(11);
		Assert::IsFalse(actualList == expectedList);

		procName = "Second";
		Assert::IsTrue(PKB::getPKBInstance()->getProcModifiedBy(procName) == list<int>());

		procName = "Third";
		Assert::IsTrue(PKB::getPKBInstance()->getProcModifiedBy(procName) == list<int>());

		return;
	}

	TEST_METHOD(getAssignPatternStmtNoTest) {

		int side;
		list<int> actualList, expectedList;
		string varName, inputString;

		actualList.clear();
		expectedList.clear();

		//test query stmtNo w LHS
		side = 1;

		inputString = "y";
		actualList = PKB::getPKBInstance()->getAssignPatternStmtNumber(side, inputString);
		expectedList.push_back(3);
		Assert::IsTrue(expectedList == actualList);

		actualList.clear();
		expectedList.clear();
		inputString = "v";
		actualList = PKB::getPKBInstance()->getAssignPatternStmtNumber(side, inputString);
		expectedList.push_back(14);
		Assert::IsTrue(expectedList == actualList);


		//test query stmtNo w RHS
		side = 2;

		inputString = "x+c";
		actualList.clear();
		expectedList.clear();
		actualList = PKB::getPKBInstance()->getAssignPatternStmtNumber(side, inputString);
		expectedList.push_back(5);
		Assert::IsTrue(expectedList == actualList);

		actualList.clear();
		expectedList.clear();
		inputString = "(a+b)-c";
		actualList = PKB::getPKBInstance()->getAssignPatternStmtNumber(side, inputString);
		expectedList.push_back(14);
		Assert::IsTrue(expectedList == actualList);

		return;
	}

	TEST_METHOD(getStmtNoWithStringTest) {
		
		int side;
		string inputString;
		list<int> actualList, expectedList;
		//test query stmtNo w LHS
		side = 1;

		actualList.clear();
		expectedList.clear();
		inputString = "x";
		actualList = PKB::getPKBInstance()->getStmtNoWithString(side, inputString);
		expectedList.push_back(1);
		expectedList.push_back(5);
		expectedList.push_back(19);
		expectedList.push_back(20);
		Assert::IsTrue(actualList == expectedList);

		
		actualList.clear();
		expectedList.clear();
		inputString = "x";
		actualList = PKB::getPKBInstance()->getStmtNoWithString(side, inputString);
		expectedList.push_back(1);
		expectedList.push_back(2);
		expectedList.push_back(5);
		expectedList.push_back(20);
		Assert::IsFalse(actualList == expectedList);

		//test query stmtNo w RHS
		side = 2;

		actualList.clear();
		expectedList.clear();
		inputString = "x";
		actualList = PKB::getPKBInstance()->getStmtNoWithString(side, inputString);
		expectedList.push_back(5);
		expectedList.push_back(13);
		Assert::IsTrue(actualList == expectedList);


		return;
	}



	TEST_METHOD(getWhilePatternStmtNumberTest) {

		list<int> actualList, expectedList;
		string varName;

		actualList.clear();
		expectedList.clear();

		varName = "e";
		actualList = PKB::getPKBInstance()->getWhilePatternStmtNumber(varName);
		expectedList.push_back(10);
		Assert::IsTrue(expectedList == actualList);

		actualList.clear();
		expectedList.clear();
		varName = "a";
		actualList = PKB::getPKBInstance()->getWhilePatternStmtNumber(varName);
		expectedList.push_back(6);
		Assert::IsTrue(expectedList == actualList);

		actualList.clear();
		expectedList.clear();
		varName = "v";
		actualList = PKB::getPKBInstance()->getWhilePatternStmtNumber(varName);
		expectedList.push_back(16);
		Assert::IsTrue(expectedList == actualList);

		actualList.clear();
		expectedList.clear();
		actualList = PKB::getPKBInstance()->getWhilePatternStmtNumber(varName);
		expectedList.push_back(6);
		Assert::IsFalse(expectedList == actualList);

		return;
	}



	TEST_METHOD(getAssignPatternLHSTest) {

		int stmtNo;
		string expectedString, actualString;


		stmtNo = 14;
		actualString = PKB::getPKBInstance()->getAssignPatternLHS(stmtNo);
		expectedString = "v";
		Assert::IsTrue(expectedString == actualString);

		stmtNo = 1;
		actualString = PKB::getPKBInstance()->getAssignPatternLHS(stmtNo);
		expectedString = "x";
		Assert::IsTrue(expectedString == actualString);

		stmtNo = 5;
		actualString = PKB::getPKBInstance()->getAssignPatternLHS(stmtNo);
		expectedString = "x";
		Assert::IsTrue(expectedString == actualString);


		stmtNo = 20;
		actualString = PKB::getPKBInstance()->getAssignPatternLHS(stmtNo);
		expectedString = "x";
		Assert::IsTrue(expectedString == actualString);


		stmtNo = 20;
		actualString = PKB::getPKBInstance()->getAssignPatternLHS(stmtNo);
		expectedString = "v";
		Assert::IsFalse(expectedString == actualString);

		return;
	}

	TEST_METHOD(getAssignPatternRHSTest) {

		int stmtNo;
		string expectedString, actualString;

		stmtNo = 1;
		actualString = PKB::getPKBInstance()->getAssignPatternRHS(stmtNo);
		expectedString = ".a..b.+";
		Assert::IsTrue(expectedString == actualString);

		stmtNo = 3;
		actualString = PKB::getPKBInstance()->getAssignPatternRHS(stmtNo);
		expectedString = ".a..2.*.3.+";
		Assert::IsTrue(expectedString == actualString);

		stmtNo = 15;
		actualString = PKB::getPKBInstance()->getAssignPatternRHS(stmtNo);
		expectedString = ".v..z.+.a.-";
		Assert::IsTrue(expectedString == actualString);

		stmtNo = 19;
		actualString = PKB::getPKBInstance()->getAssignPatternRHS(stmtNo);
		expectedString = ".var1..var2..var3.*+";
		Assert::IsTrue(expectedString == actualString);


		stmtNo = 20;
		actualString = PKB::getPKBInstance()->getAssignPatternRHS(stmtNo);
		expectedString = ".1.";
		Assert::IsTrue(expectedString == actualString);


		stmtNo = 14;
		actualString = PKB::getPKBInstance()->getAssignPatternRHS(stmtNo);
		expectedString = ".a..b.+.c.-";
		Assert::IsTrue(expectedString == actualString);

		return;
	}



	TEST_METHOD(isModifiesValidTest) {
		string varName = "e";
		Assert::IsTrue(PKB::getPKBInstance()->isModifiesValid(5, varName));
		Assert::IsTrue(PKB::getPKBInstance()->isModifiesValid(7, varName));
		Assert::IsTrue(PKB::getPKBInstance()->isModifiesValid(17, varName));
		Assert::IsFalse(PKB::getPKBInstance()->isModifiesValid(18, varName));

		return;
	}


	TEST_METHOD(getVarIDTest) {
		int actual, expected;
		actual = PKB::getPKBInstance()->getVarID("a");
		expected = 1;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("b");
		expected = 2;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("c");
		expected = 3;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("d");
		expected = 4;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("e");
		expected = 5;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("v");
		expected = 6;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("w");
		expected = 7;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("x");
		expected = 8;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("y");
		expected = 9;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("z");
		expected = 10;
		Assert::AreEqual(expected, actual);

		actual = PKB::getPKBInstance()->getVarID("f");
		expected = -1;
		Assert::AreEqual(expected, actual);

		return;
	}

	TEST_METHOD(getFollowsTest)
	{

		int actual, expected;

		actual = PKB::getPKBInstance()->getFollows(2);
		expected = 1;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(3);
		expected = 2;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(4);
		expected = 3;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(5);
		expected = 4;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(6);
		expected = 5;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(8);
		expected = 7;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(10);
		expected = 9;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(12);
		expected = 11;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(14);
		expected = 13;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(15);
		expected = 14;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(17);
		expected = 16;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(18);
		expected = 17;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(19);
		expected = 18;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(20);
		expected = 19;
		Assert::AreEqual(actual, expected);

		//error cases
		actual = PKB::getPKBInstance()->getFollows(21);
		expected = -1;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollows(1);
		expected = -1;
		Assert::AreEqual(actual, expected);

		return;
	}


	TEST_METHOD(getFollowedByTest) {
		int actual, expected;

		actual = PKB::getPKBInstance()->getFollowedBy(1);
		expected = 2;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(2);
		expected = 3;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(3);
		expected = 4;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(4);
		expected = 5;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(5);
		expected = 6;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(7);
		expected = 8;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(9);
		expected = 10;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(11);
		expected = 12;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(13);
		expected = 14;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(14);
		expected = 15;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(16);
		expected = 17;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(17);
		expected = 18;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(18);
		expected = 19;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(19);
		expected = 20;
		Assert::AreEqual(actual, expected);

		//error cases
		actual = PKB::getPKBInstance()->getFollowedBy(6);
		expected = -1;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(20);
		expected = -1;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getFollowedBy(21);
		expected = -1;
		Assert::AreEqual(actual, expected);

		return;


	}

	TEST_METHOD(isFollowsValidTest) {
		Assert::IsTrue(PKB::getPKBInstance()->isFollowsValid(1, 2));

		Assert::IsTrue(PKB::getPKBInstance()->isFollowsValid(3, 4));

		Assert::IsTrue(PKB::getPKBInstance()->isFollowsValid(9, 10));

		Assert::IsTrue(PKB::getPKBInstance()->isFollowsValid(11, 12));

		Assert::IsTrue(PKB::getPKBInstance()->isFollowsValid(19, 20));

		Assert::IsFalse(PKB::getPKBInstance()->isFollowsValid(2, 1));

		Assert::IsFalse(PKB::getPKBInstance()->isFollowsValid(20, 21));


		return;
	}


	TEST_METHOD(getParentTest) {

		int actual, expected;

		actual = PKB::getPKBInstance()->getParent(7);
		expected = 3;
		Assert::AreEqual(actual, expected);

		actual = PKB::getPKBInstance()->getParent(8);
		expected = 3;
		Assert::AreEqual(actual, expected);


		actual = PKB::getPKBInstance()->getParent(9);
		expected = -1;
		Assert::AreEqual(actual, expected);
		return;
	}


	TEST_METHOD(isParentValidTest) {

		int actual, expected;

		Assert::IsTrue(PKB::getPKBInstance()->isParentValid(3, 7));
		Assert::IsTrue(PKB::getPKBInstance()->isParentValid(3, 8));
		Assert::IsTrue(PKB::getPKBInstance()->isParentValid(14, 16));
		Assert::IsTrue(PKB::getPKBInstance()->isParentValid(14, 17));
		Assert::IsTrue(PKB::getPKBInstance()->isParentValid(14, 18));

		Assert::IsFalse(PKB::getPKBInstance()->isParentValid(14, 19));
		Assert::IsFalse(PKB::getPKBInstance()->isParentValid(3, 9));

		return;
	}


	};
}