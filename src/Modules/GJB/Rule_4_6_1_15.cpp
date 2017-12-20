#include "Rule_4_6_1_15.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_15::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = stmt(anyOf(
    ifStmt(hasCondition(binaryOperator(hasOperatorName("=")).bind("gjb46115"))),
    ifStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb46115"))))),
    forStmt(hasCondition(binaryOperator(hasOperatorName("=")).bind("gjb46115"))),
    forStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb46115"))))),
    whileStmt(hasCondition(binaryOperator(hasOperatorName("=")).bind("gjb46115"))),
    whileStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb46115")))))
  ));
  Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_15::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb46115")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    std::string msg = "[" + CheckerName + "] " + "禁止在逻辑表达式中使用赋值操作符";
    unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
    DE.Report(Op->getOperatorLoc(), DiagID);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
