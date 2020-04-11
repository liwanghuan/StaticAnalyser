#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <../SPA Front End/Front End Controller/FrontEndController.h>
#include <../PKB/PKB.h>
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTesting
{
	TEST_CLASS(ParserTest1)
	{
	public:

		// Parser Test - Able to add the following Source code with only assign statment
		/*procedure Example {
			  x = y;
			  a = b + c;
			  y = d + a +k;
			}*/

		TEST_METHOD(integrationTestOnlyAssign1Source)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			frontEndController.createCFG();
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(3, 1, 1, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			//Check total number(Size of stmts)
			int actualSourceSize, expectedSourceSize;
			actualSourceSize = PKB::getPKBInstance()->getTotalNumOfProgLine();
			expectedSourceSize = 3;
			Assert::IsTrue(expectedSourceSize == actualSourceSize);

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[2] = ".x..y.+";
			expectedAssignRHSMap[3] = ".a..b.+.c.+";
			for (int i = 1; i <= 3; i++) {
				 Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(i), expectedAssignRHSMap[i]);
			}

			map<int, string> expectedAssignLHSMap;
			expectedAssignLHSMap[1] = "x";
			expectedAssignLHSMap[2] = "z";
			expectedAssignLHSMap[3] = "i";
			for (int i = 1; i <= 3; i++) {
				Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(i), expectedAssignLHSMap[i]);
			}
			
			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());

			//getVarID test
			int actual, expected;
			actual = PKB::getPKBInstance()->getVarID("x");
			expected = 1;
			Assert::AreEqual(expected, actual);

			actual = PKB::getPKBInstance()->getVarID("z");
			expected = 2;
			Assert::AreEqual(expected, actual);

			actual = PKB::getPKBInstance()->getVarID("y");
			expected = 3;
			Assert::AreEqual(expected, actual);

			actual = PKB::getPKBInstance()->getVarID("i");
			expected = 4;
			Assert::AreEqual(expected, actual);

			actual = PKB::getPKBInstance()->getVarID("a");
			expected = 5;
			Assert::AreEqual(expected, actual);

			actual = PKB::getPKBInstance()->getVarID("b");
			expected = 6;
			Assert::AreEqual(expected, actual);

			actual = PKB::getPKBInstance()->getVarID("c");
			expected = 7;
			Assert::AreEqual(expected, actual);

			//check uses x=1, z=2, y=3, i=4, a=5, b=6, c=7
			list<int> expectedList, actualList;
			actualList.clear();
			expectedList.clear();
			actualList = PKB::getPKBInstance()->getUsedBy(2);
			expectedList.push_back(1);
			expectedList.push_back(3);
			Assert::IsTrue(actualList == expectedList);

			
			//check modifies
			actualList.clear();
			expectedList.clear();
			actualList = PKB::getPKBInstance()->getModifiedBy(1);
			expectedList.push_back(1);
			Assert::IsTrue(actualList == expectedList);
			

			//checking StmtType
			string actualString, expectedString;

			actualString = PKB::getPKBInstance()->getStmtType(1);
			expectedString = "assign";
			Assert::IsTrue(expectedString == actualString);
			
			actualString = PKB::getPKBInstance()->getStmtType(2);
			expectedString = "assign";
			Assert::IsTrue(expectedString == actualString);

			actualString = PKB::getPKBInstance()->getStmtType(3);
			expectedString = "while";
			Assert::IsFalse(expectedString == actualString);

			actualString = PKB::getPKBInstance()->getStmtType(3);
			expectedString = "assign";
			Assert::IsTrue(expectedString == actualString);
			
			//Test getAffectedBy
			actualList.clear();
			expectedList.clear();
			actualList = PKB::getPKBInstance()->getAffectedBy(1);
			expectedList.push_back(2);
			Assert::IsTrue(actualList == expectedList);

			//Test getAffects
			actualList.clear();
			expectedList.clear();
			actualList = PKB::getPKBInstance()->getAffects(2);
			expectedList.push_back(1);
			Assert::IsTrue(actualList == expectedList);
		}

		TEST_METHOD(integrationTestOnlyAssignMultipleSource)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Index{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "y = 3;\n";
			sourceCode += "d = x + y * 13;\n";
			sourceCode += "z = x * y + d + 4;\n";
			sourceCode += "call Example;\n";
			sourceCode += "x = z;\n";
			sourceCode += "y = d + 2;\n";
			sourceCode += "}\n";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 18;\n";
			sourceCode += "j = 1;\n";
			sourceCode += "i = x * 1 + 394 - 230 * x;\n";
			sourceCode += "j = d - j;\n";
			sourceCode += "}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Index"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "y=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "d=x+y*13"));
			expectedSourceList.push_back(Statement(4, 1, 0, "assign", "z=x*y+d+4"));
			expectedSourceList.push_back(Statement(5, 1, 0, "call", "Example"));
			expectedSourceList.push_back(Statement(6, 1, 0, "assign", "x=z"));
			expectedSourceList.push_back(Statement(7, 1, 1, "assign", "y=d+2"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(8, 1, 0, "assign", "x=18"));
			expectedSourceList.push_back(Statement(9, 1, 0, "assign", "j=1"));
			expectedSourceList.push_back(Statement(10, 1, 0, "assign", "i=x*1+394-230*x"));
			expectedSourceList.push_back(Statement(11, 1, 1, "assign", "j=d-j"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			
			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[2] = ".3.";
			expectedAssignRHSMap[3] = ".x..y..13.*+";
			expectedAssignRHSMap[4] = ".x..y.*.d.+.4.+";
			expectedAssignRHSMap[6] = ".z.";
			expectedAssignRHSMap[7] = ".d..2.+";
			expectedAssignRHSMap[8] = ".18.";
			expectedAssignRHSMap[9] = ".1.";
			expectedAssignRHSMap[10] = ".x..1.*.394.+.230..x.*-";
			expectedAssignRHSMap[11] = ".d..j.-";

			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(1), expectedAssignRHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(2), expectedAssignRHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(3), expectedAssignRHSMap[3]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(4), expectedAssignRHSMap[4]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(7), expectedAssignRHSMap[7]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(8), expectedAssignRHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(9), expectedAssignRHSMap[9]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(10), expectedAssignRHSMap[10]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(11), expectedAssignRHSMap[11]);

			map<int, string> expectedAssignLHSMap;
			expectedAssignLHSMap[1] = "x";
			expectedAssignLHSMap[2] = "y";
			expectedAssignLHSMap[3] = "d";
			expectedAssignLHSMap[4] = "z";
			expectedAssignLHSMap[6] = "x";
			expectedAssignLHSMap[7] = "y";
			expectedAssignLHSMap[8] = "x";
			expectedAssignLHSMap[9] = "j";
			expectedAssignLHSMap[10] = "i";
			expectedAssignLHSMap[11] = "j";

			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(1), expectedAssignLHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(2), expectedAssignLHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(3), expectedAssignLHSMap[3]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(4), expectedAssignLHSMap[4]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(6), expectedAssignLHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(7), expectedAssignLHSMap[7]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(8), expectedAssignLHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(9), expectedAssignLHSMap[9]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(10), expectedAssignLHSMap[10]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(11), expectedAssignLHSMap[11]);
			

			//check no. of variables
			Assert::AreEqual(6, PKB::getPKBInstance()->getVarTableSize());
		}

		TEST_METHOD(integrationTestOnlyOneWhile1Source)
		{
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "while i {\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(2, 2, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(3, 2, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(4, 2, 2, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();


			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[2] = ".2.";
			expectedAssignRHSMap[3] = ".x..y.+";
			expectedAssignRHSMap[4] = ".a..b.+.c.+";
			for (int i = 2; i <= 4; i++) {
				Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(i), expectedAssignRHSMap[i]);
			}

			map<int, string> expectedWhileMap;
			expectedWhileMap[1] = "i";
			Assert::AreEqual(PKB::getPKBInstance()->getWhilePatternUses(1), expectedWhileMap[1]);

			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());
		}

		TEST_METHOD(integrationTestOnlyOneWhileMultipleSource)
		{
			string sourceCode = "";
			sourceCode += "procedure First{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3;\n";
			sourceCode += "call Second;\n";
			sourceCode += "}\n";
			sourceCode += "procedure Second{\n";
			sourceCode += "while i {\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "First"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 1, "call", "Second"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Second"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(7, 2, 2, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			
			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[2] = ".3.";
			expectedAssignRHSMap[5] = ".2.";
			expectedAssignRHSMap[6] = ".x..y.+";
			expectedAssignRHSMap[7] = ".a..b.+.c.+";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(1), expectedAssignRHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(2), expectedAssignRHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(5), expectedAssignRHSMap[5]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(7), expectedAssignRHSMap[7]);
			

			map<int, string> expectedWhileMap;
			expectedWhileMap[4] = "i";
			Assert::AreEqual(PKB::getPKBInstance()->getWhilePatternUses(4), expectedWhileMap[4]);
			
			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());
		}

		TEST_METHOD(integrationTestOnlyOneIf1Source)
		{
			string sourceCode = "";
			
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "if x then {\n";
			sourceCode += "z = x + 24;\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "z = x * 2 + y;\n";
			sourceCode += "}\n";
			sourceCode += "z = x + y;\n";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "if", "x"));
			expectedSourceList.push_back(Statement(3, 2, 1, "assign", "z=x+24"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(4, 2, 1, "assign", "z=x*2+y"));
			expectedSourceList.push_back(Statement(5, 1, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(6, 1, 1, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			
			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[3] = ".x..24.+";
			expectedAssignRHSMap[4] = ".x..2.*.y.+";
			expectedAssignRHSMap[5] = ".x..y.+";
			expectedAssignRHSMap[6] = ".a..b.+.c.+";
			for (int i = 1; i <= 6; i++) {
				if (i == 2)
					continue;
				Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(i), expectedAssignRHSMap[i]);
			}

			map<int, string> expectedIfMap;
			expectedIfMap[2] = "x";
			Assert::AreEqual(PKB::getPKBInstance()->getIfPatternUses(2), expectedIfMap[2]);

			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());
			return;
		}

		TEST_METHOD(integrationTestOnlyOneIfMultipleSource)
		{
			string sourceCode = "";
			sourceCode += "procedure First{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3;\n";
			sourceCode += "call Second;\n";
			sourceCode += "}\n";
			sourceCode += "procedure Second{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "if x then {\n";
			sourceCode += "z = x + 24;\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "z = x * 2 + y;\n";
			sourceCode += "}\n";
			sourceCode += "z = x + y;\n";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";


			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "First"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 1, "call", "Second"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Second"));
			expectedSourceList.push_back(Statement(4, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(5, 1, 0, "if", "x"));
			expectedSourceList.push_back(Statement(6, 2, 1, "assign", "z=x+24"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(7, 2, 1, "assign", "z=x*2+y"));
			expectedSourceList.push_back(Statement(8, 1, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(9, 1, 1, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			
			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[2] = ".3.";
			expectedAssignRHSMap[4] = ".2.";
			expectedAssignRHSMap[6] = ".x..24.+";
			expectedAssignRHSMap[7] = ".x..2.*.y.+";
			expectedAssignRHSMap[8] = ".x..y.+";
			expectedAssignRHSMap[9] = ".a..b.+.c.+";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(1), expectedAssignRHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(2), expectedAssignRHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(4), expectedAssignRHSMap[4]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(7), expectedAssignRHSMap[7]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(8), expectedAssignRHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(9), expectedAssignRHSMap[9]);

			
			map<int, string> expectedIfMap;
			expectedIfMap[5] = "x";
			Assert::AreEqual(PKB::getPKBInstance()->getIfPatternUses(5), expectedIfMap[5]);
			
			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());
			return;
		}


		TEST_METHOD(integrationTestMultipleWhile1Source)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "while i {\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";
			sourceCode += "while i {\n";
			sourceCode += "x = 2;\n";
			sourceCode += "while i {\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "}\n";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(2, 2, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(3, 2, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(4, 2, 1, "assign", "i=a+b+c"));
			expectedSourceList.push_back(Statement(5, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(7, 2, 0, "while", "i"));
			expectedSourceList.push_back(Statement(8, 3, 1, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(9, 2, 2, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			// Check assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[2] = ".2.";
			expectedAssignRHSMap[3] = ".x..y.+";
			expectedAssignRHSMap[4] = ".a..b.+.c.+";
			expectedAssignRHSMap[6] = ".2.";
			expectedAssignRHSMap[8] = ".x..y.+";
			expectedAssignRHSMap[9] = ".a..b.+.c.+";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(2), expectedAssignRHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(3), expectedAssignRHSMap[3]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(4), expectedAssignRHSMap[4]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(8), expectedAssignRHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(9), expectedAssignRHSMap[9]);

			map<int, string> expectedAssignLHSMap;
			expectedAssignLHSMap[2] = "x";
			expectedAssignLHSMap[3] = "z";
			expectedAssignLHSMap[4] = "i";
			expectedAssignLHSMap[6] = "x";
			expectedAssignLHSMap[8] = "z";
			expectedAssignLHSMap[9] = "i";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(2), expectedAssignLHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(3), expectedAssignLHSMap[3]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(4), expectedAssignLHSMap[4]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(6), expectedAssignLHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(8), expectedAssignLHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(9), expectedAssignLHSMap[9]);

			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());
		}

		TEST_METHOD(integrationTestMultipleWhileMultipleSource)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure First{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3;\n";
			sourceCode += "call Second;\n";
			sourceCode += "}\n";
			sourceCode += "procedure Second{\n";
			sourceCode += "while i {\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";
			sourceCode += "while i {\n";
			sourceCode += "x = 2;\n";
			sourceCode += "while i {\n";
			sourceCode += "z = x + y\n;";
			sourceCode += "}\n";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "First"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 1, "call", "Second"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Second"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(7, 2, 1, "assign", "i=a+b+c"));
			expectedSourceList.push_back(Statement(8, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(9, 2, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(10, 2, 0, "while", "i"));
			expectedSourceList.push_back(Statement(11, 3, 1, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(12, 2, 2, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();
			
			// Check assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[2] = ".3.";
			expectedAssignRHSMap[5] = ".2.";
			expectedAssignRHSMap[6] = ".x..y.+";
			expectedAssignRHSMap[7] = ".a..b.+.c.+";
			expectedAssignRHSMap[9] = ".2.";
			expectedAssignRHSMap[11] = ".x..y.+";
			expectedAssignRHSMap[12] = ".a..b.+.c.+";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(1), expectedAssignRHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(2), expectedAssignRHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(5), expectedAssignRHSMap[5]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(7), expectedAssignRHSMap[7]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(9), expectedAssignRHSMap[9]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(11), expectedAssignRHSMap[11]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(12), expectedAssignRHSMap[12]);

			map<int, string> expectedAssignLHSMap;
			expectedAssignLHSMap[1] = "x";
			expectedAssignLHSMap[2] = "z";
			expectedAssignLHSMap[5] = "x";
			expectedAssignLHSMap[6] = "z";
			expectedAssignLHSMap[7] = "i";
			expectedAssignLHSMap[9] = "x";
			expectedAssignLHSMap[11] = "z";
			expectedAssignLHSMap[12] = "i";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(1), expectedAssignLHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(2), expectedAssignLHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(5), expectedAssignLHSMap[5]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(6), expectedAssignLHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(7), expectedAssignLHSMap[7]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(9), expectedAssignLHSMap[9]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(11), expectedAssignLHSMap[11]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternLHS(12), expectedAssignLHSMap[12]);
			
			//check no. of variables
			Assert::AreEqual(7, PKB::getPKBInstance()->getVarTableSize());
		}

		TEST_METHOD(integrationTestMultipleIf1Source)
		{
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "if x then {\n";
			sourceCode += "z = x + 24;\n";
			sourceCode += "if z then {\n";
			sourceCode += "u = y + 2 * z;\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "u = 1;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "z = x * 2 + y;\n";
			sourceCode += "}\n";
			sourceCode += "z = x + y;\n";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1	, 0, "if", "x"));
			expectedSourceList.push_back(Statement(3, 2, 0, "assign", "z=x+24"));
			expectedSourceList.push_back(Statement(4, 2, 0, "if", "z"));
			expectedSourceList.push_back(Statement(5, 3, 1, "assign", "u=y+2*z"));
			expectedSourceList.push_back(Statement(-1, 2, 0, "else", ""));
			expectedSourceList.push_back(Statement(6, 3, 2, "assign", "u=1"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(7, 2, 1, "assign", "z=x*2+y"));
			expectedSourceList.push_back(Statement(8, 1, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(9, 1, 1, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			
			// Test assign statements
			map<int, string> expectedAssignRHSMap;

			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[3] = ".x..24.+";
			expectedAssignRHSMap[5] = ".y..2..z.*+";
			expectedAssignRHSMap[6] = ".1.";
			expectedAssignRHSMap[7] = ".x..2.*.y.+";
			expectedAssignRHSMap[8] = ".x..y.+";
			expectedAssignRHSMap[9] = ".a..b.+.c.+";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(1), expectedAssignRHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(3), expectedAssignRHSMap[3]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(5), expectedAssignRHSMap[5]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(7), expectedAssignRHSMap[7]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(8), expectedAssignRHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(9), expectedAssignRHSMap[9]);
		
			map<int, string> expectedIfMap;
			expectedIfMap[2] = "x";
			expectedIfMap[4] = "z";
			Assert::AreEqual(PKB::getPKBInstance()->getIfPatternUses(2), expectedIfMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getIfPatternUses(4), expectedIfMap[4]);

			//check no. of variables
			Assert::AreEqual(8, PKB::getPKBInstance()->getVarTableSize());
			return;
		}

		TEST_METHOD(integrationTestMultipleIfMultipleSource)
		{
			string sourceCode = "";
			sourceCode += "procedure First{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3;\n";
			sourceCode += "call Second;\n";
			sourceCode += "}\n";
			sourceCode += "procedure Second{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "if x then {\n";
			sourceCode += "z = x + 24;\n";
			sourceCode += "if z then {\n";
			sourceCode += "u = y + 2 * z;\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "u = 1;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "z = x * 2 + y;\n";
			sourceCode += "}\n";
			sourceCode += "z = x + y;\n";
			sourceCode += "i = a + b + c;\n";
			sourceCode += "}\n";


			// Initialize actual and expected lists
			FrontEndController frontEndController;

			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "First"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 1, "call", "Second"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Second"));
			expectedSourceList.push_back(Statement(4, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(5, 1, 0, "if", "x"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=x+24"));
			expectedSourceList.push_back(Statement(7, 2, 0, "if", "z"));
			expectedSourceList.push_back(Statement(8, 3, 1, "assign", "u=y+2*z"));
			expectedSourceList.push_back(Statement(-1, 2, 0, "else", ""));
			expectedSourceList.push_back(Statement(9, 3, 2, "assign", "u=1"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(10, 2, 1, "assign", "z=x*2+y"));
			expectedSourceList.push_back(Statement(11, 1, 0, "assign", "z=x+y"));
			expectedSourceList.push_back(Statement(12, 1, 1, "assign", "i=a+b+c"));

			// Check if expected and actual lists having same size
			Assert::AreEqual(true, actualSourceList.size() == expectedSourceList.size());

			// Compare expected and actual lists by iterating through both lists
			for (int i = 0; i < expectedSourceList.size(); i++) {
				Assert::AreEqual(actualSourceList.at(i).getStatementNum(), expectedSourceList.at(i).getStatementNum());
				Assert::AreEqual(actualSourceList.at(i).getstatementType(), expectedSourceList.at(i).getstatementType());
				Assert::AreEqual(actualSourceList.at(i).getStatementData(), expectedSourceList.at(i).getStatementData());
				Assert::AreEqual(actualSourceList.at(i).getNumOfCloseBraces(), expectedSourceList.at(i).getNumOfCloseBraces());
				Assert::AreEqual(actualSourceList.at(i).getStatementLevel(), expectedSourceList.at(i).getStatementLevel());
			}
			expectedSourceList.clear();
			actualSourceList.clear();

			
			// Test assign statements
			map<int, string> expectedAssignRHSMap;
			expectedAssignRHSMap[1] = ".2.";
			expectedAssignRHSMap[2] = ".3.";
			expectedAssignRHSMap[4] = ".2.";
			expectedAssignRHSMap[6] = ".x..24.+";
			expectedAssignRHSMap[8] = ".y..2..z.*+";
			expectedAssignRHSMap[9] = ".1.";
			expectedAssignRHSMap[10] = ".x..2.*.y.+";
			expectedAssignRHSMap[11] = ".x..y.+";
			expectedAssignRHSMap[12] = ".a..b.+.c.+";
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(1), expectedAssignRHSMap[1]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(2), expectedAssignRHSMap[2]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(4), expectedAssignRHSMap[4]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(6), expectedAssignRHSMap[6]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(8), expectedAssignRHSMap[8]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(9), expectedAssignRHSMap[9]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(10), expectedAssignRHSMap[10]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(11), expectedAssignRHSMap[11]);
			Assert::AreEqual(PKB::getPKBInstance()->getAssignPatternRHS(12), expectedAssignRHSMap[12]);
			
			
			map<int, string> expectedIfMap;
			expectedIfMap[5] = "x";
			expectedIfMap[7] = "z";
			Assert::AreEqual(PKB::getPKBInstance()->getIfPatternUses(5), expectedIfMap[5]);
			Assert::AreEqual(PKB::getPKBInstance()->getIfPatternUses(7), expectedIfMap[7]);
			
			//check no. of variables
			Assert::AreEqual(8, PKB::getPKBInstance()->getVarTableSize());
			return;
		}

		TEST_METHOD(integrationTestMultipleWhileAffects)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Source3{\n";
			sourceCode += "a = 1;\n";
			sourceCode += "b = 2;\n";
			sourceCode += "c = 3;\n";
			sourceCode += "d = 4;\n";
			sourceCode += "e = 5;\n";
			sourceCode += "while a {\n";
			sourceCode += "d = c + d;\n";
			sourceCode += "while b {\n";
			sourceCode += "c = c + a + b;";
			sourceCode += "a = b;\n";
			sourceCode += "c = a;\n";
			sourceCode += "}\n";
			sourceCode += "c = 2;\n";
			sourceCode += "b = a;\n";
			sourceCode += "e = c;\n";
			sourceCode += "while c {\n";
			sourceCode += "a = b + 1;\n";
			sourceCode += "}\n";
			sourceCode += "a = a + 1;\n";
			sourceCode += "}\n";
			sourceCode += "a = 12;\n";
			sourceCode += "b = 2;\n";
			sourceCode += "c = d + e;\n";
			sourceCode += "while b {\n";
			sourceCode += "c = 2;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";

			// Initialize actual and expected lists
			FrontEndController frontEndController;
			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			frontEndController.createCFG();
			vector<Statement> expectedSourceList;

			list<int> expectedUseList, actualUseList;
			actualUseList.clear();
			expectedUseList.clear();
			actualUseList = PKB::getPKBInstance()->getUsedBy(7);
			expectedUseList.push_back(3);
			expectedUseList.push_back(4);
			Assert::IsTrue(actualUseList == expectedUseList);


			//check modifies
			list<int> expectedModifyList, actualModifyList;
			actualModifyList.clear();
			expectedModifyList.clear();
			actualModifyList = PKB::getPKBInstance()->getModifies("c");
			expectedModifyList.push_back(3);
			expectedModifyList.push_back(6);
			expectedModifyList.push_back(8);
			expectedModifyList.push_back(9);
			expectedModifyList.push_back(11);
			expectedModifyList.push_back(12);
			expectedModifyList.push_back(20);
			expectedModifyList.push_back(21);
			expectedModifyList.push_back(22);
			Assert::IsTrue(actualModifyList == expectedModifyList);

			actualModifyList.clear();
			expectedModifyList.clear();
			actualModifyList = PKB::getPKBInstance()->getModifies("d");
			expectedModifyList.push_back(4);
			expectedModifyList.push_back(6);
			expectedModifyList.push_back(7);
			Assert::IsTrue(actualModifyList == expectedModifyList);

			list<int> actualAffectList, expectedAffectList;
			//Test getAffectedBy

			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(1);
			actualAffectList.sort();
			expectedAffectList.push_back(9);
			expectedAffectList.push_back(13);
			expectedAffectList.push_back(17);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(2);
			actualAffectList.sort();
			expectedAffectList.push_back(9);
			expectedAffectList.push_back(10);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(3);
			actualAffectList.sort();
			expectedAffectList.push_back(7);
			expectedAffectList.push_back(9);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(4);
			actualAffectList.sort();
			expectedAffectList.push_back(7);
			expectedAffectList.push_back(20);
			Assert::IsTrue(actualAffectList == expectedAffectList);
			
			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(5);
			actualAffectList.sort();
			expectedAffectList.push_back(20);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(7);
			actualAffectList.sort();
			expectedAffectList.push_back(7);
			expectedAffectList.push_back(20);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			actualAffectList.clear();
			expectedAffectList.clear();

			//empty list
			actualAffectList = PKB::getPKBInstance()->getAffectedBy(9);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			//Test getAffects (while loop affects itself)

			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffects(7);
			expectedAffectList.push_back(3);
			expectedAffectList.push_back(4);
			expectedAffectList.push_back(7);
			expectedAffectList.push_back(12);
			Assert::IsTrue(actualAffectList == expectedAffectList);


			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffects(9);
			expectedAffectList.push_back(1);
			expectedAffectList.push_back(2);
			expectedAffectList.push_back(3);
			expectedAffectList.push_back(10);
			expectedAffectList.push_back(11);
			expectedAffectList.push_back(12);
			expectedAffectList.push_back(13);
			expectedAffectList.push_back(17);
			Assert::IsTrue(actualAffectList == expectedAffectList);


			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffects(17);
			actualAffectList.sort();
			expectedAffectList.push_back(1);
			expectedAffectList.push_back(10);
			expectedAffectList.push_back(16);
			expectedAffectList.push_back(17);
			Assert::IsTrue(actualAffectList == expectedAffectList);
		}


		TEST_METHOD(integrationTestIsAffectsValid)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Level3Source{\n";
			sourceCode += "a = 1;\n";
			sourceCode += "while i {\n";
			sourceCode += "if i then {\n";
			sourceCode += "while i {\n";
			sourceCode += "c = a;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "a = 1;\n";
			sourceCode += "while i {\n";
			sourceCode += "a = 1;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";
			sourceCode += "c = a;\n";
			sourceCode += "}\n";
			sourceCode += "b = a;\n";
			sourceCode += "}\n";


			// Initialize actual and expected lists
			FrontEndController frontEndController;
			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			frontEndController.createFollowsStarMap();
			frontEndController.createFollowsStarMapReverse();
			frontEndController.createParentStarMap();
			frontEndController.createParentStarMapReverse();
			frontEndController.createStmtCallsMap();
			frontEndController.createCallsMap();
			frontEndController.createCallsStarMap();
			frontEndController.updateProcUsesMap();
			frontEndController.updateProcModifiesMap();
			frontEndController.updateStmtUsesMap();
			frontEndController.updateStmtModifiesMap();
			frontEndController.sortUsesModifiesMap();
			frontEndController.createCFG();
			vector<Statement> expectedSourceList;

			list<int> expectedChildrenStarList, actualChildrenStarList;
			actualChildrenStarList.clear();
			expectedChildrenStarList.clear();
			actualChildrenStarList = PKB::getPKBInstance()->getAllChildrenStar(2);
			actualChildrenStarList.sort();
			expectedChildrenStarList.push_back(3);
			expectedChildrenStarList.push_back(4);
			expectedChildrenStarList.push_back(5);
			expectedChildrenStarList.push_back(6);
			expectedChildrenStarList.push_back(7);
			expectedChildrenStarList.push_back(8);
			expectedChildrenStarList.push_back(9);
			
			Assert::IsTrue(expectedChildrenStarList == actualChildrenStarList);

			Assert::IsTrue(PKB::getPKBInstance()->isAffectsValid(1, 5));

			Assert::IsTrue(PKB::getPKBInstance()->isAffectsValid(6, 5));

			Assert::IsTrue(PKB::getPKBInstance()->isAffectsValid(8, 5));

			Assert::IsTrue(PKB::getPKBInstance()->isAffectsValid(1, 9));

			Assert::IsTrue(PKB::getPKBInstance()->isAffectsValid(6, 9));

			Assert::IsTrue(PKB::getPKBInstance()->isAffectsValid(8, 9));

			Assert::IsFalse(PKB::getPKBInstance()->isAffectsValid(8, 6));

			Assert::IsFalse(PKB::getPKBInstance()->isAffectsValid(2, 5));

			return;
		}


		TEST_METHOD(integrationTestWhileIfAffects)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Level3Source{\n";
			sourceCode += "a = 1;\n";
			sourceCode += "while i {\n";
			sourceCode += "if i then {\n";
			sourceCode += "while i {\n";
			sourceCode += "c = a;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";
			sourceCode += "else {\n";
			sourceCode += "a = 1;\n";
			sourceCode += "while i {\n";
			sourceCode += "a = 1;\n";
			sourceCode += "}\n";
			sourceCode += "}\n";
			sourceCode += "c = a;\n";
			sourceCode += "}\n";
			sourceCode += "b = a;\n";
			sourceCode += "}\n";


			// Initialize actual and expected lists
			FrontEndController frontEndController;
			vector<Statement> actualSourceList = frontEndController.processSourceCode(sourceCode);
			frontEndController.createCFG();
			vector<Statement> expectedSourceList;

			list<int> actualAffectList, expectedAffectList;
			//Test getAffectedBy
			//Test getAffectedBy1
			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(1);
			expectedAffectList.push_back(5);
			expectedAffectList.push_back(9);
			expectedAffectList.push_back(10);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			//Test getAffectedBy5
			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(5);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			//Test getAffectedBy6
			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffectedBy(6);
			expectedAffectList.push_back(5);
			expectedAffectList.push_back(9);
			expectedAffectList.push_back(10);
			Assert::IsTrue(actualAffectList == expectedAffectList);
			

			//Test getAffectedBy8
			actualAffectList.clear();
			expectedAffectList.clear();
			
			actualAffectList = PKB::getPKBInstance()->getAffectedBy(8);
			expectedAffectList.push_back(5);
			expectedAffectList.push_back(9);
			expectedAffectList.push_back(10);
			Assert::IsTrue(actualAffectList == expectedAffectList);
			
			//Test use
			list<int> expectedUseList, actualUseList;
			actualUseList.clear();
			expectedUseList.clear();
			actualUseList = PKB::getPKBInstance()->getUsedBy(5);
			expectedUseList.push_back(1);
			Assert::IsTrue(actualUseList == expectedUseList);

			//Test getAffects(5)
			actualAffectList.clear();
			expectedAffectList.clear();
			
			actualAffectList = PKB::getPKBInstance()->getAffects(5);
			expectedAffectList.push_back(1);
			expectedAffectList.push_back(6);
			expectedAffectList.push_back(8);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			//Test getAffects(9)
			actualAffectList.clear();
			expectedAffectList.clear();

			actualAffectList = PKB::getPKBInstance()->getAffects(9);
			actualAffectList.sort();
			actualAffectList.unique();
			expectedAffectList.push_back(1);
			expectedAffectList.push_back(6);
			expectedAffectList.push_back(8);
			Assert::IsTrue(actualAffectList == expectedAffectList);

			//Test getAffectedByStar
			list<int> actualAffectStarList, expectedAffectStarList;
			//Test getAffectedByStar1
			actualAffectStarList.clear();
			expectedAffectStarList.clear();

			actualAffectStarList = PKB::getPKBInstance()->getAffectedByStar(1);
			expectedAffectStarList.push_back(5);
			expectedAffectStarList.push_back(9);
			expectedAffectStarList.push_back(10);
			Assert::IsTrue(actualAffectStarList == expectedAffectStarList);

			//Test getAffectedByStar5
			actualAffectStarList.clear();
			expectedAffectStarList.clear();

			actualAffectStarList = PKB::getPKBInstance()->getAffectedBy(5);
			Assert::IsTrue(actualAffectStarList == expectedAffectStarList);

			//Test getAffectedByStar6
			actualAffectStarList.clear();
			expectedAffectStarList.clear();

			actualAffectStarList = PKB::getPKBInstance()->getAffectedBy(6);
			expectedAffectStarList.push_back(5);
			expectedAffectStarList.push_back(9);
			expectedAffectStarList.push_back(10);
			Assert::IsTrue(actualAffectStarList == expectedAffectStarList);


			//Test getAffectedByStar8
			actualAffectStarList.clear();
			expectedAffectStarList.clear();

			actualAffectStarList = PKB::getPKBInstance()->getAffectedBy(8);
			expectedAffectStarList.push_back(5);
			expectedAffectStarList.push_back(9);
			expectedAffectStarList.push_back(10);
			Assert::IsTrue(actualAffectStarList == expectedAffectStarList);
			
			//Test getAffectsStar
			//Test getAffectsStar(5)
			actualAffectStarList.clear();
			expectedAffectStarList.clear();

			actualAffectStarList = PKB::getPKBInstance()->getAffects(5);
			expectedAffectStarList.push_back(1);
			expectedAffectStarList.push_back(6);
			expectedAffectStarList.push_back(8);
			Assert::IsTrue(actualAffectStarList == expectedAffectStarList);

			//Test getAffectsStar(9)
			actualAffectStarList.clear();
			expectedAffectStarList.clear();

			actualAffectStarList = PKB::getPKBInstance()->getAffects(9);
			actualAffectStarList.sort();
			actualAffectStarList.unique();
			expectedAffectStarList.push_back(1);
			expectedAffectStarList.push_back(6);
			expectedAffectStarList.push_back(8);
			Assert::IsTrue(actualAffectStarList == expectedAffectStarList);
			
		}

	};
}