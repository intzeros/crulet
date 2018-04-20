#include "Rule_9_1_4.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_9_1_4::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl(
                                  isDefinition(), 
                                  hasDescendant(returnStmt())
                                ).bind("gjb914");
  Finder->addMatcher(Matcher, this);
}

void Rule_9_1_4::checkReturnStmtByDFS(const Stmt *S, const FunctionDecl *FD, SourceManager &SM, DiagnosticsEngine &DE){
  if(S == nullptr) return;

  if(const auto *RS = dyn_cast<ReturnStmt>(S)){
    if(const auto *RE = RS->getRetValue()){
      RE = RE->IgnoreParenImpCasts();
      if(RE->getType() != FD->getReturnType()){
        Context->report(this->CheckerName, this->ReportMsg, DE, RS->getLocStart(), this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, RS->getLocStart(), this->DiagLevel);
      }
    }
  }

  for(auto it = S->child_begin(); it != S->child_end(); ++it){
    checkReturnStmtByDFS(*it, FD, SM, DE);
  }
}

void Rule_9_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb914")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(FD->getReturnType().getAsString() == "void"){
      return;
    }

    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    checkReturnStmtByDFS(FD->getBody(), FD, SM, DE);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
