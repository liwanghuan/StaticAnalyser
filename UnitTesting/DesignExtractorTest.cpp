#include "stdafx.h"
#include "CppUnitTest.h"
#include "../PKB/PKB.h"
#include "../SPA Front End/Front End Controller/FrontEndController.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStudent_VS2015{

	TEST_CLASS(DesignExtractorTest){
	public:
		TEST_METHOD_INITIALIZE(setUpPKB) {

			//init follows
			PKB::getPKBInstance()->setFollows(1, 2);
			PKB::getPKBInstance()->setFollows(2, 12);
			PKB::getPKBInstance()->setFollows(3, 4);
			PKB::getPKBInstance()->setFollows(4, 7);
			PKB::getPKBInstance()->setFollows(7, 8);
            PKB::getPKBInstance()->setFollows(8, 11);
            PKB::getPKBInstance()->setFollows(9, 10);
			PKB::getPKBInstance()->setFollows(11, 13);

			FrontEndController FEC;
            //Create followsStarMap(DE)
            FEC.createFollowsStarMap();
            //Create followsStarMapReverse(DE)
            FEC.createFollowsStarMapReverse(); 
            
			//init parent
			PKB::getPKBInstance()->setParent(2, 3);
			PKB::getPKBInstance()->setParent(2, 4);
			PKB::getPKBInstance()->setParent(2, 7);
			PKB::getPKBInstance()->setParent(2, 8);
			PKB::getPKBInstance()->setParent(2, 11);
			PKB::getPKBInstance()->setParent(4, 5);
			PKB::getPKBInstance()->setParent(4, 6);
            PKB::getPKBInstance()->setParent(8, 9);
			PKB::getPKBInstance()->setParent(8, 10);
			PKB::getPKBInstance()->setParent(12, 13);
		
			//Create parentStarMap(DE)
            FEC.createParentStarMap();
            //Create parentStarMapReverse(DE)
            FEC.createParentStarMapReverse();

		}

		TEST_METHOD(getAllChildrenStarTest) { //get list of follower

			list<int> actualList, expectedList;
            
			Assert::IsTrue(PKB::getPKBInstance()->getAllChildrenStar(5) == list<int>()); //return empty 
			actualList.clear();
			expectedList.clear();

			actualList = PKB::getPKBInstance()->getAllChildrenStar(12); //return 1 children only
			expectedList.clear();
			expectedList.push_back(13);
			Assert::IsTrue(actualList == expectedList);
			actualList.clear();
			expectedList.clear();

			expectedList.clear();
			actualList = PKB::getPKBInstance()->getAllChildrenStar(2);
			expectedList.push_back(3);
			expectedList.push_back(4);
			expectedList.push_back(5);
            expectedList.push_back(6);
			expectedList.push_back(7);
			expectedList.push_back(8);
			expectedList.push_back(9);
			expectedList.push_back(10);
			expectedList.push_back(11);
            Assert::IsTrue(actualList == expectedList);


			expectedList.clear();
			actualList.clear();
			actualList = PKB::getPKBInstance()->getAllChildrenStar(4);
			expectedList.push_back(5);
			expectedList.push_back(6);
			Assert::IsTrue(actualList == expectedList);

			return;
		}
        
        TEST_METHOD(getFollowsStarByTest) { //get list of follower

			list<int> actualList, expectedList;
            
			Assert::IsTrue(PKB::getPKBInstance()->getFollowsStarBy(12) == list<int>()); //return empty 
			actualList.clear();
			expectedList.clear();

			actualList = PKB::getPKBInstance()->getFollowsStarBy(2); //return 1 children only
			expectedList.clear();
			expectedList.push_back(12);
			Assert::IsTrue(actualList == expectedList);
			actualList.clear();
			expectedList.clear();

			expectedList.clear();
			actualList = PKB::getPKBInstance()->getFollowsStarBy(3);
			expectedList.push_back(4);
			expectedList.push_back(7);
			expectedList.push_back(8);
            expectedList.push_back(11);
			expectedList.push_back(13);
           Assert::IsTrue(actualList == expectedList);


			expectedList.clear();
			actualList.clear();
			actualList = PKB::getPKBInstance()->getFollowsStarBy(1);
			expectedList.push_back(2);
			expectedList.push_back(12);
			Assert::IsTrue(actualList == expectedList);

			return;
		}


        TEST_METHOD(getFollowsStarTest) { //get list of follower

			list<int> actualList, expectedList;
            
			Assert::IsTrue(PKB::getPKBInstance()->getFollowsStar(1) == list<int>()); //return empty 
			actualList.clear();
			expectedList.clear();

			actualList = PKB::getPKBInstance()->getFollowsStar(2); //return 1 children only
			expectedList.clear();
			expectedList.push_back(1);
			Assert::IsTrue(actualList == expectedList);
			actualList.clear();
			expectedList.clear();

		
			actualList = PKB::getPKBInstance()->getFollowsStar(11);
			expectedList.push_back(3);
			expectedList.push_back(7);
			expectedList.push_back(8);
			expectedList.push_back(4);
			actualList.sort();
			expectedList.sort();
            Assert::IsTrue(actualList == expectedList);


			expectedList.clear();
			actualList.clear();
			actualList = PKB::getPKBInstance()->getFollowsStar(7);
			expectedList.push_back(3);
			expectedList.push_back(4);
			Assert::IsTrue(actualList == expectedList);

			return;
		}
        
        TEST_METHOD(getParentStarTest) { //get list of follower

			list<int> actualList, expectedList;
            
			Assert::IsTrue(PKB::getPKBInstance()->getParentStar(2) == list<int>()); //return empty 
			actualList.clear();
			expectedList.clear();

			actualList = PKB::getPKBInstance()->getParentStar(3); //return 1 children only
			expectedList.clear();
			expectedList.push_back(2);
			actualList.sort();
			expectedList.sort();
			Assert::IsTrue(1 == expectedList.size());
			Assert::IsTrue(actualList == expectedList);
			actualList.clear();
			expectedList.clear();

			expectedList.clear();
			actualList = PKB::getPKBInstance()->getParentStar(5);
			expectedList.push_back(2);
			expectedList.push_back(4);
            Assert::IsTrue(actualList == expectedList);


			expectedList.clear();
			actualList.clear();
			actualList = PKB::getPKBInstance()->getParentStar(10);
			expectedList.push_back(2);
			expectedList.push_back(8);
			Assert::IsTrue(actualList == expectedList);

			return;
        }
		TEST_METHOD(CFGNextTest)
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

			list<int> actualNextList, expectedNextList;
			
			//Test getNext
			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getNext(3);
			actualNextList.sort();
			expectedNextList.push_back(4);
			Assert::IsTrue(actualNextList == expectedNextList);

			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getNext(6);
			actualNextList.sort();
			expectedNextList.push_back(7);
			expectedNextList.push_back(18);
			Assert::IsTrue(actualNextList == expectedNextList);

			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getNext(8);
			actualNextList.sort();
			expectedNextList.push_back(9);
			expectedNextList.push_back(12);
			Assert::IsTrue(actualNextList == expectedNextList);
			
			//Test getNextStar
			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getNextStar(19);
			actualNextList.sort();
			expectedNextList.push_back(20);
			expectedNextList.push_back(21);
			expectedNextList.push_back(22);
			Assert::IsTrue(actualNextList == expectedNextList);
			
			//Test getPrevious
			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getPrevious(3);
			actualNextList.sort();
			expectedNextList.push_back(2);
			Assert::IsTrue(actualNextList == expectedNextList);

			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getPrevious(8);
			actualNextList.sort();
			expectedNextList.push_back(7);
			expectedNextList.push_back(11);
			Assert::IsTrue(actualNextList == expectedNextList);

			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getPrevious(6);
			actualNextList.sort();
			expectedNextList.push_back(5);
			expectedNextList.push_back(17);
			Assert::IsTrue(actualNextList == expectedNextList);
			
			//Test getPreviousStar
			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getPreviousStar(3);
			actualNextList.sort();
			expectedNextList.push_back(1);
			expectedNextList.push_back(2);
			Assert::IsTrue(actualNextList == expectedNextList);
			
			actualNextList.clear();
			expectedNextList.clear();

			actualNextList = PKB::getPKBInstance()->getPreviousStar(5);
			actualNextList.sort();
			expectedNextList.push_back(1);
			expectedNextList.push_back(2);
			expectedNextList.push_back(3);
			expectedNextList.push_back(4);
			Assert::IsTrue(actualNextList == expectedNextList);
			
			return;
		}
			
	};
	
}
