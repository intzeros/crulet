#ifndef CRULET_GJB_RULE_4_3_1_4_H
#define CRULET_GJB_RULE_4_3_1_4_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_4_3_1_4 : public CruletChecker {
public:
  Rule_4_3_1_4(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
    : CruletChecker(Context, CheckerName, ReportMsg) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif