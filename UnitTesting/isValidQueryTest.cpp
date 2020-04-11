#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Query/Query Processor/QueryValidator.h"

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
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Valid SUCH THAT queries
			s = "assign a; stmt s; Select a such that Follows(4, 5)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));
			s = "assign a; stmt s; Select a such that Follows*(4, 5)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a; stmt s; Select a such that Parent(4, 5)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));
			s = "assign a; stmt s; Select a such that Parent*(4, 5)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "stmt s; Select s such that Modifies(s, \"i\")";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "variable v; Select v such that Uses(6, v)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// =======Include next, next*, affects and affects* in the future=======

			// Simple queries with invalid syntax/declaration
			s = "assign a; stmt s;";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assign x; stmt y; Select x(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assign a; stmt s; Select b such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));

			// For BOOLEAN query statements (With declaration)
			s = "assign a; stmt s; Select BOOLEAN such that Follows(4, 5)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// For BOOLEAN query statements (Without declaration)
			s = "Select BOOLEAN such that Follows(4, 5)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Invalid BOOLEAN selection
			s = "assign a; stmt s; Select BOOLEANNN such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));

			// Wrong declaration
			s = "variableqwe x; stmt s; Select a such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "constantqwe c; stmt s; Select a such that Parent(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "stmtqwe s; stmt s; Select a such that Parent*(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assignqwe a; stmt s; Select a such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "whileqwe w; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "ifqwe a; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "procedureqwe p; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "prog_lineqwe n; stmtaaa s; Select a such that Follows(4, 5)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));

			// Check trim/split (Valid)
			s = "        assign     a;      Select     BOOLEAN     such   that  Follows*     (2, 3)       ";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));
			s = "assign a; Select a such that Parent*(4,a)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Check trim/split (Invalid)
			s = "   assign a; Se lect BOOLEAN su ch th at Follows*(2, 3)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assigna;SelectasuchthatParent*(4,a)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
		}

		TEST_METHOD(testQueryPattern) {
			QueryValidator qv; string s;

			// Valid PATTERN (ASSIGN) queries
			s = "assign a; variable v; Select a pattern a(v, \"a + 2\")";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign b; variable v; Select b pattern b(v, _\"a + 2\"_)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));
			s = "assign b; variable v; Select b pattern b(v, _\"a * 2\"_)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));
			s = "assign b; variable v; Select b pattern b(v, _\"a - 2\"_)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign c; variable v; Select c pattern c(\"y\", _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign d; variable v; Select d pattern d(_, _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign d; variable v; Select d pattern d(_, _\"x+y\"_)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Valid PATTERN (WHILE) queries
			s = "while w; Select w pattern w(\"x\", _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Valid PATTERN (IF) queries
			s = "if ifs; assign a; Select ifs pattern ifs(\"x\", _, _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Invalid PATTERN queries
			s = "assign a; variable v; Select a pattern a(_\"x+y\"_, _)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assign a; variable v; Select a pattern a(\"x+y\"_, _)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assign a; variable v; Select a pattern a(_\"x+y\", _)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));

			s = "assign a; variable v; Select a pattern a(_, \"x+y\"_)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
			s = "assign a; variable v; Select a pattern a(_, _\"x+y\")";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));

			s = "assign a; variable v; Select a pattern a(,)";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
		}

		TEST_METHOD(testQueryWith) {
			QueryValidator qv; string s;

			// Procedure name
			s = "variable v; procedure p; Select p with p.procName = v.varName";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Program line
			s = "prog_line n; assign a; Select a such that Parent(4, 5) such that Follows(a, 6) with n = 10";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Statement#
			s = "stmt s; constant c; Select s with s.stmt# = c.value";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));
		}

		TEST_METHOD(testQueryMultipleClauses) {
			QueryValidator qv; string s;

			// Multiple clauses (VALID)
			s = "assign a; stmt s; constant c; variable v; procedure p; Select s with s.stmt# = c.value with p.procName = v.varName pattern a(v, _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a, a1; variable v; Select a such that Uses(a, v) pattern a1(v, _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a, a1; variable v; stmt s; constant c; Select a such that Uses(a, v) pattern a1(v, _) with s.stmt# = c.value";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a, a1, a2; variable v; Select a such that Uses(a, v) pattern a1(v, _) such that Follows(4, 5) pattern a2(_, _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a, a1, a2; variable v; Select a such that Uses(a, v) pattern a1(v, _) such that Follows(4, 5) pattern a2(_, _) such that Modifies(a, _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a, a1; variable v; stmt s; constant c; Select a such that Uses(a, v) pattern a1(v, _) with s.stmt# = c.value such that Follows(4, 6)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "procedure p; Select p such that Calls(p, \"Second\") and Modifies(p, \"x\")";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a, a1, a2; variable v; procedure p; Select a such that Uses(a, v) and Follows(4, 5) and Calls*(p, \"Second\") pattern a1(v, _) and a2(_, _) such that Modifies(a, _) and Affects(20, a)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "procedure p, q; Select BOOLEAN such that Calls(p, q) with q.procName = \"p\" and p.procName = \"Example\"";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			s = "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3; Select s1 such that Uses (s3, v1) and Modifies (s3, \"x\") and Follows (s1, s2) and Parent (s3, s1) and Uses (s2, v1) such that Uses(5, \"y\") and Follows(3, 4) pattern a1(v2, _\"x + y\"_) such that Affects(a1, a2) with a2.stmt# = 20 such that Modifies(a3, v3) pattern a3(\"z\", _)";
			Assert::IsTrue(qv.isValidDeclarationAndQuery(s));

			// Multiple clauses (INVALID)
			s = "stmt s; constant c; variable v; Select s with s.stmt# = v.varName";
			Assert::IsFalse(qv.isValidDeclarationAndQuery(s));
		}
	};
}