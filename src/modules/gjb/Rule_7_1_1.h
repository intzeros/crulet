#ifndef CRULET_GJB_RULE_7_1_1_H
#define CRULET_GJB_RULE_7_1_1_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_7_1_1 : public CruletChecker {
public:
  Rule_7_1_1(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
      DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning)
      : CruletChecker(Context, CheckerName, ReportMsg, DiagLevel) {}

};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif