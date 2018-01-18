#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_MODULE_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_MODULE_H

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletContext.h"
#include "CruletChecker.h"
#include <unordered_map>
#include <vector>

namespace clang {
namespace crulet {

class CruletModule {
public:
  CruletModule(CruletContext *Context, StringRef ModuleName)
      : Context(Context), ModuleName(ModuleName) {}
  virtual ~CruletModule();

  virtual void registerCheckers() = 0;
  std::vector<std::string> getCheckerNames();
  StringRef getName();

  void addCheckerActions(CompilerInstance &CI, ast_matchers::MatchFinder *Finder);

  template <typename CheckerType>
  void registerChecker(StringRef CheckerName, StringRef ReportMsg){
    if(Context->isCheckerEnabled(CheckerName)){
      createChecker<CheckerType>(CheckerName, ReportMsg);
    }
  }
  
protected:
  template <typename CheckerType>
  CruletChecker* createChecker(StringRef CheckerName, StringRef ReportMsg){
    if(CheckerMap.find(CheckerName) == CheckerMap.end()){
      CheckerMap[CheckerName] = new CheckerType(Context, CheckerName, ReportMsg);
    }
    return CheckerMap[CheckerName];
  }

protected:
  CruletContext *Context;
  std::string ModuleName;
  std::unordered_map<std::string, CruletChecker*> CheckerMap;
};

} // namespace crulet
} // namespace clang

#endif