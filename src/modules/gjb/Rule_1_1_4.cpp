#include "Rule_1_1_4.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_4::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = labelStmt(has(labelStmt())).bind("multi_labelStmt");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const LabelStmt *LS = Result.Nodes.getNodeAs<LabelStmt>("multi_labelStmt")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, LS->getIdentLoc(), DiagnosticIDs::Warning);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
