#include "Rule_2_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_2_1_3::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(ifStmt().bind("if"), this);
}

void Rule_2_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const auto *S = Result.Nodes.getNodeAs<IfStmt>("if")){
    const auto *Then = S->getThen();
    if(Then && !isa<CompoundStmt>(Then)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getIfLoc(), DiagnosticIDs::Warning);
    }

    const auto *Else = S->getElse();
    if(Else && !isa<IfStmt>(Else) && !isa<CompoundStmt>(Else)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getElseLoc(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
