#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECK_UTILS_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECK_UTILS_H

#include "clang/AST/Expr.h"
#include <unordered_set>
#include <string>

namespace clang {
namespace crulet {
namespace check_utils {

extern std::unordered_set<std::string> CPPKeywords;

bool isCPPKeyword(std::string Name);

bool isEnumConstant(const Expr *E);

} // namespace check_utils
} // namespace crulet
} // namespace clang

#endif