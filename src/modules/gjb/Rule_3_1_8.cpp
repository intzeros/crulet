#include "Rule_3_1_8.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_8::registerMatchers(MatchFinder *Finder) {
  // StatementMatcher Matcher = switchStmt(forEachSwitchCase(caseStmt().bind("gjb318_switchCase")));
  StatementMatcher Matcher = switchStmt().bind("gjb318_switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_8::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *Switch = Result.Nodes.getNodeAs<SwitchStmt>("gjb318_switch")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Switch->getSwitchLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const SwitchCase* SC = Switch->getSwitchCaseList();
    bool OK = true;
    while(SC){
      if(const CaseStmt* Case = dyn_cast<CaseStmt>(SC)){
        auto SubStmt = Case->getSubStmt();
        if(isa<CaseStmt>(SubStmt)){
          OK = false;
          break;
        }
      }
      SC = SC->getNextSwitchCase();
    }

    if(!OK){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SC->getLocStart(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SC->getLocStart(), this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
