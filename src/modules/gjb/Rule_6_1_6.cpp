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
  DeclarationMatcher Matcher = fieldDecl(isBitField(), hasType(isSignedInteger()), has(integerLiteral(equals(1)))).bind("gjb616");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_6::run(const MatchFinder::MatchResult &Result) {
  if(const FieldDecl *FD = Result.Nodes.getNodeAs<FieldDecl>("gjb616")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
    Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
