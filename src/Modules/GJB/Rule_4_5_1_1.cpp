#include "Rule_4_5_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_5_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = callExpr().bind("call_expr");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_5_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const CallExpr *CE = Result.Nodes.getNodeAs<CallExpr>("call_expr")){
    if(CE->getDirectCallee()->getNameInfo().getAsString() == "longjump"){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      std::string msg = "[" + CheckerName + "] " + "禁止直接从过程中跳出";
      unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
      DE.Report(CE->getLocStart(), DiagID);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
