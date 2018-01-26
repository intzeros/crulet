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
  ).bind("bitwise_op");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_12::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("bitwise_op")){
    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS();
    const Type* TP1 = LHS->getType().getTypePtr();
    const Type* TP2 = RHS->getType().getTypePtr();
    
    if(TP1->isSignedIntegerType() || TP2->isSignedIntegerType()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, Op->getOperatorLoc(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
