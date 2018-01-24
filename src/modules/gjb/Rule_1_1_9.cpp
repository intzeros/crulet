#include "Rule_1_1_9.h"
#include "../../utils/CheckUtils.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_9::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl().bind("namedDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_9::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
    if(check_utils::isCPPKeyword(ND->getName())){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, ND->getLocation(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
