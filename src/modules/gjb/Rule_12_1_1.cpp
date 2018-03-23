#include "Rule_12_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include <string.h>

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_12_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = cStyleCastExpr().bind("gjb1211_cStyleCastExpr");
  Finder->addMatcher(Matcher, this);
}

void Rule_12_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const CStyleCastExpr *CCE = Result.Nodes.getNodeAs<CStyleCastExpr>("gjb1211_cStyleCastExpr")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = CCE->getExprLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(strcmp(CCE->getCastKindName(), "IntegralToPointer") == 0){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, CCE->getRParenLoc(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, CCE->getRParenLoc(), this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
