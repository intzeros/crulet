#include "Rule_2_2_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_2_2_2::registerMatchers(MatchFinder *Finder)
{
    DeclarationMatcher Matcher = functionDecl().bind("function-single-more-than-200-decl");
    Finder->addMatcher(Matcher, this);
}

void Rule_2_2_2::run(const MatchFinder::MatchResult &Result)
{
    if (const FunctionDecl *decl =
        Result.Nodes.getNodeAs<FunctionDecl>("function-single-more-than-200-decl")) {
        if (decl->getBody() == nullptr)
            return;
        auto b = Result.SourceManager->getSpellingLineNumber(decl->getBody()->getLocStart());
        auto e = Result.SourceManager->getSpellingLineNumber(decl->getBody()->getLocEnd());
        if (e - b < 200)
            return;
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
