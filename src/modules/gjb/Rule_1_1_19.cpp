#include "Rule_1_1_19.h"
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

void Rule_1_1_19::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = varDecl(has(initListExpr())).bind("gjb1119_Array");
  Finder->addMatcher(Matcher, this);
}

bool Rule_1_1_19::check(std::string var, std::string text){
  size_t start = text.find(var);
  if(start == std::string::npos){
    return false;
  }

  for(unsigned int i = start; i < text.size(); i++){
    if(text[i] == '['){
      i++;
      while(text[i] == ' ') i++;
      if(text[i] == ']') return true;
      else return false;
    }else if(text[i] == ']'){
      break;
    }
  }
  return false;
}

void Rule_1_1_19::run(const MatchFinder::MatchResult &Result) {
  if(const VarDecl *VD = Result.Nodes.getNodeAs<VarDecl>("gjb1119_Array")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = VD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    std::string text = Lexer::getSourceText(CharSourceRange::getTokenRange(VD->getSourceRange()), SM, LangOptions(), 0);

    if(check(VD->getName(), text)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
