#include "Rule_1_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_3::registerMatchers(MatchFinder *Finder) {
  
}

void Rule_1_1_3::run(const MatchFinder::MatchResult &Result) {
  
}

} // namespace GJB
} // namespace crulet
} // namespace clang
