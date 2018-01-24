#include "Rule_2_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_2_1_2::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(forStmt().bind("for"), this);
  Finder->addMatcher(whileStmt().bind("while"), this);
  Finder->addMatcher(doStmt().bind("do"), this);
}

void Rule_2_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const auto *S = Result.Nodes.getNodeAs<ForStmt>("for")){
    const auto *Body = S->getBody();
    if(Body && !isa<CompoundStmt>(Body)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getRParenLoc(), DiagnosticIDs::Warning);
    }
  }else if(const auto *S = Result.Nodes.getNodeAs<WhileStmt>("while")){
    const auto *Body = S->getBody();
    if(Body && !isa<CompoundStmt>(Body)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getLocStart(), DiagnosticIDs::Warning);
    }
  }else if(const auto *S = Result.Nodes.getNodeAs<DoStmt>("do")){
    const auto *Body = S->getBody();
    if(Body && !isa<CompoundStmt>(Body)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, S->getLocStart(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
