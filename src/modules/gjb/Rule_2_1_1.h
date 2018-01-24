#ifndef CRULET_GJB_RULE_2_1_1_H
#define CRULET_GJB_RULE_2_1_1_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_2_1_1 : public CruletChecker {
public:
  Rule_2_1_1(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
    : CruletChecker(Context, CheckerName, ReportMsg) {}
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif