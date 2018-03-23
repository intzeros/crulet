#include "Rule_6_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = stmt(anyOf(
    ifStmt(hasCondition(ignoringParenImpCasts(binaryOperator(hasOperatorName("=")).bind("gjb611")))),
    ifStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb611"))))),
    forStmt(hasCondition(ignoringParenImpCasts(binaryOperator(hasOperatorName("=")).bind("gjb611")))),
    forStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb611"))))),
    whileStmt(hasCondition(ignoringParenImpCasts(binaryOperator(hasOperatorName("=")).bind("gjb611")))),
    whileStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb611"))))),
    conditionalOperator(hasCondition(ignoringParenImpCasts(binaryOperator(hasOperatorName("=")).bind("gjb611"))))
  ));
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb611")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
    Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
