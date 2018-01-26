#include "Rule_6_1_4.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_4::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(anyOf(
    hasOperatorName("<<"), hasOperatorName(">>"), hasOperatorName("<<="), hasOperatorName(">>="))
  ).bind("shift_op");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("shift_op")){
    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS();

    llvm::APSInt APSIntResult;
    if(LHS->getType().getTypePtr()->isIntegerType() && RHS->EvaluateAsInt(APSIntResult, *Result.Context)){
      TypeInfo TPLHSInfo = Result.Context->getTypeInfo(LHS->getType());
      if(APSIntResult >= TPLHSInfo.Width){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, Op->getExprLoc(), DiagnosticIDs::Warning);
        const auto FixIt = clang::FixItHint::CreateReplacement(RHS->getSourceRange(), "< " + std::to_string(TPLHSInfo.Width));
        DB.AddFixItHint(FixIt);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
