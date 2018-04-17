#include "Rule_6_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = arraySubscriptExpr().bind("gjb612");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const ArraySubscriptExpr *ASE = Result.Nodes.getNodeAs<ArraySubscriptExpr>("gjb612")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ASE->getExprLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const Expr* LHS = ASE->getLHS()->IgnoreImpCasts();
    const Expr* RHS = ASE->getRHS();
    const DeclRefExpr* DRE = dyn_cast<DeclRefExpr>(LHS);

    llvm::APSInt APSIntResult;
    if(DRE && RHS->EvaluateAsInt(APSIntResult, *Result.Context)){
      const Type* TP = DRE->getDecl()->getType().getTypePtr();
      if(const ConstantArrayType* ATP = dyn_cast<ConstantArrayType>(TP)){
        if(APSIntResult.getExtValue() >= ATP->getSize().getLimitedValue()){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
