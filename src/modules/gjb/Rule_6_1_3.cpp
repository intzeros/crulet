#include "Rule_6_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(anyOf(
    hasOperatorName("<<"), hasOperatorName(">>"), hasOperatorName("<<="), hasOperatorName(">>="))
  ).bind("gjb613_shift_op");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb613_shift_op")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    Expr* LHS = Op->getLHS();
    const Type* TP = LHS->getType().getTypePtr();
    
    if(TP->isSignedIntegerType()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, LHS->getLocStart(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, LHS->getLocStart(), this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
