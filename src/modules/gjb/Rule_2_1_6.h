#ifndef CRULET_GJB_RULE_2_1_6_H
#define CRULET_GJB_RULE_2_1_6_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_2_1_6 : public CruletChecker {
public:
  Rule_2_1_6(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
    : CruletChecker(Context, CheckerName, ReportMsg) {}

  virtual void registerPPCallbacks(CompilerInstance &CI) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif