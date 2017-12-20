#include "Rule_4_6_1_12.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_12::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(anyOf(
    hasOperatorName("<<"), hasOperatorName(">>"), hasOperatorName("<<="), hasOperatorName(">>=")
    , hasOperatorName("|"), hasOperatorName("|="), hasOperatorName("&"), hasOperatorName("&=")
    , hasOperatorName("^"), hasOperatorName("^="), hasOperatorName("~"))
  ).bind("bitwise_op");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_12::run(const MatchFinder::MatchResult &Result) {
  // if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("bitwise_op")){
  //   Expr* LHS = Op->getLHS();
  //   const Type* TP = LHS->getType().getTypePtr();
    
  //   if(TP->isSignedIntegerType()){
  //     DiagnosticsEngine &DE = Result.Context->getDiagnostics();
  //     std::string msg = "[" + CheckerName + "] " + "禁止对有符号类型进行移位操作";
  //     unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
  //     DE.Report(LHS->get  LocStart(), DiagID);
  //   }
  // }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
