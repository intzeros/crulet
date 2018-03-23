#include "Rule_6_1_17.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_17::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(hasOperatorName("|")).bind("gjb_46117");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_17::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb_46117")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }
    
    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS();
    if(LHS->isKnownToHaveBooleanValue() || RHS->isKnownToHaveBooleanValue()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);

      const auto Start = Op->getOperatorLoc();
      const auto End = Start.getLocWithOffset(+1);
      const auto SourceRange = clang::CharSourceRange::getCharRange(Start, End);
      const auto FixIt = clang::FixItHint::CreateReplacement(SourceRange, "||");
      DB.AddFixItHint(FixIt);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
