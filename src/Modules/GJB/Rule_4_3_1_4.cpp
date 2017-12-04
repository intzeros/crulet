#include "Rule_4_3_1_4.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_3_1_4::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_3_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("switch")){
    const SwitchCase* SC = SS->getSwitchCaseList();
    bool HasDefaultStmt = false;
    while(SC){
      if(isa<DefaultStmt>(SC)){
        HasDefaultStmt = true;
        break;
      }
      SC = SC->getNextSwitchCase();
    }

    if(!HasDefaultStmt){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      std::string msg = "[" + CheckerName + "] " + "在switch语句中必须有default语句";
      unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
      DE.Report(SS->getSwitchLoc(), DiagID);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
