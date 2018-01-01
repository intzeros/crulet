#include "Rule_4_3_1_5.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_3_1_5::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_3_1_5::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("switch")){
    const SwitchCase* SC = SS->getSwitchCaseList();
    
    if(!SC){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SS->getSwitchLoc(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
