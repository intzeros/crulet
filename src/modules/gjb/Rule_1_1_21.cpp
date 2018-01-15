#include "Rule_1_1_21.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_21::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = recordDecl().bind("recordDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_21::run(const MatchFinder::MatchResult &Result) {
  if(const RecordDecl *RD = Result.Nodes.getNodeAs<RecordDecl>("recordDecl")){
    if(!RD->isCompleteDefinition()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, RD->getLocStart(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
