#include "Rule_4_2_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

#include <iostream>

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_4_2_2::registerMatchers(MatchFinder *Finder)
{
    StatementMatcher Matcher = binaryOperator(
        hasEitherOperand(hasType(pointerType()))).bind("remark-pointer-arithmetic-stmt");
    Finder->addMatcher(Matcher, this);
}

void Rule_4_2_2::run(const MatchFinder::MatchResult &Result)
{
    if (const BinaryOperator *stmt =
        Result.Nodes.getNodeAs<BinaryOperator>("remark-pointer-arithmetic-stmt")) {
        if (!(stmt->isAdditiveOp()))
            return;
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, stmt->getLocStart(), DiagnosticIDs::Remark);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
