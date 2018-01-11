#include "Rule_1_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_1::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl().bind("namedDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *CurND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    for(const auto D : TUD->decls()){
      if(const auto *FD = dyn_cast<FunctionDecl>(D)){
        if(CurND != FD && CurND->getName() == FD->getName()){
          if(!isa<FunctionDecl>(CurND)){
            DiagnosticsEngine &DE = Result.Context->getDiagnostics();
            Context->report(this->CheckerName, this->ReportMsg, DE, CurND->getLocation(), DiagnosticIDs::Warning);
          }
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
