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
  Finder->addMatcher(forStmt().bind("gjb212_for"), this);
  Finder->addMatcher(whileStmt().bind("gjb212_while"), this);
  Finder->addMatcher(doStmt().bind("gjb212_do"), this);
}

void Rule_2_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const auto *S = Result.Nodes.getNodeAs<ForStmt>("gjb212_for")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = S->getRParenLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const auto *Body = S->getBody();
    if(Body && !isa<CompoundStmt>(Body)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }else if(const auto *S = Result.Nodes.getNodeAs<WhileStmt>("gjb212_while")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = S->getLocStart();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const auto *Body = S->getBody();
    if(Body && !isa<CompoundStmt>(Body)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }else if(const auto *S = Result.Nodes.getNodeAs<DoStmt>("gjb212_do")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = S->getLocStart();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const auto *Body = S->getBody();
    if(Body && !isa<CompoundStmt>(Body)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
