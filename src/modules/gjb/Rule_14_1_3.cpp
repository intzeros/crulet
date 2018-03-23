#include "Rule_14_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_14_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("gjb1413_switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_14_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("gjb1413_switch")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = SS->getSwitchLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const Expr* Cond = SS->getCond();
    if(Cond && Cond->isKnownToHaveBooleanValue()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
      
      const auto SourceRange = clang::CharSourceRange::getTokenRange(Cond->getLocStart(), Cond->getLocEnd());
      DB.AddSourceRange(SourceRange);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
