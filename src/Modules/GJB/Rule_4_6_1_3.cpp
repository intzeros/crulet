#include "Rule_4_6_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(allOf( \
    eachOf(hasOperatorName("<<"), hasOperatorName(">>"), hasOperatorName("<<="), hasOperatorName(">>=")) \
    , eachOf(hasLHS(expr().bind("gjb4613")), hasRHS(expr().bind("gjb4613")))));
  Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const Expr *EXP = Result.Nodes.getNodeAs<Expr>("gjb4613")){
    const Type* TP = EXP->getType().getTypePtr();
    
    if(TP->isSignedIntegerType()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      std::string msg = "[" + CheckerName + "] " + "禁止对有符号类型进行移位操作";
      unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
      DE.Report(EXP->getLocStart(), DiagID);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
