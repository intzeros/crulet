#include "Rule_4_13_1_4.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_13_1_4::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = varDecl().bind("varDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_13_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const VarDecl *VD = Result.Nodes.getNodeAs<VarDecl>("varDecl")){
    // if(!VD->hasInit()){

    // }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
