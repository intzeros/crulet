#include "Rule_15_1_2.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_15_1_2::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = varDecl(isDefinition()).bind("gjb1512");
  Finder->addMatcher(Matcher, this);
}

void Rule_15_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const VarDecl *CurVD = Result.Nodes.getNodeAs<VarDecl>("gjb1512")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = CurVD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(!CurVD->isLocalVarDecl()){
      return;
    }

    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    for(const auto D : TUD->decls()){
      if(const auto *VD = dyn_cast<VarDecl>(D)){
        if(VD->getName() == CurVD->getName()){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, VD->getLocation(), this->DiagLevel);
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
