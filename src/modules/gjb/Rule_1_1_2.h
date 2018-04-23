#ifndef CRULET_GJB_RULE_1_1_2_H
#define CRULET_GJB_RULE_1_1_2_H

#include "../../CruletChecker.h"
#include <unordered_map>

namespace clang {
namespace crulet {
namespace GJB {

class Rule_1_1_2 : public CruletChecker {
public:
  Rule_1_1_2(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
      DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning)
      : CruletChecker(Context, CheckerName, ReportMsg, DiagLevel) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
  std::unordered_map<std::string, SourceLocation> LabelMap;
  std::unordered_map<std::string, SourceLocation> NameMap;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif