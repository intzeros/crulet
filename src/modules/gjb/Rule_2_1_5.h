#ifndef CRULET_GJB_RULE_2_1_5_H
#define CRULET_GJB_RULE_2_1_5_H

#include "../../CruletChecker.h"
#include <vector>

namespace clang {
namespace crulet {
namespace GJB {

class Rule_2_1_5 : public CruletChecker {
public:
  Rule_2_1_5(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
      : CruletChecker(Context, CheckerName, ReportMsg) {
    IsReported = false;
  }

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
  virtual void registerPPCallbacks(CompilerInstance &CI) override;

  void addIncludeSourceLocation(SourceLocation SL);

private:
  std::vector<SourceLocation> IncludeSLVec;
  bool IsReported;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif