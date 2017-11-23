#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECKER_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECKER_H

#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
namespace crulet {

class CruletChecker : public ast_matchers::MatchFinder::MatchCallback {
public:
  CruletChecker(StringRef CheckerName)
    : CheckerName(CheckerName) {}
  virtual ~CruletChecker() {}
  
  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) {}
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) = 0;

protected:
  std::string CheckerName;
};

} // namespace crulet
} // namespace clang

#endif