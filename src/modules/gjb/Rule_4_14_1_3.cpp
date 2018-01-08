#include "Rule_4_14_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_14_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_14_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("switch")){
    const Expr* Cond = SS->getCond();
    if(Cond && Cond->isKnownToHaveBooleanValue()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, SS->getSwitchLoc(), DiagnosticIDs::Warning);
      const auto SourceRange = clang::CharSourceRange::getTokenRange(Cond->getLocStart(), Cond->getLocEnd());
      DB.AddSourceRange(SourceRange);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
