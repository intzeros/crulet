#ifndef CRULET_GJB_RULE_1_2_9_H
#define CRULET_GJB_RULE_1_2_9_H

#include "../../CruletChecker.h"

namespace clang {

namespace crulet {

namespace GJB {

class Rule_1_2_9: public CruletChecker {
public:
    Rule_1_2_9(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg):
        CruletChecker(Context, CheckerName, ReportMsg) {}

    virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
private:
    bool remarked = false;
};

} // namespace GJB

} // namespace crulet

} // namespace clang

#endif
