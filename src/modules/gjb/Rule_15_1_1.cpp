#include "Rule_15_1_1.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_15_1_1::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = enumConstantDecl().bind("gjb1511_enum");
  Finder->addMatcher(Matcher, this);
}

void Rule_15_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const EnumConstantDecl *ECD = Result.Nodes.getNodeAs<EnumConstantDecl>("gjb1511_enum")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ECD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    for(const auto D : TUD->decls()){
      if(const auto *VD = dyn_cast<VarDecl>(D)){
        if(!VD->hasExternalStorage() && VD->getName() == ECD->getName()){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, VD->getLocation(), this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, VD->getLocation(), SL, this->DiagLevel);
        }
      }else if(const auto *FD = dyn_cast<FunctionDecl>(D)){
        if(FD->isThisDeclarationADefinition() && FD->getName() == ECD->getName()){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocation(), this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, FD->getLocation(), SL, this->DiagLevel);
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
