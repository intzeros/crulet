#include "Rule_5_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_5_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = callExpr().bind("gjb511_callExpr");
  Finder->addMatcher(Matcher, this);
}

void Rule_5_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const CallExpr *CE = Result.Nodes.getNodeAs<CallExpr>("gjb511_callExpr")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = CE->getExprLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(CE->getDirectCallee()){
      if(CE->getDirectCallee()->getNameInfo().getAsString() == "longjump"){
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
