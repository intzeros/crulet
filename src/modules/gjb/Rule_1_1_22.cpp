#include "Rule_1_1_22.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_22::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl().bind("functionDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_22::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("functionDecl")){
    if(!FD->isThisDeclarationADefinition()){
      size_t Count1 = 0, Count2 = 0;
      for(auto it = FD->param_begin(); it != FD->param_end(); ++it){
        if((*it)->getName() == ""){
          Count1++;
        }else{
          Count2++;
        }
      }

      if(Count1 != FD->param_size() || Count2 != FD->param_size()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocStart(), DiagnosticIDs::Warning);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
