#include "Rule_4_3_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_3_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = ifStmt(unless(hasElse(stmt()))).bind("onlyif");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_3_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const IfStmt *IS = Result.Nodes.getNodeAs<IfStmt>("onlyif")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    std::string msg = "[" + CheckerName + "] " + "在if...else if语句中必须使用else分支";
    unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
    DE.Report(IS->getIfLoc(), DiagID);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
