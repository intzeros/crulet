#include "Rule_4_6_1_11.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_11::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = unaryOperator(hasOperatorName("!")).bind("unaryOp_not");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_11::run(const MatchFinder::MatchResult &Result) {
  if(const UnaryOperator *Up = Result.Nodes.getNodeAs<UnaryOperator>("unaryOp_not")){
    Expr* EXP = Up->getSubExpr();
    if(isa<IntegerLiteral>(EXP)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      std::string msg = "[" + CheckerName + "] " + "禁止对常数值做逻辑非的运算";
      unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
      DE.Report(Up->getOperatorLoc(), DiagID);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
