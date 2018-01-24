#include "Rule_1_2_2.h"
#include "RuleRemarkFunc.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_2::registerMatchers(MatchFinder *Finder)
{
    Finder->addMatcher(RemarkFunctionDeclMatcher().first, this);
}

void Rule_1_2_2::run(const MatchFinder::MatchResult &Result)
{
    if (remarked)
        return;
    if (const FunctionDecl *decl =
        Result.Nodes.getNodeAs<FunctionDecl>(RemarkFunctionDeclMatcher().second)) {
        for (auto p : decl->parameters()) {
            auto type = p->getType().getTypePtr();
            if (type && type->isFunctionPointerType()) {
                remarked = true;
                DiagnosticsEngine &DE = Result.Context->getDiagnostics();
                Context->report(this->CheckerName, this->ReportMsg, DE, p->getLocStart(), DiagnosticIDs::Remark);
                break;
            }
        }
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
