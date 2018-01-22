#include "Rule_1_2_9.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_9::registerMatchers(MatchFinder *Finder)
{
    DeclarationMatcher Matcher = recordDecl(allOf(
        has(fieldDecl().bind("field-uname-bit-field")), isStruct()));
    Finder->addMatcher(Matcher, this);
}

void Rule_1_2_9::run(const MatchFinder::MatchResult &Result)
{
    if (const FieldDecl *decl = Result.Nodes.getNodeAs<FieldDecl>("field-uname-bit-field")) {
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
