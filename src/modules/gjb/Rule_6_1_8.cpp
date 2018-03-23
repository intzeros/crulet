#include "Rule_6_1_8.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_8::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = implicitCastExpr().bind("gjb618_implicitCastExpr");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_8::run(const MatchFinder::MatchResult &Result) {
  if(const ImplicitCastExpr *ICE = Result.Nodes.getNodeAs<ImplicitCastExpr>("gjb618_implicitCastExpr")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ICE->getExprLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    CastKind CK = ICE->getCastKind();
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();

    if(CK == CK_FloatingToIntegral || CK == CK_IntegralToBoolean || CK == CK_FloatingToBoolean){
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }else if(CK == CK_IntegralCast || CK ==  CK_FloatingCast){
      TypeInfo TPInfo1 = Result.Context->getTypeInfo(ICE->getType());
      TypeInfo TPInfo2 = Result.Context->getTypeInfo(ICE->getSubExpr()->getType());
      
      if(TPInfo1.Width < TPInfo2.Width){
        Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
