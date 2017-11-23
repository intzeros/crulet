#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_SIDE_EFFECT_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_SIDE_EFFECT_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_4_3_1_4 : public CruletChecker {
public:
  Rule_4_3_1_4(StringRef CheckerName)
    : CruletChecker(CheckerName) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif