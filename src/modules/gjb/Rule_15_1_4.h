#ifndef CRULET_GJB_RULE_15_1_4_H
#define CRULET_GJB_RULE_15_1_4_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_15_1_4 : public CruletChecker {
public:
  Rule_15_1_4(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
      DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning)
      : CruletChecker(Context, CheckerName, ReportMsg, DiagLevel) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
  bool isValidDeclaratorDecl(const Decl *D);
};


} // namespace GJB
} // namespace crulet
} // namespace clang

#endif