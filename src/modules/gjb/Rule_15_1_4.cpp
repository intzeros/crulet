#include "Rule_15_1_4.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_15_1_4::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl(isDefinition()).bind("gjb1514");
  Finder->addMatcher(Matcher, this);
}

bool Rule_15_1_4::isValidDeclaratorDecl(const Decl *D){
  if(const auto *FD = dyn_cast<FunctionDecl>(D)){
    return FD->isThisDeclarationADefinition();
  }else if(const auto *VD = dyn_cast<VarDecl>(D)){
    return !VD->hasExternalStorage();
  }
  return isa<DeclaratorDecl>(D);
}

void Rule_15_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb1514")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    for(auto it = FD->param_begin(); it != FD->param_end(); ++it){
      for(const auto D : TUD->decls()){
        if(isValidDeclaratorDecl(D) || isa<TypeDecl>(D)){
          const auto *ND = dyn_cast<NamedDecl>(D);
          if(ND->getName() == (*it)->getName()){
            DiagnosticsEngine &DE = Result.Context->getDiagnostics();
            Context->report(this->CheckerName, this->ReportMsg, DE, (*it)->getLocation(), this->DiagLevel);
            Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, (*it)->getLocation(), ND->getLocation(), this->DiagLevel);
          }
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
