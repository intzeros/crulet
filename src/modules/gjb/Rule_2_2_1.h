#ifndef CRULET_GJB_RULE_2_2_1_H
#define CRULET_GJB_RULE_2_2_1_H

#include "../../CruletChecker.h"

namespace clang {

namespace crulet {

namespace GJB {

class Rule_2_2_1: public CruletChecker {
public:
    Rule_2_2_1(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg):
        CruletChecker(Context, CheckerName, ReportMsg) {}

    virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
private:
    size_t program_line = 0;
    bool remarked = false;
};

} // namespace GJB

} // namespace crulet

} // namespace clang

#endif
