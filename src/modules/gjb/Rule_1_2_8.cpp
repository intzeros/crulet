#include "Rule_1_2_8.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_8::registerMatchers(MatchFinder *Finder)
{
    DeclarationMatcher Matcher = recordDecl(isUnion()).bind("exclude-union-record");
    Finder->addMatcher(Matcher, this);
}

void Rule_1_2_8::run(const MatchFinder::MatchResult &Result)
{
    if (remarked)
        return;
    if (const RecordDecl *decl = Result.Nodes.getNodeAs<RecordDecl>("exclude-union-record")) {
        remarked = true;
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
