#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECKER_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECKER_H

#include "clang/Frontend/CompilerInstance.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include "CruletContext.h"

namespace clang {
namespace crulet {

class CruletChecker : public ast_matchers::MatchFinder::MatchCallback {
public:
  CruletChecker(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg, 
                DiagnosticIDs::Level DiagLevel = DiagnosticIDs::Warning);
  virtual ~CruletChecker();
  
  virtual void registerPPCallbacks(CompilerInstance &CI) {}
  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) {}
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) {}

  CruletContext* getCruletContext();
  StringRef getName();
  StringRef getReportMsg();
  DiagnosticIDs::Level getDiagLevel();

protected:
  CruletContext *Context;
  std::string CheckerName;
  std::string ReportMsg;
  DiagnosticIDs::Level DiagLevel;
};

} // namespace crulet
} // namespace clang

#endif