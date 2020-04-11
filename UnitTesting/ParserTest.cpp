#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <../SPA Front End/Parser/Parser.h>
#include <../PKB/PKB.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(ParserTest1)
	{
	public:

		// Parser Test - Able to add the following Statement types:
		// 1) Procedure
		// 2) Assignment
		// 3) While
		TEST_METHOD(parsingSingleProcedureSourceCodeTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; \n";

			sourceCode += "a= x +y;\n";
			sourceCode += "b =3;\n";
			sourceCode += "t     = 5;}\n";
			sourceCode += "if l then{\n";
			sourceCode += "n = d - 1;\n";
			sourceCode += "z = z+x    + s;}\n";
			sourceCode += "else {";
			sourceCode += "k = n - 1; }";
			sourceCode += "}";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "i=5"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=x-1"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=z+(x+i)"));
			expectedSourceList.push_back(Statement(7, 2, 0, "assign", "i=i-1"));
			expectedSourceList.push_back(Statement(8, 2, 0, "assign", "a=x+y"));
			expectedSourceList.push_back(Statement(9, 2, 0, "assign", "b=3"));
			expectedSourceList.push_back(Statement(10, 2, 1, "assign", "t=5"));
			expectedSourceList.push_back(Statement(11, 1, 0, "if", "l"));
			expectedSourceList.push_back(Statement(12, 2, 0, "assign", "n=d-1"));
			expectedSourceList.push_back(Statement(13, 2, 1, "assign", "z=z+x+s"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(14, 2, 2, "assign", "k=n-1"));

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
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingMultipleProcedureSourceCodeTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example1{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; \n";

			sourceCode += "a= x +y;\n";
			sourceCode += "b =3;\n";
			sourceCode += "t     = 5;}\n";
			sourceCode += "if l then{\n";
			sourceCode += "n = d - 1;\n";
			sourceCode += "z = z+x    + s;}\n";
			sourceCode += "else {";
			sourceCode += "k = n - 1;";
			sourceCode += "call Example2; }";
			sourceCode += "}";
			sourceCode += "procedure Example2{\n";
			sourceCode += "k = n - 1;";
			sourceCode += "call Example3;}";
			sourceCode += "procedure Example3{\n";
			sourceCode += "k = n - 1;}";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example1"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "i=5"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=x-1"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=z+(x+i)"));
			expectedSourceList.push_back(Statement(7, 2, 0, "assign", "i=i-1"));
			expectedSourceList.push_back(Statement(8, 2, 0, "assign", "a=x+y"));
			expectedSourceList.push_back(Statement(9, 2, 0, "assign", "b=3"));
			expectedSourceList.push_back(Statement(10, 2, 1, "assign", "t=5"));
			expectedSourceList.push_back(Statement(11, 1, 0, "if", "l"));
			expectedSourceList.push_back(Statement(12, 2, 0, "assign", "n=d-1"));
			expectedSourceList.push_back(Statement(13, 2, 1, "assign", "z=z+x+s"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(14, 2, 0, "assign", "k=n-1"));
			expectedSourceList.push_back(Statement(15, 2, 2, "call", "Example2"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example2"));
			expectedSourceList.push_back(Statement(16, 1, 0, "assign", "k=n-1"));
			expectedSourceList.push_back(Statement(17, 1, 1, "call", "Example3"));
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example3"));
			expectedSourceList.push_back(Statement(18, 1, 1, "assign", "k=n-1"));

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
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingNormalIndentSourceCodeTest)
		{
			string sourceCode = "";
			sourceCode += "procedure \tExample{\n\t";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";
			sourceCode += "a= x +y;";
			sourceCode += "b =3;\n";
			sourceCode += "t = 5;";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1;\n";
			sourceCode += "z = z+x    + s;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "i=5"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=x-1"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=z+(x+i)"));
			expectedSourceList.push_back(Statement(7, 2, 1, "assign", "i=i-1"));
			expectedSourceList.push_back(Statement(8, 1, 0, "assign", "a=x+y"));
			expectedSourceList.push_back(Statement(9, 1, 0, "assign", "b=3"));
			expectedSourceList.push_back(Statement(10, 1, 0, "assign", "t=5"));
			expectedSourceList.push_back(Statement(11, 1, 0, "while", "l"));
			expectedSourceList.push_back(Statement(12, 2, 0, "assign", "n=d-1"));
			expectedSourceList.push_back(Statement(13, 2, 0, "assign", "z=z+x+s"));
			expectedSourceList.push_back(Statement(14, 2, 2, "assign", "k=n-1"));

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
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingArbitraryIndentSourceCodeTest)
		{
			string sourceCode = "";
			sourceCode += "procedure \tExample{\n\t";
			sourceCode += "x = 2\t;\n";
			sourceCode += "z = 3\n\t;";
			sourceCode += "i = 5;\t\n";
			sourceCode += "while \ti{\n";
			sourceCode += "x = x - \t1;\n";
			sourceCode += "z = z \t+ (x + i);\n";
			sourceCode += "i = i \t- 1; }\n";
			sourceCode += "a= \tx +\ty;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "i=5"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=x-1"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=z+(x+i)"));
			expectedSourceList.push_back(Statement(7, 2, 1, "assign", "i=i-1"));
			expectedSourceList.push_back(Statement(8, 1, 0, "assign", "a=x+y"));
			expectedSourceList.push_back(Statement(9, 1, 0, "assign", "b=3"));
			expectedSourceList.push_back(Statement(10, 1, 0, "assign", "t=5"));
			expectedSourceList.push_back(Statement(11, 1, 0, "while", "l"));
			expectedSourceList.push_back(Statement(12, 2, 0, "assign", "n=d-1"));
			expectedSourceList.push_back(Statement(13, 2, 0, "assign", "z=z+x+s"));
			expectedSourceList.push_back(Statement(14, 2, 2, "assign", "k=n-1"));

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
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingOnlyWhileSourceCodeTest)
		{
			string sourceCode = "";
			sourceCode += "procedure \tExample{\n\t";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";
			sourceCode += "a= x +y;";
			sourceCode += "b =3;\n";
			sourceCode += "t = 5;";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1;\n";
			sourceCode += "z = z+x    + s;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "i=5"));
			expectedSourceList.push_back(Statement(4, 1, 0, "while", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=x-1"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=z+(x+i)"));
			expectedSourceList.push_back(Statement(7, 2, 1, "assign", "i=i-1"));
			expectedSourceList.push_back(Statement(8, 1, 0, "assign", "a=x+y"));
			expectedSourceList.push_back(Statement(9, 1, 0, "assign", "b=3"));
			expectedSourceList.push_back(Statement(10, 1, 0, "assign", "t=5"));
			expectedSourceList.push_back(Statement(11, 1, 0, "while", "l"));
			expectedSourceList.push_back(Statement(12, 2, 0, "assign", "n=d-1"));
			expectedSourceList.push_back(Statement(13, 2, 0, "assign", "z=z+x+s"));
			expectedSourceList.push_back(Statement(14, 2, 2, "assign", "k=n-1"));

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
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingOnlyIfSourceCodeTest)
		{
			string sourceCode = "";
			sourceCode += "procedure \tExample{\n\t";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "if i then {\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1;\n";
			sourceCode += "a= x +y;";
			sourceCode += "b =3;\n";
			sourceCode += "t = 5;}";
			sourceCode += "else {\n";
			sourceCode += "n = d - 1;\n";
			sourceCode += "z = z+x    + s;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			// Populate expected values into a list
			expectedSourceList.push_back(Statement(-1, 0, 0, "procedure", "Example"));
			expectedSourceList.push_back(Statement(1, 1, 0, "assign", "x=2"));
			expectedSourceList.push_back(Statement(2, 1, 0, "assign", "z=3"));
			expectedSourceList.push_back(Statement(3, 1, 0, "assign", "i=5"));
			expectedSourceList.push_back(Statement(4, 1, 0, "if", "i"));
			expectedSourceList.push_back(Statement(5, 2, 0, "assign", "x=x-1"));
			expectedSourceList.push_back(Statement(6, 2, 0, "assign", "z=z+(x+i)"));
			expectedSourceList.push_back(Statement(7, 2, 0, "assign", "i=i-1"));
			expectedSourceList.push_back(Statement(8, 2, 0, "assign", "a=x+y"));
			expectedSourceList.push_back(Statement(9, 2, 0, "assign", "b=3"));
			expectedSourceList.push_back(Statement(10, 2, 1, "assign", "t=5"));
			expectedSourceList.push_back(Statement(-1, 1, 0, "else", ""));
			expectedSourceList.push_back(Statement(11, 2, 0, "assign", "n=d-1"));
			expectedSourceList.push_back(Statement(12, 2, 0, "assign", "z=z+x+s"));
			expectedSourceList.push_back(Statement(13, 2, 2, "assign", "k=n-1"));

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
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingFollowTest)
		{
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(1, 2));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(2, 3));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(3, 4));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(5, 6));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(6, 7));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(8, 9));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(9, 10));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(10, 11));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(12, 13));
			Assert::AreEqual(true, PKB::getPKBInstance()->isFollowsValid(13, 14));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingParentTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;
			Assert::AreEqual(true, PKB::getPKBInstance()->isParentValid(4, 5));
			Assert::AreEqual(true, PKB::getPKBInstance()->isParentValid(4, 6));
			Assert::AreEqual(true, PKB::getPKBInstance()->isParentValid(4, 7));
			Assert::AreEqual(true, PKB::getPKBInstance()->isParentValid(11, 12));
			Assert::AreEqual(true, PKB::getPKBInstance()->isParentValid(11, 13));
			Assert::AreEqual(true, PKB::getPKBInstance()->isParentValid(11, 14));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingUsesTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(4, "i"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(5, "x"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(6, "z"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(6, "x"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(6, "i"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(7, "i"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(8, "x"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(8, "y"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(11, "l"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(7, "i"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(12, "d"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(13, "z"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(13, "x"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(13, "s"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isUsesValid(14, "n"));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingModifiesTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;

			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(1, "x"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(2, "z"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(3, "i"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(5, "x"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(6, "z"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(7, "i"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(8, "a"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(9, "b"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(10, "t"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(12, "n"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(13, "z"));
			Assert::AreEqual(true, PKB::getPKBInstance()->isModifiesValid(14, "k"));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingAssignPatternTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;
			string LHS = "x";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(1));
			LHS = "z";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(2));
			LHS = "i";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(3));
			LHS = "x";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(5));
			LHS = "z";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(6));
			LHS = "i";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(7));
			LHS = "a";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(8));
			LHS = "b";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(9));
			LHS = "t";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(10));
			LHS = "n";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(12));
			LHS = "z";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(13));
			LHS = "k";
			Assert::AreEqual(LHS, PKB::getPKBInstance()->getAssignPatternLHS(14));

			string RHS = ".2.";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(1));
			RHS = ".3.";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(2));
			RHS = ".5.";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(3));
			RHS = ".x..1.-";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(5));
			RHS = ".z..x..i.++";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(6));
			RHS = ".i..1.-";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(7));
			RHS = ".x..y.+";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(8));
			RHS = ".3.";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(9));
			RHS = ".5.";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(10));
			RHS = ".d..1.-";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(12));
			RHS = ".z..x.+.s.+";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(13));
			RHS = ".n..1.-";
			Assert::AreEqual(RHS, PKB::getPKBInstance()->getAssignPatternRHS(14));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingWhilePatternTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "while i{\n";
			sourceCode += "x = x - 1;\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "while l{\n";
			sourceCode += "n = d - 1\n;\n";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";

			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;
			string whileVar = "i";
			Assert::AreEqual(whileVar, PKB::getPKBInstance()->getWhilePatternUses(4));
			whileVar = "l";
			Assert::AreEqual(whileVar, PKB::getPKBInstance()->getWhilePatternUses(11));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}

		TEST_METHOD(parsingIfPatternTest)
		{
			// Normal Indentation codes
			string sourceCode = "";
			sourceCode += "procedure Example{\n";
			sourceCode += "x = 2;\n";
			sourceCode += "z = 3\n;";
			sourceCode += "i = 5;\n";
			sourceCode += "if i then {\n";
			sourceCode += "x = x - 1;}\n";
			sourceCode += "else {\n";
			sourceCode += "z = z + (x + i);\n";
			sourceCode += "i = i - 1; }\n";

			// Arbitrary Indentation codes
			sourceCode += "a= x +y;";
			sourceCode += "b =3\n;";
			sourceCode += "t     = 5;\t";
			sourceCode += "if l then {\n";
			sourceCode += "n = d - 1\n;}\n";
			sourceCode += "else {";
			sourceCode += "z = z+x    + s\t;\n";
			sourceCode += "k = n - 1; }\n";
			sourceCode += "\n}\t";


			// Initialize actual and expected lists
			Parser parser;

			vector<Statement> actualSourceList = parser.processSourceCode(sourceCode);
			vector<Statement> expectedSourceList;
			string ifVar = "i";
			Assert::AreEqual(ifVar, PKB::getPKBInstance()->getIfPatternUses(4));
			ifVar = "l";
			Assert::AreEqual(ifVar, PKB::getPKBInstance()->getIfPatternUses(11));
			expectedSourceList.clear();
			actualSourceList.clear();
			PKB::getPKBInstance()->removePKBInstance();
		}
	};
}