#include "Rule_14_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_14_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(hasOperatorName("==")).bind("gjb1411_equalComp");
  Finder->addMatcher(Matcher, this);
}

void Rule_14_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb1411_equalComp")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = Op->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }
    
    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS();
    if(LHS && RHS){
      const Type *LHSType = LHS->getType().getTypePtr();
      const Type *RHSType = RHS->getType().getTypePtr();
      if((LHSType && LHSType->isRealFloatingType()) || (RHSType && RHSType->isRealFloatingType())){
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
