#include "Rule_1_1_17.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_17::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl(anyOf(
                                          functionDecl(isDefinition()),
                                          fieldDecl(),
                                          varDecl(isDefinition()),
                                          enumConstantDecl(),
                                          labelDecl(), 
                                          typedefDecl(),
                                          enumDecl(isDefinition()), 
                                          recordDecl(isDefinition())
                                        )).bind("gjb1117_namedDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_17::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("gjb1117_namedDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ND->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
    for(const auto D : TUD->decls()){
      if(const auto *TD = dyn_cast<TypedefDecl>(D)){
        if(ND != TD && ND->getName() == TD->getName()){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, TD->getLocation(), this->DiagLevel);
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
