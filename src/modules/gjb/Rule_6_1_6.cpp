#include "Rule_6_1_6.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_6::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = fieldDecl(isBitField(), hasType(isSignedInteger()), has(integerLiteral(equals(1)))).bind("gjb_4616");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_6::run(const MatchFinder::MatchResult &Result) {
  if(const FieldDecl *FD = Result.Nodes.getNodeAs<FieldDecl>("gjb_4616")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocation(), DiagnosticIDs::Warning);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
