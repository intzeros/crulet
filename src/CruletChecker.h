#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECKER_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECKER_H

#include "clang/Frontend/CompilerInstance.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletContext.h"

namespace clang {
namespace crulet {

class CruletChecker : public ast_matchers::MatchFinder::MatchCallback {
public:
  CruletChecker(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg)
      : Context(Context), CheckerName(CheckerName), ReportMsg(ReportMsg) {}
  virtual ~CruletChecker() {}
  
  virtual void registerPPCallbacks(CompilerInstance &CI) {}
  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) {}
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) {}

  StringRef getName();

protected:
  CruletContext *Context;
  std::string CheckerName;
  std::string ReportMsg;
};

} // namespace crulet
} // namespace clang

#endif