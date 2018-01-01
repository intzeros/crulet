#include "Rule_4_6_1_16.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_16::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(anyOf(hasOperatorName("||"), hasOperatorName("&&")),
                                hasDescendant(binaryOperator(hasOperatorName("=")))
                              ).bind("gjb_46116");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_16::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb_46116")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, Op->getOperatorLoc(), DiagnosticIDs::Warning);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
