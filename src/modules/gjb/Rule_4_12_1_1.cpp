#include "Rule_4_12_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include <string.h>

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_12_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = cStyleCastExpr().bind("cStyleCastExpr");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_12_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const CStyleCastExpr *CCE = Result.Nodes.getNodeAs<CStyleCastExpr>("cStyleCastExpr")){
    if(strcmp(CCE->getCastKindName(), "IntegralToPointer") == 0){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, CCE->getRParenLoc(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
