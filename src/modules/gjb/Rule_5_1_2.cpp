#include "Rule_5_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_5_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = gotoStmt().bind("gjb512_goto");
  Finder->addMatcher(Matcher, this);
}

void Rule_5_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const GotoStmt *GS = Result.Nodes.getNodeAs<GotoStmt>("gjb512_goto")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = GS->getGotoLoc();
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
