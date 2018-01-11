#include "Rule_1_1_7.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_7::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = parmVarDecl().bind("parmVarDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_7::run(const MatchFinder::MatchResult &Result) {
  if(const ParmVarDecl *PD = Result.Nodes.getNodeAs<ParmVarDecl>("parmVarDecl")){
    if(PD->getName() == ""){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, PD->getLocStart(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
