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
  DeclarationMatcher Matcher = valueDecl(hasType(isAnyCharacter())).bind("valueDecl_char");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_15::run(const MatchFinder::MatchResult &Result) {
  if(const ValueDecl *VD = Result.Nodes.getNodeAs<ValueDecl>("valueDecl_char")){
    if(VD->getType().getAsString() == "char"){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, VD->getLocStart(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
