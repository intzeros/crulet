#include "Rule_6_1_12.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_12::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(anyOf(
    hasOperatorName("<<"), hasOperatorName(">>"), hasOperatorName("<<="), hasOperatorName(">>=")
    , hasOperatorName("|"), hasOperatorName("|="), hasOperatorName("&"), hasOperatorName("&=")
    , hasOperatorName("^"), hasOperatorName("^="), hasOperatorName("~"))
  ).bind("gjb6112_bitwise_op");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_12::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb6112_bitwise_op")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS();
    const Type* TP1 = LHS->getType().getTypePtr();
    const Type* TP2 = RHS->getType().getTypePtr();
    
    if(TP1->isSignedIntegerType() || TP2->isSignedIntegerType()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
