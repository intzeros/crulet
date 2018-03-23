#include "Rule_8_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_8_1_1::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl(anyOf(hasName("l"), hasName("O"))).bind("gjb811");
  Finder->addMatcher(Matcher, this);
}

void Rule_8_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("gjb811")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ND->getLocation();
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
