#ifndef CRULET_GJB_RULE_1_1_11_H
#define CRULET_GJB_RULE_1_1_11_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_1_1_11 : public CruletChecker {
public:
  Rule_1_1_11(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
    : CruletChecker(Context, CheckerName, ReportMsg) {}

  virtual void registerPPCallbacks(CompilerInstance &CI) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif