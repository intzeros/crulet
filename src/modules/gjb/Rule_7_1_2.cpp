#include "Rule_7_1_2.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_7_1_2::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl(isDefinition()).bind("gjb712_functionDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_7_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb712_functionDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    bool isInMainFuncFile = false;
    for(const auto D : TUD->decls()){
      if(const auto *FD = dyn_cast<FunctionDecl>(D)){
        if(FD->isMain()){
          isInMainFuncFile = true;
          break;
        }
      }
    }

    if(isInMainFuncFile && !FD->isMain() && !FD->isUsed()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
