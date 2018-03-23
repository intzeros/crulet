#include "Rule_13_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_13_1_1::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = enumDecl().bind("gjb1311_enumDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_13_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const EnumDecl *ED = Result.Nodes.getNodeAs<EnumDecl>("gjb1311_enumDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ED->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }
    
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
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
