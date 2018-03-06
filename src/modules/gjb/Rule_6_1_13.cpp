#include "Rule_6_1_13.h"
#include "../../utils/CheckUtils.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_13::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = implicitCastExpr(has(declRefExpr().bind("gjb_6113")));
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_13::run(const MatchFinder::MatchResult &Result) {
  if(const DeclRefExpr *DRE = Result.Nodes.getNodeAs<DeclRefExpr>("gjb_6113")){
    if(check_utils::isEnumConstant(DRE)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, DRE->getLocation(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
