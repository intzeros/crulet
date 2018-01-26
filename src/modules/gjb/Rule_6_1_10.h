#ifndef CRULET_GJB_RULE_6_1_10_H
#define CRULET_GJB_RULE_6_1_10_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_6_1_10 : public CruletChecker {
public:
  Rule_6_1_10(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
    : CruletChecker(Context, CheckerName, ReportMsg) {}
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif