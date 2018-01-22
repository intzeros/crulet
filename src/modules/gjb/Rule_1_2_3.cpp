#include "Rule_1_2_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_3::registerMatchers(MatchFinder *Finder)
{
    DeclarationMatcher Matcher = functionDecl().bind("function-decl-20-para");
    Finder->addMatcher(Matcher, this);
}

void Rule_1_2_3::run(const MatchFinder::MatchResult &Result)
{
    if (const FunctionDecl *decl = Result.Nodes.getNodeAs<FunctionDecl>("function-decl-20-para")) {
        if (decl->parameters().size() > 20) {
            DiagnosticsEngine &DE = Result.Context->getDiagnostics();
            Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
        }
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
