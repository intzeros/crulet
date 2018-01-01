#include "Rule_4_6_1_7.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_7::registerMatchers(MatchFinder *Finder) {
  // DeclarationMatcher Matcher = fieldDecl(isBitField()).bind("gjb_4617");
  // DeclarationMatcher Matcher = fieldDecl(hasType(isInteger()), has(integerLiteral())).bind("gjb_4617");
  // Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_7::run(const MatchFinder::MatchResult &Result) {
  // if(const FieldDecl *FD = Result.Nodes.getNodeAs<FieldDecl>("gjb_4617")){
  //   DiagnosticsEngine &DE = Result.Context->getDiagnostics();
  //   Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocation(), DiagnosticIDs::Warning);
  // }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
