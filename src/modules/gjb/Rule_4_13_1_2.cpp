#include "Rule_4_13_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_13_1_2::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = varDecl(has(initListExpr().bind("initListExpr")));
  Finder->addMatcher(Matcher, this);
}

void Rule_4_13_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const InitListExpr *ILE = Result.Nodes.getNodeAs<InitListExpr>("initListExpr")){
    for(unsigned int i = 0; i < ILE->getNumInits(); i++){
      const Expr* EXP = ILE->getInit(i);
      if(isa<CastExpr>(EXP)){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, EXP->getExprLoc(), DiagnosticIDs::Warning);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
