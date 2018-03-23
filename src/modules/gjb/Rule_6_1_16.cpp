#include "Rule_6_1_16.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_16::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(anyOf(hasOperatorName("||"), hasOperatorName("&&")),
                                hasDescendant(binaryOperator(hasOperatorName("=")))
                              ).bind("gjb6116");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_16::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb6116")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
    Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
