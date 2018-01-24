#include "Rule_2_2_1.h"
#include "RuleRemarkFunc.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_2_2_1::registerMatchers(MatchFinder *Finder)
{
    Finder->addMatcher(RemarkFunctionDeclMatcher().first, this);
}

void Rule_2_2_1::run(const MatchFinder::MatchResult &Result)
{
    if (remarked)
        return;
    if (const FunctionDecl *decl =
        Result.Nodes.getNodeAs<FunctionDecl>(RemarkFunctionDeclMatcher().second)) {
        if (decl->getBody() == nullptr)
            return;
        auto b = Result.SourceManager->getSpellingLineNumber(decl->getBody()->getLocStart());
        auto e = Result.SourceManager->getSpellingLineNumber(decl->getBody()->getLocEnd());
        if ((program_line += e - b) < 2000)
            return;
        remarked = true;
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
