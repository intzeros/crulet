#ifndef CRULET_GJB_RULE_9_1_3_H
#define CRULET_GJB_RULE_9_1_3_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_9_1_3 : public CruletChecker {
public:
  Rule_9_1_3(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
      DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning)
      : CruletChecker(Context, CheckerName, ReportMsg, DiagLevel) {}
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif