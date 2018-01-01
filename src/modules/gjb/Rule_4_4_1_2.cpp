#include "Rule_4_4_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_4_1_2::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = valueDecl(anyOf(varDecl(), fieldDecl())).bind("vardecl_fielddecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_4_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const ValueDecl *VD = Result.Nodes.getNodeAs<ValueDecl>("vardecl_fielddecl")){
    if(VD->getType()->isPointerType() == false){
      return;
    }

    if(isa<VarDecl>(VD)){
      VD = dyn_cast<VarDecl>(VD);
    }else if(isa<FieldDecl>(VD)){
      VD = dyn_cast<FieldDecl>(VD);
    }else return;

    std::string VDTypeString = VD->getType().getCanonicalType().getAsString();
    int PointerLevel = 0u;

    for(unsigned int i = 0; i < VDTypeString.size(); i++){
      if(VDTypeString[i] == '*'){
        PointerLevel++;
        if(PointerLevel > 2){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, VD->getLocation(), DiagnosticIDs::Warning);
          break;
        }
      }else if(VDTypeString[i] == '('){
        PointerLevel = 0;
      }else if(VDTypeString[i] == ')'){
        break;
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
