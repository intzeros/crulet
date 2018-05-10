#include "Rule_4_1_3.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include <string.h>

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(hasOperatorName("=")).bind("gjb413");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb413")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    auto RHS = Op->getRHS();
    if(!RHS){
      return;
    }

    const Type* TP = RHS->getType().getTypePtr();
    if(TP->isFunctionPointerType()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, RHS->getExprLoc(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, RHS->getExprLoc(), this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
