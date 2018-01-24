#include "Rule_1_2_5.h"
#include "RuleRemarkFunc.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

void Rule_1_2_5::registerPPCallbacks(CompilerInstance &CI)
{
    struct CatchDefineInBlock: PPCallbacks {

    };
    auto &pp = CI.getPreprocessor();
}

void Rule_1_2_5::registerMatchers(MatchFinder *Finder)
{
    Finder->addMatcher(RemarkFunctionDeclMatcher().first, this);
}

void Rule_1_2_5::run(const MatchFinder::MatchResult &Result)
{
    if (const FunctionDecl *decl =
        Result.Nodes.getNodeAs<FunctionDecl>(RemarkFunctionDeclMatcher().second)) {
        if (decl->getBody() == nullptr)
            return;
        auto b = Result.SourceManager->getSpellingLineNumber(decl->getBody()->getLocStart());
        auto e = Result.SourceManager->getSpellingLineNumber(decl->getBody()->getLocEnd());
        ///
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, decl->getLocStart(), DiagnosticIDs::Remark);
    }
}

} // namespace GJB

} // namespace crulet

} // namespace clang
