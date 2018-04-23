#include "Rule_1_1_3.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_3::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = recordDecl(has(recordDecl().bind("gjb113")));
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const RecordDecl *RD = Result.Nodes.getNodeAs<RecordDecl>("gjb113")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = RD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(RD->isAnonymousStructOrUnion()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
