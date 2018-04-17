#include "Rule_15_1_3.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_15_1_3::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl(isDefinition()).bind("gjb1513");
  Finder->addMatcher(Matcher, this);
}

void Rule_15_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb1513")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    for(auto it = FD->param_begin(); it != FD->param_end(); ++it){
      for(const auto D : TUD->decls()){
        if(const auto *VD = dyn_cast<VarDecl>(D)){
          if(VD->getName() == (*it)->getName()){
            DiagnosticsEngine &DE = Result.Context->getDiagnostics();
            Context->report(this->CheckerName, this->ReportMsg, DE, (*it)->getLocation(), this->DiagLevel);
            Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, (*it)->getLocation(), VD->getLocation(), this->DiagLevel);
          }
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
