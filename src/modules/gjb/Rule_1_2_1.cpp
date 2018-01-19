#include "Rule_1_2_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_1::registerMatchers(MatchFinder *Finder)
{
    DeclarationMatcher Matcher = declaratorDecl().bind("declarator-decl");
    Finder->addMatcher(Matcher, this);
}

void Rule_1_2_1::run(const MatchFinder::MatchResult &Result)
{
    if (const DeclaratorDecl *decl = Result.Nodes.getNodeAs<DeclaratorDecl>("declarator-decl")) {
        auto qt = decl->getType();
        auto type = qt.getTypePtr();
        while (type && (type->isFunctionType() || type->isArrayType() || type->isPointerType())) {
            if (type->isFunctionType())
                type = type->getAs<FunctionType>()->getReturnType().getTypePtr();
            if (type->isArrayType() || type->isPointerType())
                type = type->getPointeeOrArrayElementType();
        }
        if (!type || !type->isBuiltinType() || type->isVoidType() || type->getAs<TypedefType>())
            return;
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Note);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
