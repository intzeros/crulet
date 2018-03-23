#ifndef CRULET_GJB_RULE_1_1_19_H
#define CRULET_GJB_RULE_1_1_19_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_1_1_19 : public CruletChecker {
public:
  Rule_1_1_19(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
      DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning)
      : CruletChecker(Context, CheckerName, ReportMsg, DiagLevel) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
  bool check(std::string var, std::string text);
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif