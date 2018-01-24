#ifndef RULE_REMARK_FUNC_H
#define RULE_REMARK_FUNC_H

#include <map>

#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"

using namespace clang::ast_matchers;

namespace clang {

namespace crulet {

namespace GJB {

inline std::pair<const DeclarationMatcher &, const char *> RemarkFunctionDeclMatcher()
{
    static DeclarationMatcher Matcher = functionDecl().bind("gjb-remark-function-decl");
    return std::make_pair(Matcher, "gjb-remark-function-decl");
}

} // namespace GJB

} // namespace crulet

} // namespace clang


#endif
