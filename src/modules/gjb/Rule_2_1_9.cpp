#include "Rule_2_1_9.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_2_1_9::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = stringLiteral().bind("stringLiteral");
  Finder->addMatcher(Matcher, this);
}

void Rule_2_1_9::run(const MatchFinder::MatchResult &Result) {
  if(const StringLiteral *SL = Result.Nodes.getNodeAs<StringLiteral>("stringLiteral")){
    unsigned Length = SL->getLength();
    StringRef Str = SL->getString();

    if(Length != 0 && Str[Length-1] != '\0'){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL->getLocEnd(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
