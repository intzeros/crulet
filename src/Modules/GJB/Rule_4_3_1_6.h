#ifndef CRULET_GJB_RULE_4_3_1_6_H
#define CRULET_GJB_RULE_4_3_1_6_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_4_3_1_6 : public CruletChecker {
public:
  Rule_4_3_1_6(StringRef CheckerName)
    : CruletChecker(CheckerName) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif