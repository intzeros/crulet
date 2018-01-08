#include "Rule_4_1_3.h"
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

void Rule_4_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = implicitCastExpr().bind("implicitCastExpr");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const ImplicitCastExpr *ICE = Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastExpr")){
    if(strcmp(ICE->getCastKindName(), "FunctionToPointerDecay") == 0){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, ICE->getLocStart(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
