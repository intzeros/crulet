#include "Rule_7_1_9.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_7_1_9::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = callExpr().bind("gjb719_call");
  Finder->addMatcher(Matcher, this);
}

void Rule_7_1_9::run(const MatchFinder::MatchResult &Result) {
  if(const CallExpr *CE = Result.Nodes.getNodeAs<CallExpr>("gjb719_call")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = CE->getLocStart();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    for(auto it = CE->arg_begin(); it != CE->arg_end(); ++it){
      auto QT1 = (*it)->getType();
      auto QT2 = (*it)->IgnoreParenImpCasts()->getType();
      if(QT1.getAsString() != QT2.getAsString()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, (*it)->getLocStart(), this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, (*it)->getLocStart(), this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
