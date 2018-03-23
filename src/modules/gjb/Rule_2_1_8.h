#ifndef CRULET_GJB_RULE_2_1_8_H
#define CRULET_GJB_RULE_2_1_8_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_2_1_8 : public CruletChecker {
public:
  Rule_2_1_8(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
      DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning)
      : CruletChecker(Context, CheckerName, ReportMsg, DiagLevel) {}

  virtual void registerPPCallbacks(CompilerInstance &CI) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif