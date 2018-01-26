#include "Rule_6_1_9.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_9::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = implicitCastExpr().bind("implicitCastExpr");
  Finder->addMatcher(Matcher, this);
}

void Rule_6_1_9::run(const MatchFinder::MatchResult &Result) {
  if(const ImplicitCastExpr *ICE = Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastExpr")){
    CastKind CK = ICE->getCastKind();
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();

    if(CK == CK_FloatingToIntegral || CK == CK_IntegralToBoolean || CK == CK_FloatingToBoolean){
      Context->report(this->CheckerName, this->ReportMsg, DE, ICE->getLocStart(), DiagnosticIDs::Warning);
    }else if(CK == CK_IntegralCast || CK ==  CK_FloatingCast){
      TypeInfo TPInfo1 = Result.Context->getTypeInfo(ICE->getType());
      TypeInfo TPInfo2 = Result.Context->getTypeInfo(ICE->getSubExpr()->getType());
      if(TPInfo1.Width < TPInfo2.Width){
        Context->report(this->CheckerName, this->ReportMsg, DE, ICE->getLocStart(), DiagnosticIDs::Warning);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
