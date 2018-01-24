#include "Rule_1_2_3.h"
#include "RuleRemarkFunc.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_3::registerMatchers(MatchFinder *Finder)
{
    Finder->addMatcher(RemarkFunctionDeclMatcher().first, this);
}

void Rule_1_2_3::run(const MatchFinder::MatchResult &Result)
{
    if (remarked)
        return;
    if (const FunctionDecl *decl =
        Result.Nodes.getNodeAs<FunctionDecl>(RemarkFunctionDeclMatcher().second)) {
        if (decl->parameters().size() > 20) {
            remarked = true;
            DiagnosticsEngine &DE = Result.Context->getDiagnostics();
            Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
        }
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
