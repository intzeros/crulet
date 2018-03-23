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
  Finder->addMatcher(ifStmt().bind("gjb213_if"), this);
}

void Rule_2_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const auto *S = Result.Nodes.getNodeAs<IfStmt>("gjb213_if")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = S->getIfLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const auto *Then = S->getThen();
    if(Then && !isa<CompoundStmt>(Then)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getIfLoc(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }

    const auto *Else = S->getElse();
    if(Else && !isa<IfStmt>(Else) && !isa<CompoundStmt>(Else)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getElseLoc(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
