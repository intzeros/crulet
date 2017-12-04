#include "Rule_4_5_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_5_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = gotoStmt().bind("goto");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_5_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const GotoStmt *GS = Result.Nodes.getNodeAs<GotoStmt>("goto")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    std::string msg = "[" + CheckerName + "] " + "禁止使用goto语句";
    unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
    DE.Report(GS->getGotoLoc(), DiagID);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
