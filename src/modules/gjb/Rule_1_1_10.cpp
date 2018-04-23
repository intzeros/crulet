#include "Rule_1_1_10.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_10::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl().bind("gjb1110_functionDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_10::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb1110_functionDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(FD->isImplicit()){
      return;
    }

    if(FD->param_size() == 0){
      std::string Name = FD->getType().getCanonicalType().getAsString();
      if(Name.find(')') - Name.find('(') == 1){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
