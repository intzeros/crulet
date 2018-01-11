#include "Rule_1_1_6.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_6::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl(unless(isDefinition())).bind("functionDecl_nobody");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_6::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("functionDecl_nobody")){
    const FunctionDecl *OrgFD = FD->getDefinition();
    if(OrgFD && FD->param_size() == 0 && OrgFD->param_size() != 0){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocStart(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
