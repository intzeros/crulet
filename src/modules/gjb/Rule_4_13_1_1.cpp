#include "Rule_4_13_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_13_1_1::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = enumDecl().bind("enumDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_13_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const EnumDecl *ED = Result.Nodes.getNodeAs<EnumDecl>("enumDecl")){
    int InitCount = 0, TotalCount = 0;
    bool IsFirstInit = false;
    for(auto it = ED->enumerator_begin(); it != ED->enumerator_end(); ++it){
      const Expr* EXP = (*it)->getInitExpr();
      if(EXP){
        if(it == ED->enumerator_begin()){
          IsFirstInit = true;
        }
        InitCount++;
      }
      TotalCount++;
    }

    bool IsSafe = false;
    if(InitCount == TotalCount || (InitCount == 1 && IsFirstInit)){
      IsSafe = true;
    }

    if(!IsSafe){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, ED->getLocation(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
