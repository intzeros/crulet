#include "Rule_4_3_1_7.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_3_1_7::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_3_1_7::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("switch")){
    auto SSBody = SS->getBody();
    bool OK = true;
    auto PreStmtItr = SSBody->child_end();
    SourceLocation CaseLocation;
    
    for(auto it = SSBody->child_begin(); it != SSBody->child_end(); ++it){
      if(isa<CaseStmt>(*it)){

        if(PreStmtItr != SSBody->child_end() && !isa<BreakStmt>(*PreStmtItr)){
          OK = false;
          break;
        }

        CaseLocation = cast<CaseStmt>(*it)->getCaseLoc();
      }
      PreStmtItr = it;
    }

    if(!OK){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      std::string msg = "[" + CheckerName + "] " + "禁止switch的case语句不是由break终止";
      unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
      DE.Report(CaseLocation, DiagID);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
