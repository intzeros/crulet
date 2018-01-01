#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_MODULE_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_MODULE_H

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletContext.h"
#include "CruletChecker.h"
#include <map>
#include <vector>

namespace clang {
namespace crulet {

class CruletModule {
public:
  CruletModule(CruletContext *Context, StringRef ModuleName);
  virtual ~CruletModule();

  virtual void registerCheckers(ast_matchers::MatchFinder *Finder) = 0;
  std::vector<std::string> getCheckerNames();
  StringRef getName();

  template <typename CheckerType>
  void registerChecker(StringRef CheckerName, ast_matchers::MatchFinder *Finder){
    if(Context->isCheckerEnabled(CheckerName)){
      createChecker<CheckerType>(CheckerName)->registerMatchers(Finder);
    }
  }
  
protected:
  template <typename CheckerType>
  CruletChecker* createChecker(StringRef CheckerName){
    if(CheckerMap.find(CheckerName) == CheckerMap.end()){
      CheckerMap[CheckerName] = new CheckerType(CheckerName);
    }
    return CheckerMap[CheckerName];
  }

protected:
  std::string ModuleName;
  std::map<std::string, CruletChecker*> CheckerMap;
  CruletContext *Context;
};

} // namespace crulet
} // namespace clang

#endif