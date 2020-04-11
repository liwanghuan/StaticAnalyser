#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "../Query/Query Processor/QueryValidator.h"

const string VALID_QUERY = "VALID";
const string INVALID_QUERY = "INVALID";
const string INVALID_BOOLEAN_QUERY = "INVALID_BOOLEAN";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryValidator)
	{
	public:

		TEST_METHOD(testQuerySuchThat) // Sample
		{
			QueryValidator qv; string s;

			// No clauses
			s = "procedure p; Select p";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			
			// Special selection queries
			s = "assign a1; variable v1; Select v1.varName such that Follows(a1, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "call c1; Select c1.procName such that Calls*(_, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "call c1; procedure p; Select c1.stmt# such that Calls(_, p)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "procedure p; Select p.procName such that Calls(p, \"PROCEDURE\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "stmt s; constant c; Select c.value with s.stmt# = c.value";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a1; variable v1; Select a1.stmt# such that Follows(a1, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Special selection tuple clauses
			s = "assign a1, a2; variable v1; Select <a1.stmt#, a2.stmt#> such that Follows(a1, a2)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a1, a2; variable v1; Select <a1.stmt#, a2> such that Follows(a1, a2)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a1, a2; variable v1; Select <a1, a2.stmt#> such that Follows(a1, a2)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Follows and Follows*
			s = "assign a; stmt s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a; stmt s; Select a such that Follows*(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Parent and Parent*
			s = "assign a; stmt s; Select a such that Parent(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a; stmt s; Select a such that Parent*(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Modifies
			s = "stmt s; Select s such that Modifies(s, \"i\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Uses
			s = "variable v; Select v such that Uses(6, v)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Calls and Calls*
			s = "procedure p; Select p such that Calls(p, \"PROCEDURE\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "procedure p; Select p such that Calls*(p, \"PROCEDURE\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Next and Next*
			s = "assign a; Select a such that Next(4, a)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a; Select a such that Next*(4, a)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Affects and Affects*
			s = "assign a; stmt s1, s2; Select a such that Affects(4, s1)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a; stmt s1, s2; Select a such that Affects*(s1, s2)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Invalid syntax/declaration
			s = "assign a; stmt s;";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assign x; stmt y; Select x(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assign a; stmt s; Select b such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);

			// BOOLEAN query statements (With declaration)
			QueryValidator qv2;
			s = "assign a; stmt s; Select BOOLEAN such that Follows(4, 5)";
			Assert::AreEqual(qv2.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// BOOLEAN query statements (Without declaration)
			s = "Select BOOLEAN such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Invalid BOOLEAN selection
			s = "assign a; stmt s; Select BOOLEANNN such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			QueryValidator qv3;
			s = "assign a1, a2; stmt s; Select BOOLEAN such that Calls(a1, a2)";
			Assert::AreEqual(qv3.isValidDeclarationAndQuery(s).compare(INVALID_BOOLEAN_QUERY), 0);

			// For STMTLIST query
			s = "stmtLst s1; Select s1";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Queries with invalid declarations
			s = "variableqwe x; stmt s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "constantqwe c; stmt s; Select a such that Parent(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "stmtqwe s; stmt s; Select a such that Parent*(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assignqwe a; stmt s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "whileqwe w; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "ifqwe a; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "procedureqwe p; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "prog_lineqwe n; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);

			// Check trim/split (Valid)
			s = "        assign     a;      Select     BOOLEAN     such   that  Follows*     (2, 3)       ";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign a; Select a such that Parent*(4,a)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Check trim/split (Invalid)
			s = "   assign a; Se lect BOOLEAN su ch th at Follows*(2, 3)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assigna;SelectasuchthatParent*(4,a)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);

			// Make sure multiple declarations are not possible (Invalid)
			s = "assign a1, a2; stmt a1, a2; Select a1 such that Follows(a1, a2)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
		}

		TEST_METHOD(testQueryPattern) {
			QueryValidator qv; string s;

			// Valid PATTERN (ASSIGN) queries
			s = "assign a; variable v; Select a pattern a(v, \"a + 2\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign b; variable v; Select b pattern b(v, _\"a + 2\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign b; variable v; Select b pattern b(v, _\"a * 2\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign b; variable v; Select b pattern b(v, _\"a - 2\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign c; variable v; Select c pattern c(\"y\", _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign d; variable v; Select d pattern d(_, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign b; variable v; Select b pattern b(v, _\"(a + 2) * y\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign b; variable v; Select b pattern b(_, _\"((a + 2) * y)\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign b; variable v; Select b pattern b(_, \"((a + 2) * y)\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			s = "assign b; variable v; Select b pattern b(_, \"(((((((a + 2) * y))))))\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign d; variable v; Select d pattern d(_, _\"x+y\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Valid PATTERN (WHILE) queries
			s = "while w; Select w pattern w(\"x\", _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Valid PATTERN (IF) queries
			s = "if ifs; assign a; Select ifs pattern ifs(\"x\", _, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Invalid PATTERN queries
			s = "assign a; variable v; Select a pattern a(_\"x+y\"_, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assign a; variable v; Select a pattern a(\"x+y\"_, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assign a; variable v; Select a pattern a(_\"x+y\", _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);

			s = "assign a; variable v; Select a pattern a(_, \"x+y\"_)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			s = "assign a; variable v; Select a pattern a(_, _\"x+y\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);

			s = "assign a; variable v; Select a pattern a(,)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
		}

		TEST_METHOD(testQueryWith) {
			QueryValidator qv; string s;

			// Procedure name
			s = "variable v; procedure p; Select p with p.procName = v.varName";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Program line
			s = "prog_line n; assign a; Select a such that Parent(4, 5) such that Follows(a, 6) with n = 10";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Statement#
			s = "stmt s; constant c; Select s with s.stmt# = c.value";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Able to process queries in any order
			// (i.e. c.value = 12 is the same as 12 = c.value)
			s = "stmt s; constant c; Select s with c.value = s.stmt#";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
		}

		TEST_METHOD(testQueryMultipleClauses) {
			QueryValidator qv; string s;

			// Multiple clauses (VALID)
			s = "assign a; stmt s; constant c; variable v; procedure p; Select s with s.stmt# = c.value with p.procName = v.varName pattern a(v, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a, a1; variable v; Select a such that Uses(a, v) pattern a1(v, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a, a1; variable v; stmt s; constant c; Select a such that Uses(a, v) pattern a1(v, _) with s.stmt# = c.value";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a, a1, a2; variable v; Select a such that Uses(a, v) pattern a1(v, _) such that Follows(4, 5) pattern a2(_, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a, a1, a2; variable v; Select a such that Uses(a, v) pattern a1(v, _) such that Follows(4, 5) pattern a2(_, _) such that Modifies(a, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a, a1; variable v; stmt s; constant c; Select a such that Uses(a, v) pattern a1(v, _) with s.stmt# = c.value such that Follows(4, 6)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "procedure p; Select p such that Calls(p, \"Second\") and Modifies(p, \"x\")";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a, a1, a2; variable v; procedure p; Select a such that Uses(a, v) and Follows(4, 5) and Calls*(p, \"Second\") pattern a1(v, _) and a2(_, _) such that Modifies(a, _) and Affects(20, a)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "procedure p, q; Select BOOLEAN such that Calls(p, q) with q.procName = \"p\" and p.procName = \"Example\"";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3; Select s1 such that Uses (s3, v1) and Modifies (s3, \"x\") and Follows (s1, s2) and Parent (s3, s1) and Uses (s2, v1) such that Uses(5, \"y\") and Follows(3, 4) pattern a1(v2, _\"x + y\"_) such that Affects(a1, a2) with a2.stmt# = 20 such that Modifies(a3, v3) pattern a3(\"z\", _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);
			
			// Multiple pattern clause with extra whitespaces in arguments
			s = "if ifs; assign a; while w; Select ifs pattern ifs(     \"x\", _   ,  _   ) and ifs(   _,  _   ,  _   )";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "if ifs; assign a; while w; Select a pattern a(     _,     _\"(x+y)*z\"_     ) and a(     _,   _      )";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			s = "while w; Select w pattern w(   _    ,   _    ) and w(   \"x\"   ,  _    )";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(VALID_QUERY), 0);

			// Multiple clauses (INVALID)
			// Invalid clause
			s = "stmt s; constant c; variable v; Select s with s.stmt# = v.varName";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);

			// There is no "and" in the last 2 clauses
			s = "assign s1, s2, s3, s4, s5, s6, s7, s8; Select s1 such that Affects*(s1, s2) and Affects*(s3, s4) such that Affects*(s5, s6) Affects*(s7, s8)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
			
			// There is no need for a "pattern" after "and" in the second clause
			s = "assign a1, a2; Select a1 pattern a1(_, _) and pattern a2(_, _)";
			Assert::AreEqual(qv.isValidDeclarationAndQuery(s).compare(INVALID_QUERY), 0);
		}
	};
}