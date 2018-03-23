#include "Rule_1_1_5.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_5::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl().bind("gjb115_functionDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_5::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb115_functionDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    for(auto it = FD->param_begin(); it != FD->param_end(); ++it){
      std::string text = Lexer::getSourceText(CharSourceRange::getTokenRange((*it)->getSourceRange()), SM, LangOptions(), 0);
      int NumTokens = 1;
      for(unsigned int i = 0; i < text.size(); i++){
        if(i > 0 && text[i] == ' ' && text[i-1] != ' '){
          NumTokens++;
        }
      }

      if(NumTokens == 1){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, (*it)->getLocation(), this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, (*it)->getLocation(), this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
