#include "Rule_3_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = ifStmt(unless(hasElse(stmt()))).bind("onlyif");
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const IfStmt *IS = Result.Nodes.getNodeAs<IfStmt>("onlyif")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, IS->getIfLoc(), DiagnosticIDs::Warning);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
