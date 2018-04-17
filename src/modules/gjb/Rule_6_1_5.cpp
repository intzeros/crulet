#include "Rule_6_1_5.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_5::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(hasOperatorName("=")).bind("gjb615_assign_op");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_5::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb615_assign_op")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS()->IgnoreImpCasts();

    llvm::APSInt APSIntResult;
    if(LHS->getType().getTypePtr()->isUnsignedIntegerType() && RHS->EvaluateAsInt(APSIntResult, *Result.Context)){
      if(APSIntResult < 0){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
