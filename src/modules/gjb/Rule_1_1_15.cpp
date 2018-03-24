#include "Rule_1_1_15.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_15::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = valueDecl(hasType(isAnyCharacter())).bind("gjb1115_valueDecl_char");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_15::run(const MatchFinder::MatchResult &Result) {
  if(const ValueDecl *VD = Result.Nodes.getNodeAs<ValueDecl>("gjb1115_valueDecl_char")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = VD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(VD->getType().getAsString() == "char"){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
