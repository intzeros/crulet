#include "Rule_3_1_8.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_8::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt(forEachSwitchCase(caseStmt().bind("gjb318_switchCase")));
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_8::run(const MatchFinder::MatchResult &Result) {
  if(const CaseStmt *CS = Result.Nodes.getNodeAs<CaseStmt>("gjb318_switchCase")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = CS->getCaseLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    auto SubStmt = CS->getSubStmt();
    bool OK = true;
    if(isa<CaseStmt>(SubStmt)){
      OK = false;
    }

    if(!OK){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
