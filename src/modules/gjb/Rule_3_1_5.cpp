#include "Rule_3_1_5.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_5::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("gjb315_switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_5::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("gjb315_switch")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = SS->getSwitchLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const SwitchCase* SC = SS->getSwitchCaseList();
    
    if(!SC){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
